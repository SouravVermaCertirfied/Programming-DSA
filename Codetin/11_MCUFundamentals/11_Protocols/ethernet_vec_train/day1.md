# Ethernet for AUTOSAR Engineers

If you've spent your career in CAN, this is written for you. You already know signals, arbitration, DLC, and the discipline of squeezing a system onto a shared bus. Ethernet asks you to unlearn a few things and relearn a few others. Let's walk through it together, the way I'd explain it over a whiteboard.

## Ethernet, in a Nutshell

- **Speed**: started at 10 Mbps in the 1980s and today automotive variants run from 100 Mbps up to multi-gigabit.
- **General usage**: the backbone of enterprise networks, data centers, and now the backbone of the modern vehicle's data network.
- **First introduced**: developed at Xerox PARC in 1973, standardized as IEEE 802.3 in 1983.

---

# Ethernet PHY Layer

## Why Ethernet in Automotive Now?

Ethernet has been sitting quietly in IT closets and data centers for four decades. So why is it suddenly showing up in the car you're designing today?

The honest answer is bandwidth. CAN gives you kilobits, CAN-FD gives you a few megabits, but the modern vehicle doesn't just exchange small status signals anymore — it moves images, video streams, and large chunks of diagnostic and configuration data. Think about what's actually generating traffic in a car today:

- **Car charging billing (Plug & Charge, ISO 15118)** — a TLS-secured, TCP/IP conversation between the vehicle and the charging station, negotiating identity, contracts, and billing. This is fundamentally an internet-style protocol stack; it doesn't fit on CAN at all.
- **Telematics** — the car talking to the cloud, pushing diagnostics, receiving OTA updates. Large payloads, needs routing, needs security.
- **Cameras (ADAS, surround view, mirror replacement)** — a single automotive camera can produce tens of megabits per second of raw or compressed video. No classical automotive bus other than Ethernet can carry that.
- **Infotainment** — audio/video streaming, screen mirroring, navigation map data, all bursty and bandwidth-hungry.

So it isn't that Ethernet is new — it's that the car finally has workloads that only Ethernet's bandwidth can serve. And once you're paying the cost of putting Ethernet in the vehicle for these high-bandwidth consumers, it becomes attractive to extend it as the general-purpose backbone too, with CAN and LIN pushed down to where they're still the right, cheaper tool for simple sensors and actuators.

## Advantages of CAN (Let's Give It Its Due First)

Before we tear into Ethernet's problems, it's worth remembering why CAN won the last thirty years of automotive networking:

- **EMC (Electromagnetic Compatibility)**: CAN's differential signaling on a twisted pair is inherently robust to noise — CAN_H and CAN_L move in opposite directions, so common-mode noise cancels out.
- **Wiring**: a single twisted pair, multi-dropped across dozens of nodes. Minimal copper, minimal weight, minimal cost.
- **Multi-master**: any node can attempt to transmit; there's no single controller node required.
- **Arbitration**: the bitwise, non-destructive arbitration mechanism means that when two nodes transmit at once, the higher-priority message simply wins — the loser backs off mid-frame without corrupting anything. No frame is ever lost to a collision. This is the single most elegant thing about CAN.
- **Multi-drop topology**: every node hangs off the same physical bus, so adding a node is often as simple as tapping into the existing wire.

## Where "Internet" Ethernet Falls Short for Automotive

Classic office/IT Ethernet (think the RJ45 cable running to your desk) has two problems the moment you try to drop it into a car unmodified:

1. **EMC**: traditional Ethernet (10BASE-T, 100BASE-TX) uses unshielded or lightly shielded twisted pairs not engineered for the electrically noisy environment of an engine bay, and it wasn't designed to keep emissions low enough to avoid interfering with the car's radio and other sensitive electronics.
2. **Collision handling**: classic Ethernet (10BASE-T half-duplex, using CSMA/CD) does not have CAN's graceful arbitration. When two nodes transmit at the same time, both frames collide and get corrupted. Both nodes detect the collision, and each waits a random "back-off" period before retrying. This is fine for a lightly loaded office network where a garbled retry costs you a few extra milliseconds — but it is not deterministic, and determinism is close to a religious requirement in automotive control systems.

## How Automotive Ethernet Solved These Shortcomings

### Solving EMC: MII and MDI

The fix for EMC borrows a page straight from CAN's playbook: **differential signaling**. Automotive Ethernet's physical connection is split into two conceptual pieces:

- **MDI (Medium Dependent Interface)** — the actual electrical/physical connector and cabling standard, defining voltage levels, differential pairs, and connector pinout, tuned specifically for the automotive electrical environment.
- **MII (Media Independent Interface)** — the standardized digital interface between the MAC (part of the microcontroller/SoC) and the PHY (the physical transceiver chip). "Media independent" means the MAC doesn't need to know or care whether the PHY is driving 100BASE-TX, 100BASE-T1, or something else — the digital interface looks the same.

Here's the part that trips up CAN engineers: CAN is **serial** — one bit, one wire pair, one moment in time. Classic Ethernet MII variants are **parallel** — multiple data lines carry multiple bits of the same "chunk" simultaneously, alongside a clock line that tells the receiver when to sample.

That's where the naming family comes from:

| Interface | Data width | Typical clock | Approx. speed |
|---|---|---|---|
| MII | 4 bits (nibble) | 25 MHz | 100 Mbps |
| RMII (Reduced MII) | 2 bits | 50 MHz | 100 Mbps |
| GMII | 8 bits | 125 MHz | 1 Gbps |
| RGMII | 4 bits (double data rate) | 125 MHz | 1 Gbps |

The trade-off is simple arithmetic:

**Speed = clock frequency × number of parallel lines (× bits per clock edge)**

Fewer lines means fewer pins on your chip package and fewer PCB traces to route — cheaper and simpler — but you pay for it with a higher required clock frequency to hit the same speed. More lines lets you run a gentler clock, but costs you pins and board real estate. RMII and RGMII exist specifically to claw back pin count by clocking faster or using both clock edges.

### Getting to 100BASE-T1

Now let's bring you to the standard that actually matters for most in-vehicle Ethernet today: **100BASE-T1**.

- **Two wires, not four**: office 100BASE-TX needs two twisted pairs (four wires) — one pair to transmit, one to receive. That's real wiring-harness overhead in a car where every gram and every connector pin costs money. 100BASE-T1 does full-duplex, 100 Mbps communication over a **single twisted pair**, simultaneously in both directions. This is a big deal for automotive — it's the wiring-cost story that made Ethernet viable in the harness in the first place, echoing exactly why CAN's single twisted pair was so attractive.
- **PAM3 instead of dominant/recessive logic**: CAN encodes a bit as one of two voltage states — dominant or recessive. 100BASE-T1 instead uses **PAM3 (Pulse Amplitude Modulation, 3 levels)** — each symbol sent on the wire can take one of three voltage levels, and clever encoding across those symbols is what allows both directions of traffic to share the same pair without one side's transmission simply drowning out the other (more on this below when we talk about full duplex).
- **Sleep and wake-up, CAN-style**: just like CAN nodes can go to sleep to save power and wake on bus activity or a wake-up frame, 100BASE-T1 nodes support low-power sleep states and a defined wake-up mechanism, so an ECU's Ethernet interface doesn't have to stay fully powered just to remain reachable.

## 100BASE-TX vs 100BASE-T1

| | 100BASE-TX | 100BASE-T1 |
|---|---|---|
| Wiring | 2 twisted pairs (4 wires) | 1 twisted pair (2 wires) |
| Duplex mechanism | Separate Tx/Rx pairs | Simultaneous bidirectional on same pair (echo-cancelled) |
| Line code | MLT-3 (multi-level, not PAM3) | PAM3 |
| EMC design target | Office environment | Automotive-grade EMC |
| Typical use | IT/office networks | In-vehicle networks |

## How Ethernet Solves the Collision Problem — With a Switch

This is the part that will genuinely change how you think about the network, coming from CAN.

CAN solves collisions through arbitration on a **shared, multi-drop bus** — every node hears every transmission and the priority scheme sorts out who "wins." Ethernet in the car takes a completely different architectural approach: instead of a shared medium, every ECU gets its **own dedicated point-to-point link** into a central device called a **switch**. There is no shared wire for multiple ECUs to fight over, so there is structurally **no collision at all** — not "collisions are handled well," but "the topology makes collisions physically impossible" on each link.

Here's how the switch pulls this off:

- Every port on the switch is its own isolated, full-duplex, point-to-point 100BASE-T1 (or similar) link to exactly one ECU.
- When ECU A wants to talk to ECU C, it sends its frame to the switch. The switch looks at the destination and forwards the frame out only the port connected to C.
- If two ECUs (say B and C) both send a frame destined for the same ECU (A) at almost the same instant, there's no collision on the wire — B's frame and C's frame each arrive on their own separate physical link into the switch without ever touching each other electrically. The switch simply queues one behind the other in an internal **buffer** and transmits them to A back-to-back, one after another, at wire speed. Nothing is corrupted; at worst, one of the two frames experiences a small buffering delay.

### Worked example 1 — three ECUs sending to one

Take four ECUs, all connected to a switch: ECU1, ECU2, ECU3, ECU4.

ECU2, ECU3, and ECU4 all send a frame to ECU1 at essentially the same moment.

- Each of ECU2, 3, and 4 has its own dedicated link into the switch — no contention on any of those three links.
- The switch receives all three frames essentially simultaneously on three different ingress ports.
- ECU1 has only one link, so it can only receive one frame at a time. The switch buffers the frames destined for ECU1 and transmits them one after another out of ECU1's port — say ECU2's frame first, then ECU3's, then ECU4's (order depends on arrival timing and switch scheduling/priority).
- No data is lost. Worst case, ECU4's frame sits in a buffer for a short queuing delay.

### Worked example 2 — three ECUs sending to one, and that one transmitting back at the same time

Now add the twist: ECU2, 3, and 4 are sending to ECU1, **and ECU1 is simultaneously transmitting its own frame** (say, back to ECU2) at the very same instant.

This is where **full duplex** — and PAM3 — earns its keep. ECU1's link to the switch can carry data in both directions at the same time on the same physical pair, because:

- 100BASE-T1 uses **echo cancellation**: each side knows exactly what it itself is transmitting, so it can mathematically subtract its own outgoing signal from the combined voltage it sees on the wire, leaving only what the other side sent.
- PAM3's multi-level encoding is what makes the combined, overlapped signal on the wire decomposable in this way — the transmitted and received symbols are superimposed on the same pair, and each endpoint's own knowledge of what *it* sent lets it cleanly recover what the other side sent.

So ECU1 can receive frames arriving from the switch (originally from ECU2, 3, 4) while simultaneously transmitting its own frame to the switch, all on the same physical pair, with no collision and no need to "wait its turn" the way half-duplex CSMA/CD would require.

**A neat side effect**: because the voltage on the wire at any instant is really the superposition of *both* directions' PAM3 signals, someone tapping the wire from outside — without knowing exactly what one side itself transmitted — sees a combined waveform that isn't trivially separable into "message from ECU1" and "message from ECU2." Only the two endpoints, each of which knows its own transmitted symbols and can cancel them out, can cleanly recover the other side's data. It's not designed as an encryption mechanism — real automotive networks still need proper security (MACsec, TLS, etc.) — but it does mean casual eavesdropping on a differential automotive Ethernet pair is meaningfully harder than it looks at first glance.

## Link Speed vs Network Speed

In CAN, **link speed and network (effective) speed are the same number**, because there's exactly one shared medium — everyone is on the same wire, so the bus's bit rate *is* the network's total capacity, full stop. If your CAN bus runs at 500 kbps, the entire network's aggregate capacity is 500 kbps, shared by everyone.

Switched Ethernet breaks that equivalence, because each ECU has its **own dedicated link**, and the switch can move traffic across multiple links **simultaneously**.

Take the same 4-ECU example, all on 100BASE-T1 links (100 Mbps link speed each):

- ECU1 → ECU2, ECU3 → ECU4, and so on — if traffic pairs don't share a destination port, the switch can be moving 100 Mbps on the ECU1↔ECU2 link **at the exact same time** as it moves 100 Mbps on the ECU3↔ECU4 link.
- With 4 ECUs each pushing 100 Mbps concurrently through the switch (assuming the switch's internal fabric has enough capacity, i.e., it's non-blocking), the aggregate, instantaneous network throughput can be as high as **4 × 100 Mbps = 400 Mbps** — four times the speed of any single link.

This is a fundamentally different mental model from CAN: **link speed is a per-cable number; network speed is what the switch fabric can move in aggregate across all its ports at once.**

## Switch vs Router

- **Switch** operates at Layer 2 (MAC addresses). It forwards frames within a single local network based on learned MAC-address-to-port mappings. Fast, simple, no awareness of IP.
- **Router** operates at Layer 3 (IP addresses). It forwards packets *between* different networks/subnets, making decisions based on IP addresses and routing tables, and is what lets your vehicle's internal network talk out to, say, a telematics unit's cellular-facing network or ultimately the cloud.

---

# Ethernet: Layer 2 [MAC + VLAN]

## Addressing Modes

- **Unicast (1:1)**: one sender, one specific intended receiver.
- **Multicast (1:m)**: one sender, a defined group of interested receivers.
- **Broadcast (1:n)**: one sender, every node on the local network segment.

## The Ethernet Frame

A simplified breakdown of an Ethernet II frame:

| Field | Size | Purpose |
|---|---|---|
| Preamble + SFD | 8 bytes | Clock sync, marks start of frame |
| Destination MAC | 6 bytes | Who it's going to |
| Source MAC | 6 bytes | Who sent it |
| EtherType / VLAN tag | 2 (or 4 with VLAN) bytes | What's inside / VLAN info |
| Payload | 46–1500 bytes | The actual data |
| FCS (CRC) | 4 bytes | Error detection |

One thing that will feel strange coming from CAN: **there is no acknowledgment bit in the Ethernet frame.** CAN gives you a hardware ACK slot in every single frame — the receiver flips a bit in real time to confirm receipt. Ethernet has nothing equivalent at Layer 2. A frame either arrives intact (CRC checks out) or it's silently dropped — the sender at Layer 2 has no built-in way to know.

So how do you get reliability? That's pushed up to **TCP** at the Transport Layer. TCP numbers every byte it sends and requires the receiver to acknowledge what it's gotten; if an acknowledgment doesn't come back in time, TCP assumes the data was lost and retransmits it. This "reliability is the transport layer's job, not the link layer's job" split is one of the more important mental adjustments coming from CAN, where reliability lived right down at the frame level.

## EtherType Field

The EtherType field tells the receiver what kind of payload is riding inside the frame:

- `0x8000`... — wait, let's be precise: **`0x0800`** = IPv4
- **`0x86DD`** = IPv6
- **`0x8100`** = VLAN-tagged frame (802.1Q)
- **`0x88F7`** = PTP (Precision Time Protocol, used for automotive time sync)
- **`0x0806`** = ARP

## MAC Address Bit Semantics

Within the 48-bit MAC address, specific bits carry meaning, checked at the first byte transmitted:

- **Unicast vs. Multicast**: the least significant bit of the first octet — if it's 0, the address is unicast (one destination); if it's 1, the address is multicast (a group).
- **Global vs. Local (U/L bit)**: the second-least-significant bit of the first octet — if 0, the address is **globally unique**, assigned by the vendor from an IEEE-allocated block (a "burned-in" address); if 1, the address is **locally administered** — assigned by whoever configured the network, with no guarantee of global uniqueness.
- **Global (vendor) MAC bits**: the upper 24 bits of a globally-administered address are the **OUI (Organizationally Unique Identifier)**, purchased and registered by the manufacturer from the IEEE. The lower 24 bits are then assigned by that manufacturer to uniquely identify each device it makes.

## Switch Table (MAC Address Table)

Every switch maintains a table mapping **Port ↔ MAC address**, built through three behaviors:

- **Learning**: when a frame arrives on a port, the switch notes "this source MAC lives on this port" and records it in the table.
- **Flooding**: if the switch receives a frame for a destination MAC it hasn't learned yet, it doesn't know which port to send it out, so it floods the frame out of every port except the one it arrived on.
- **Forwarding**: once the destination MAC is known in the table, the switch sends the frame only out the correct single port — efficient, no unnecessary traffic on other links.

## VLAN (Virtual LAN)

A VLAN lets you logically partition a single physical switched network into multiple isolated broadcast domains, without needing separate physical switches or cabling for each.

**Why it matters in a vehicle:**

- **Benefit**: you can group ECUs by function — say, all infotainment-related ECUs on one VLAN and all powertrain-related ECUs on another — so broadcast traffic and general chatter from one domain doesn't spill into, or burden, the other.
- **Cybersecurity benefit**: VLANs create a hard boundary. Even if an infotainment ECU (which might have more external attack surface, e.g. via Bluetooth or a cellular modem) were compromised, VLAN segmentation prevents it from directly reaching safety-critical ECUs on a different VLAN, unless a router/gateway explicitly permits and inspects that path.

**Default VLAN**: any switch port that isn't explicitly assigned to a specific VLAN falls back to a **default VLAN** (commonly VLAN 1). For example, if you plug a diagnostic tool into a switch port that was never configured for a particular VLAN, it lands on the default VLAN and only sees traffic within that default group — useful to know when you're wondering why your test tool "sees" only some ECUs and not others.

## PCP (Priority Code Point)

Inside the VLAN tag (802.1Q) sits a 3-bit **PCP** field, letting a frame declare one of 8 priority levels. This is how automotive Ethernet gets some of CAN's prioritization spirit back — a switch can look at PCP and decide to service a high-priority frame (say, a safety-related control message) ahead of a lower-priority one (say, an infotainment media stream) when both are competing for the same egress port.

---

# Layer 3: Network Layer

## IPv4 vs IPv6

**IPv4** — a 32-bit address, conceptually split into a **Network Prefix** and a **Host/Interface ID**, with the split point defined by a subnet mask (e.g., `/24` means the first 24 bits are the network prefix, the remaining 8 bits identify the specific host).

- **Local (private)** addressing: ranges like `192.168.x.x`, `10.x.x.x` are reserved for use inside private networks (your in-vehicle network, for instance) and aren't routable on the public internet directly.
- **Public (global)** addressing: globally unique, routable addresses used for direct communication over the internet — relevant when the vehicle's telematics unit talks out to a backend server.

**IPv6** — a 128-bit address, also split into a **Network Prefix** and an **Interface ID**, but the interface ID is often derived directly from the device's MAC address (via EUI-64), and the address space is so vast that private/public address exhaustion concerns from IPv4 largely disappear.

## Payload Value

The payload (protocol) field in the IP header tells the receiving stack what's riding inside the IP packet — e.g., value 6 means TCP is next, value 17 means UDP is next, so the stack knows which upper-layer parser to hand the data to.

## Packet Content Breakdown

Each IP packet carries some key identification fields:

- **Packet (Identification) ID**: a 16-bit value that uniquely tags all the fragments belonging to one original packet, so the receiver knows which fragments to reassemble together.
- **Fragmented vs unfragmented**: if the original data was too large for the underlying link's MTU, the IP layer splits it into multiple fragments, each carrying the same identification ID.
- **Offset (in fragmented packets)**: each fragment carries an offset value indicating where its data belongs within the original, reassembled packet — like knowing which page number a torn-out sheet belongs to in a book.
- **Unfragmented packets** simply carry an offset of zero, since there's nothing to reassemble.

## TTL (Time To Live)

TTL is a counter set by the sender and decremented by one at every router hop the packet passes through. If TTL reaches zero before the packet reaches its destination, the packet is discarded, and (typically) an ICMP message is sent back to the source.

**Why it matters**: it prevents a packet from circulating forever if a routing loop or misconfiguration exists — without TTL, a single stray packet caught in a loop could keep consuming bandwidth and processing indefinitely, contributing to network overload. It's a safety valve against runaway traffic, conceptually similar to why you'd want a bounded retry count anywhere in a control system.

## UDP vs TCP

| | UDP | TCP |
|---|---|---|
| Connection | Connectionless | Connection-oriented (handshake required) |
| Reliability | None built-in — no acks, no retransmission | Reliable — acknowledgments, retransmission, ordering |
| Overhead | Low | Higher |
| Use case | Real-time, latency-sensitive (e.g. someIP events, streaming) | Where guaranteed, ordered delivery matters (e.g. diagnostics, large data transfer) |

## NH (Next Header) in IPv6

IPv6 replaces IPv4's single "Protocol" field with a chainable **Next Header** field, which not only indicates the next upper-layer protocol (TCP, UDP, etc.) but can also chain through a series of IPv6 extension headers (like routing or fragmentation headers) before finally pointing to the actual payload protocol.

---

# Network Layer

## ARP: Address Resolution Protocol (IPv4)

ARP answers a simple but essential question: "I know this device's IP address, but what's its MAC address, so I can actually put a frame on the wire to it?"

- A node broadcasts an ARP request: "Who has IP X.X.X.X? Tell me your MAC."
- The node owning that IP replies directly (unicast) with its MAC address.
- The requester caches this IP-to-MAC mapping (an ARP table entry) so it doesn't need to ask again for a while.

---

# Transport Layer

## Ports (e.g., DoIP Port, SOME/IP Port)

A port is simply a 16-bit number that lets a single IP address host **multiple simultaneous, distinct conversations**, each identified by its own port number, so the receiving stack knows which application or service a given packet belongs to.

- **DoIP (Diagnostics over IP)** uses a well-known port to carry diagnostic requests/responses — the same UDS-style diagnostics you already know from CAN, just now riding over Ethernet/TCP.
- **SOME/IP** (Scalable service-Oriented MiddlewarE over IP) uses its own ports for service discovery and for the actual service method calls/events between ECUs.

Why ports matter: without them, an ECU could only really have "one conversation" per IP address at a time — ports are what let, say, a diagnostic session and a SOME/IP service exchange happen concurrently on the same ECU without stepping on each other.

## Stateless vs Stateful (UDP vs TCP/IP)

- **UDP is stateless**: each packet is sent independently, with no memory of what came before. The sender doesn't track whether the receiver even got it.
- **TCP is stateful**: the connection itself is an object with a lifecycle — established via handshake, tracked with sequence numbers, and explicitly torn down. Both ends maintain state about what's been sent, acknowledged, and what's still outstanding.

**Implication for segmented vs unsegmented data transfer**: if a payload is small enough to fit in one datagram, UDP's statelessness is not a real problem — send it and move on. But once data must be split into multiple segments, TCP's statefulness becomes valuable: it tracks sequence numbers so segments can be reassembled in the correct order even if they arrive out of order, and it detects and retransmits anything lost. Doing reliable segmented transfer over UDP would mean building all of that bookkeeping yourself, at the application layer (which is exactly what protocols like SOME/IP-SD/TP have to do when they run large data over UDP).

**Implication for unicast vs multicast**: TCP is inherently **unicast only** — the stateful handshake and per-connection tracking only make sense between exactly two endpoints. UDP, being stateless and connectionless, is what allows **multicast** communication (and broadcast) — a single sender can push the same datagram to a whole group without needing an individual stateful session with each member. This is why SOME/IP events, which often need to reach multiple subscribers efficiently, are built on UDP.

## Segmented Data Transfer: The TCP Handshake

TCP establishes a connection with a classic three-way handshake before any real data flows:

```
   Client                              Server
     |                                    |
     |------------ SYN ------------------>|   "I'd like to connect, my seq = X"
     |                                    |
     |<--------- SYN + ACK ---------------|   "Okay, ack X+1, and my seq = Y"
     |                                    |
     |------------ ACK ------------------>|   "Ack Y+1, connection established"
     |                                    |
     |========= data flows both ways ====|
```

**Graceful ending (FIN)**: when either side is done, it sends a FIN. The other side ACKs it, and typically also sends its own FIN once it's done in its direction too, which then gets ACKed — a clean, mutually agreed teardown.

```
   Client                              Server
     |------------ FIN ------------------>|
     |<----------- ACK -------------------|
     |<----------- FIN -------------------|
     |------------ ACK ------------------>|
```

**Reset ending (RST)**: when something has gone wrong — an unexpected condition, an error, a connection that needs to be torn down immediately without the polite back-and-forth — either side can send an **RST**, which abruptly terminates the connection right away, no graceful negotiation involved.

## Congestion Control

TCP doesn't just blast data at full speed — it continuously estimates how much the network (and the receiver) can currently handle, and throttles its own sending rate accordingly. It starts conservatively, ramps up as acknowledgments confirm the network can handle more (roughly speaking, "slow start"), and backs off sharply if it detects loss (interpreted as a sign of congestion) — all to avoid one aggressive sender overwhelming shared network capacity and to allow multiple flows to share bandwidth reasonably fairly.

---

# Ethernet in AUTOSAR

## Brief History

- **BMW** is widely credited as an early automotive adopter driving Ethernet into production vehicles, initially for high-bandwidth use cases where nothing else would do the job — camera-based systems and diagnostics-over-Ethernet at the assembly-line/service level were among the earliest drivers.
- In its earliest days, in-vehicle Ethernet had **very little standardization** — early adopters had to define much of the automotive-specific behavior (physical layer, EMC handling, etc.) themselves, often working directly with a small set of suppliers, before industry-wide standards existed.
- Over time, through organizations like OPEN Alliance and IEEE 802.3 automotive task forces, these early proprietary/one-off approaches converged into real standards (100BASE-T1 and beyond) that any OEM or supplier could design against.
- Inside AUTOSAR specifically, Ethernet support matured in stages:
  - **AUTOSAR Classic Platform Release 3** introduced initial building blocks for Ethernet-related communication.
  - **AUTOSAR Classic Platform Release 4** substantially expanded this — adding the fuller communication stack modules (like SoAd, TCP/IP stack modules, DoIP support) needed to make Ethernet a first-class citizen alongside CAN in the Basic Software.

## Sockets

A **socket** is the fundamental endpoint abstraction for network communication — it's what an application actually opens and uses to send/receive data, and it's defined by the combination of:

- Source IP address
- Source port
- Destination IP address
- Destination port
- Protocol (UDP or TCP)

Change any single one of those five values, and you conceptually have a *different* socket — which is exactly why, as we'll see below, changing a socket parameter forces AUTOSAR to create a new one rather than just tweak the existing one.

## SoAd (Socket Adapter) Module

Classic AUTOSAR's Basic Software was built around signal/PDU routing concepts from the CAN world — it had no native notion of a "socket" the way a general-purpose OS does.

**SoAd's job** is to bridge that gap: it sits between the upper communication layers (PDU Router, and ultimately application-facing modules like DoIP, SOME/IP) and the TCP/IP stack, translating AUTOSAR's PDU-based world into actual socket operations (opening, closing, sending/receiving over specific sockets) and back again. In short: **SoAd is what lets a platform built around signals and PDUs speak fluent sockets**, without every upper module needing to understand TCP/IP directly.

## Containers

In AUTOSAR Ethernet communication, a **container** is a mechanism to pack multiple smaller PDUs together into one larger PDU before it goes out over the wire — much like carpooling several small errands into one trip, so you're not paying the fixed "trip overhead" (Ethernet/IP/UDP header cost, transmission overhead) separately for every tiny PDU.

**Triggering a container to actually send** can be configured through a few different strategies:

- **Message from a certain ECU/PDU**: sending is triggered as soon as a specific, designated PDU arrives to be packed — effectively saying "the moment this particular signal shows up, flush the container now."
- **Threshold byte count**: the container is sent once it has accumulated a configured number of bytes — prioritizing efficient use of the frame size over strict timing.
- **Threshold number of ECUs contributing**: the container waits until a configured number of distinct contributing ECUs/PDUs have added their data, then sends — useful when you specifically want data from a known set of sources bundled together before transmission.

**Why at least one socket per ECU is required**: since a socket is defined by that IP/port/protocol tuple, each ECU that needs to send or receive its own distinct stream of container/PDU traffic needs at least one socket configured to represent that communication relationship — without it, there's no addressable, protocol-aware endpoint for that ECU's traffic to flow through.

**Why changing a socket parameter forces a new socket**: because a socket's identity *is* the tuple (source IP, source port, destination IP, destination port, protocol). If you change any one of those — say, the destination port — you are, by definition, no longer describing the same communication endpoint; the underlying stack (and AUTOSAR's configuration model) has to instantiate a genuinely new socket to represent that new combination, rather than mutate the old one in place.

---

That's the tour — from PAM3 on a twisted pair all the way up to containers inside SoAd. The throughline worth holding onto: almost every "weird new Ethernet thing" is solving a problem CAN solved differently, not solving a problem CAN never had. Keep translating back to CAN concepts as you go deeper, and the rest of the stack (SOME/IP, DoIP, TSN) will click into place much faster.