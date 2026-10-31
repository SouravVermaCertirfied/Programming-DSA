# 1. How does the I2C slave like a sensor or eeprom progess the bits coming from the master ?

Most I2C sensors do not run a software program or firmware for communication. Instead, everything from listening to the bus to responding is handled by **dedicated hardwired digital logic** (shift registers, comparators, and finite state machines) etched directly into the silicon.

---

### How I2C device Address Detection Works

1. **Shifting Bits In:** As the master transmits the start condition followed by the 7-bit (or 10-bit) slave address on the SDA line, an internal **shift register** inside the sensor captures the incoming bits synchronized by the SCL clock pulses.
2. **Hardware Comparison:** A built-in **digital comparator circuit** instantly compares these incoming bits against the sensor's configured address (which is either hardcoded at the factory or determined by the physical wiring of address pins like $A_0, A_1$ tied to GND or $V_{CC}$).

### How the ACK Bit is Set

The I2C protocol uses a 9-clock cycle for every byte transferred (8 bits of data or address, followed by 1 acknowledgement bit). On that 9th clock pulse:

* **If the Address Matches:** The sensor's hardware automatically activates an internal **open-drain output transistor** that pulls the SDA line **LOW** (to ground). When the master checks the state of the SDA line during the 9th clock pulse, seeing it pulled low tells it that the slave has acknowledged (**ACK**).
* **If the Address Does Not Match:** The sensor stays completely passive and does nothing. External pull-up resistors keep the SDA line **HIGH**, which the master reads as a NACK (Not Acknowledged), and the sensor ignores the rest of that transaction.

Because this is implemented purely with logic gates and transistors rather than a CPU running code, the response happens almost instantaneously with zero software overhead.



# 1.1 Deep Dive : External `EEPROM` on `I2C`

Most I2C sensors do not run a software program or firmware for communication. Instead, everything from listening to the bus to responding is handled by **dedicated hardwired digital logic** (shift registers, comparators, and finite state machines) etched directly into the silicon.

---

### How Address Detection Works

1. **Shifting Bits In:** As the master transmits the start condition followed by the 7-bit (or 10-bit) slave address on the SDA line, an internal **shift register** inside the sensor captures the incoming bits synchronized by the SCL clock pulses.
2. **Hardware Comparison:** A built-in **digital comparator circuit** instantly compares these incoming bits against the sensor's configured address (which is either hardcoded at the factory or determined by the physical wiring of address pins like $A_0, A_1$ tied to GND or $V_{CC}$).

### How the ACK Bit is Set

The I2C protocol uses a 9-clock cycle for every byte transferred (8 bits of data or address, followed by 1 acknowledgement bit). On that 9th clock pulse:

* **If the Address Matches:** The sensor's hardware automatically activates an internal **open-drain output transistor** that pulls the SDA line **LOW** (to ground). When the master checks the state of the SDA line during the 9th clock pulse, seeing it pulled low tells it that the slave has acknowledged (**ACK**).
* **If the Address Does Not Match:** The sensor stays completely passive and does nothing. External pull-up resistors keep the SDA line **HIGH**, which the master reads as a NACK (Not Acknowledged), and the sensor ignores the rest of that transaction.

Because this is implemented purely with logic gates and transistors rather than a CPU running code, the response happens almost instantaneously with zero software overhead.

--- 

</br>

# 2. How master knows what to send what to send / expect ?

The master only needs to know the **protocol contract** provided in the component's datasheet.



**The Universal Language of I2C** : I2C enforces strict, universal rules for *everyone* (how to send a START condition, how to clock bits on SCL, how to check the 9th-bit ACK).

### What the Master *Does* Need to Know

The master's programmer must read the manufacturer's datasheet to know two specific things:

1. **The Device Address:** The unique 7-bit ID hardcoded into that specific chip (e.g., `0x50` for an EEPROM, `0x68` for an MPU6050 gyro). Without this, the master doesn't know who to call on the bus.
2. **The Command / Register Map:** The "menu" of instructions that the manufacturer designed into that specific chip's logic.
* For an EEPROM, the rule is: *"Send 2 bytes for the memory address, then stream data."*
* For a temperature sensor, the rule might be: *"Send command byte `0x00` to trigger a reading, then read 2 bytes back for the temperature."*



As long as the master follows the specific "menu" written in the datasheet, the internal hardware logic of the slave handles the rest automatically.