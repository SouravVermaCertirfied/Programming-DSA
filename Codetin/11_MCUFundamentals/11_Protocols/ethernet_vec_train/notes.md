write the training content, for teaching Ethernet to the Autosar engineers.
here is the outline of the blog. Keep the tone personal, as if you are talking to them.

# Ethernet
- speed, generate usage, first introduced in - in one line each.

# Ethernet PHY Layer

## Why Ethernet in Automotive now ? What are applications of Ethernet in a vehicle now a days  ? eg car charing billing, telematics, camera, infotaiment
- it has been for so long in practice, but why now being used ?

## Advangeages of CAN
- EMC, Wiring, Multimaster, Arbitration does not let frame loss, multi-drop

## Issues of internet Ethernet when comapred to CAN
- has EMC, Collisoin handling has back off mechanism (  when there is collions both wait for some time and then start sending again).

## How the short comings of intenet Ethernet were solved in automotive Ethenet ?
- Solving EMC : usage of MII and MDI ( making differentltial volatage like CAN)
    - Some info about MDI and MII ( explain how CAN has bit by bit , but in ethenet how parallel N number of wires can be used  and how MDI and MII help in this)
    - explain how clock speed * number of lines = speed of the communication, their trade off. touch upon standards of MII, RMII, GMII etc.

## Try to bring reader to 100BaseT1 standard.
    - how 2 fixed lines solved - wire overhead
    - PAM3 over dominant - ressive logic 
    - Sleep and wakeup handled like in CAN

## Compare 100BaseTS vs 100BaseT1

## Explain how ethernet solves collion problem
    - usage of switch
    - how swich and design choise is done to make NO COLLISION AT ALL.
    - explain how switch handles collions - show usage of buffers. 
    - take two examples using 4 ECU
        - eg : ECU 2, 3 and 4 sending message to 1.
        - eg : ECU 2, 3 and 4 sending message to 1 and 1 also transmitting at the same item. Highlight and explain how PAM3 helps achive the full duplex communication.
            - Add how the PAM3 and overlapsm makes it difficult for someone reading from outside to understand what is being sent in the network, as only the ECU sending reciving can fully understand by removing compoenet what is there in the network.

## Explain Link Speed and Network Speed 
    - CAN why link speed and Network speed is always same.
    - Why in Eth link speed != Network speed. take example of 4 ECU, and show network speed can be 4 times link speed. take 100BaseT1 into consideration.

## Switch vs Router

# Ethernet : Layer 2 [ MAC + VLAN ]

## Explain addressing modes 
    - unicast 1:1
    - multicast 1:m
    - broadcast 1:n

## Explain Eth frame
    - eth frame breaddown
    - highlight how eth does not has ack bit like in CAN.. touch upon how that is handled in TCP Layer. How missed frames are handled by TCP.

## Explain Ethent type field
    - 0x8600 IPV6, 0x800 IPV4 , 0x8867 - PTP, 0x806 - ATP

## In IPV4 explain how the bits are set/rest for;
    - unicast
    - multicast
    - Global MAC vs Local MAC. Bit that differentiats it.
    - Global MAC bits to be bought by Vendor.

## Explain Switch table
    - Port | MAC pairs
    - Learning
    - Flooding
    - Forwarding

## VLAN 
    - what is vlan
    - use case - benfits, cybersecuirty benfifit.
    - Explain defulat VLAN concept withh example

## Explain PCP

# Layer 3 : NETWORK LAYER

## IPV4 vs IPV6
    - explain IPV4  , Network prefix | Interface ID, and their breakdown.
        - local and public (global)
    - IPV6 - Network prefix | Interface ID, and their breakdown.

## Payload value

## Each packet content breakdown
    - packet id
    - packet 
        - fragmented
        - unfragmented
            - offset in unfragmented

## TTL value
    - explain TTL
    - expriy and signficance in network overload avoidance

## Explain and compare UDP and TCP

## NH in IPV6

# Network Layer

## ARP : Addresss Resolution Protocol in IPV4


# Transport Layer

## Ports eg DoIP prot, someIP port
    - what , why 

## Stateless vs Statefull explain and compare wrt UDP and TCP/IP
    - explain implication wrt segmented and unsegmented data transer.
    - unicast vs multicast implication wrt UDP and TCP/IP

## Segmented data transfer
    - explain the handshake with ASCII Diagram
    - Gracefull ending
    - reset flag ending - eg when error

## Congestion Control 

# ETH in Austsar

## Bried history 
    - BMW brought it when for what use case
    - earlier they it had little standard
    - how starnds become standards
        - componets added Autosar version 3
        - componets added Autosar version 4

## Sockets
    - what is socket
    - what the minimum requirement to build a socket
        - source port, dest port, src ip, dst ip, protocl - UDP/TCP

## Explain SoAd module
    - function of SoAd module
    - how this fullfils the gap of autosar not having Sockets

## Containers
    - how containers are used pack smaller PDU to make it bigger.
    - explain approacehs to handle containers trigger
        - message from certain ecu
        - threshold byte
        - thereshold number of ecu
    - for each ecu why atleast 1 socket is required
    - why any change in socket paramter will case creation of new socket.


