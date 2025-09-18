# Firmware Verification Using RSA-SHA256

Firmware verification is an essential process in embedded systems to ensure that the firmware being executed has not been tampered with and is authentic. RSA-SHA256 is a common cryptographic combination used in the verification process. Below is a structured breakdown of the process:

---

## 1. Basics

<details><summary>Terms and Concepts</summary>

1. **Firmware**:  
   Firmware is the binary file.

2. **RSA (Rivest–Shamir–Adleman)**:  
   RSA is a widely used asymmetric encryption algorithm that uses a pair of keys: a public key (used to verify signatures or encrypt data) and a private key (used to sign data or decrypt it). RSA key sizes can vary, but commonly used sizes are 2048 bits or 4096 bits. A 2048-bit RSA key is 256 bytes.

3. **SHA256 (Secure Hash Algorithm 256-bit)**:  
   SHA256 is a cryptographic hash function that outputs a 256-bit hash (32 bytes). It is commonly used to verify data integrity. Even the smallest change in input data results in a completely different hash value.

4. **Digital Signature**:  
   A digital signature is a mathematical scheme for verifying the authenticity and integrity of digital messages or documents. It involves hashing the data (e.g., firmware) and then encrypting the hash with a private key. The size of the signature in RSA-SHA256 depends on the RSA key size. For a 2048-bit RSA key, the signature size is typically 256 bytes.

5. **Memory Layout**:  
   Firmware is typically stored in non-volatile memory (e.g., Flash, ROM) in embedded devices. Its memory layout often consists of:
   - **Bootloader**: A small program (typically 512 bytes to 1 KB) that initializes the system and verifies firmware integrity.
   - **Application Firmware**: The main software controlling the hardware, which can range from a few kilobytes to several megabytes.
   - **Metadata**: Information about the firmware, such as version, date, and signature. Metadata can vary from a few bytes to several kilobytes.

6. **Signature Structure**:  
   The signature is usually composed of two main parts:
   - **Signed Data (e.g., firmware)**: The firmware data itself or a hash of the firmware.
   - **Signature Value**: The RSA signature that corresponds to the signed data. This is generated using the private RSA key and typically occupies a fixed size, e.g., 256 bytes for a 2048-bit RSA key.
</details>

---

## 2. Inputs

For the firmware verification process using RSA-SHA256, the following inputs are required:

1. **Firmware**

2. **Public Key**: The RSA public key used for signature verification. For a 2048-bit RSA key, the size is 256 bytes. and 3072-bit RSA key size is 384 bytes.
   
3. **Signature**: The RSA-encrypted SHA256 hash of the firmware. For a 2048-bit RSA key, the size of the signature is typically 256 bytes.
   
4. **Firmware Metadata**: Metadata that includes version info, dates, and the signature. The size of metadata can vary, but it is typically in the range of a few hundred bytes (e.g., 200-500 bytes).

---

## 3. Process Encryption

This section details the process by which the firmware is signed to produce a signature using RSA-SHA256.

### Step 1: Hash the Firmware with SHA256

1. **Input**: Raw firmware (binary data). The size of the firmware file can vary significantly (e.g., 100 KB to several MB).
   
2. **Process**: 
   - The firmware is fed into the SHA256 hashing algorithm.
   - The output is a 256-bit (32-byte) digest (hash) of the firmware.

### Step 2: Sign the Hash using RSA

1. **Input**: The SHA256 hash of the firmware and the private RSA key.
   
2. **Process**: 
   - The SHA256 hash is signed using the RSA private key, generating a digital signature. 
   - This signature has a fixed size, typically 256 bytes for a 2048-bit RSA key.

3. **Output**: The RSA signature is a binary blob that corresponds to the firmware's SHA256 hash.

### Step 3: Package the Signature with Firmware

The signature is usually appended to the firmware or stored in a separate metadata structure that accompanies the firmware.

---

## 4. Output of the Signature Process

The output of the encryption process is a digitally signed firmware, which includes:

- **Firmware Binary**: The original firmware content (e.g., 1-10 MB in size).
- **SHA256 Hash of Firmware**: A 32-byte (256-bit) hash of the firmware.
- **Signature**: The RSA signature, typically 256 bytes for a 2048-bit RSA key.

This signed firmware can be transmitted to the device for verification.

---

## 5. Process Decryption (Verification)

This section describes how the device verifies the authenticity of the firmware using the RSA-SHA256 signature.

### Step 1: Extract the Signature and Firmware

- **Input**: The device receives the firmware binary and the associated signature.
- The firmware and signature are separated out, with the firmware going through the verification process and the signature used to validate the integrity of the firmware.

### Step 2: Hash the Received Firmware

1. **Input**: The firmware binary received from storage or transmission.
   
2. **Process**: 
   - The device computes the SHA256 hash of the firmware.
   - This is done the same way as the signing process.
   - The output is a 32-byte (256-bit) hash.

### Step 3: Verify the RSA Signature

1. **Input**: 
   - The computed SHA256 hash of the firmware (32 bytes).
   - The received signature (256 bytes).
   - The RSA public key (256 bytes for a 2048-bit key).

2. **Process**: 
   - The device uses the RSA public key to verify the signature of the hash.
   - The process involves decrypting the signature using the RSA public key to retrieve the original hash that was signed.
   - If the decrypted hash matches the computed hash of the firmware, the firmware is authentic and untampered with.

### Step 4: Output the Result

1. **Output**: The device outputs either:
   - **Success**: If the signature is valid, meaning the firmware is authentic and has not been tampered with.
   - **Failure**: If the signature does not match, indicating that the firmware may have been modified or corrupted.

---

## Example

Let’s consider a practical example of how the entire process works with RSA-SHA256:

### Example Setup:
- **Firmware Size**: 2 MB (2,097,152 bytes).
- **RSA Key Size**: 2048 bits (256 bytes).
- **SHA256 Hash Size**: 256 bits (32 bytes).
- **Signature Size**: 2048-bit RSA signature is 256 bytes.

### Process:

1. **Create the SHA256 Hash of Firmware**:
   - The firmware (2 MB) is hashed using SHA256, producing a 32-byte (256-bit) hash.

2. **Sign the Hash**:
   - The 32-byte hash is signed using the private RSA key, generating a 256-byte signature.

3. **Transmit Firmware and Signature**:
   - The 2 MB firmware is transmitted, along with the 256-byte RSA signature.

### Verification:

1. **Receive Firmware and Signature**:
   - The device receives the 2 MB firmware and 256-byte signature.

2. **Compute the SHA256 Hash of the Firmware**:
   - The device computes the SHA256 hash of the received 2 MB firmware, producing a 32-byte hash.

3. **Verify the Signature**:
   - The device uses the RSA public key to verify the signature.
   - If the decrypted hash from the signature matches the computed 32-byte hash of the firmware, the firmware is verified and authentic.

---

## Conclusion

Firmware verification using RSA-SHA256 involves the signing of firmware with the RSA private key and verifying the authenticity of the firmware using the RSA public key. This process ensures that the firmware has not been tampered with during transmission and is trusted to run on the target device. By utilizing the SHA256 hash and RSA encryption, this method provides a robust mechanism for ensuring the integrity and authenticity of embedded firmware.

---

```mathematica
+-------------------------------------+
|         Firmware (2 MB)             |
|   +-----------------------------+   |
|   |                             |   |
|   |      Firmware Binary        |   | 
|   |     (2,097,152 bytes)       |   | 
|   |                             |   |
|   +-----------------------------+   |
+-------------------------------------+
                 |
                 |  SHA256 Hashing
                 |
          +------------------------+
          | SHA256 Hash (256 bits)  |
          |    (32 bytes)           |
          +------------------------+
                 |
                 |  RSA-256 Signing
                 |
   +------------------------------------+
   |        Signature (RSA-256)        |
   |       (32 bytes)                  |
   +------------------------------------+
                 |
                 |  Transmit Firmware and Signature
                 |
+-------------------------------------+
|         Signed Firmware             |
|   +-----------------------------+   |
|   |                             |   |
|   |      Firmware Binary        |   | 
|   |     (2,097,152 bytes)       |   | 
|   |                             |   |
|   +-----------------------------+   |
|   +-----------------------------+   |
|   |   RSA-256 Signature         |   | 
|   |     (32 bytes)              |   | 
|   +-----------------------------+   |
+-------------------------------------+
                 |
                 |  Verification Process
                 |
   +----------------------------------+
   |   Received Firmware (2 MB)      |
   +----------------------------------+
                 |
                 |  SHA256 Hashing
                 |
          +------------------------+
          | SHA256 Hash (256 bits)  |
          |    (32 bytes)           |
          +------------------------+
                 |
                 |  RSA-256 Verification
                 |
          +--------------------------+
          |  RSA-256 Public Key      |
          |  (32 bytes)              |
          +--------------------------+
                 |
                 |  Verify Signature
                 |
   +----------------------------------+
   |  Signature Valid? (Yes/No)      |
   +----------------------------------+
                 |
                 |  Result (Success/Failure)
                 |
          +--------------------------+
          |   Firmware Authentic?     |
          |    (Yes/No)               |
          +--------------------------+

```
