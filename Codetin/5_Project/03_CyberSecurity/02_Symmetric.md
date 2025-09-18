# Understanding AES (Advanced Encryption Standard)

AES (Advanced Encryption Standard) is a widely used symmetric encryption algorithm. It operates on fixed-size blocks of data and is commonly used for encrypting sensitive data in many applications, from file encryption to securing communications.

## 1. Key Concepts in AES

- **Block Cipher**: AES operates on 128-bit blocks of data at a time.
- **Key Sizes**: AES supports 128, 192, and 256-bit keys. The security level increases with the key size.
- **Rounds**: AES performs several rounds of transformations on the data. The number of rounds depends on the key size:
  - AES-128: 10 rounds
  - AES-192: 12 rounds
  - AES-256: 14 rounds

## 2. Inputs to AES

AES takes two main inputs:

- **Plaintext**: The data to be encrypted (must be in 128-bit blocks).
- **Key**: A secret key used for both encryption and decryption (either 128-bit, 192-bit, or 256-bit).

### Example Inputs

- **Plaintext**: `"This is a secret message."` (this will be padded to fit a 128-bit block).
- **Key**: A 128-bit key (16 bytes), for example: `2b7e151628aed2a6abf7158809cf4f3c`.

## 3. AES Process

AES encryption involves several steps in a sequence of rounds.

### Key Expansion

The key is expanded into multiple round keys that are used in each round of encryption.

### Initial Round (Before Main Rounds)

- **AddRoundKey**: The plaintext is XORed with the first round key derived from the original key.

### Main Rounds (Performed for 10, 12, or 14 rounds)

1. **SubBytes**: Each byte in the state is substituted using a fixed substitution table (S-box).
2. **ShiftRows**: The rows of the state are shifted to the left.
3. **MixColumns**: The columns of the state are mixed using matrix multiplication.
4. **AddRoundKey**: The state is XORed with the round key.

### Final Round (Last Round)

- **SubBytes**, **ShiftRows**, and **AddRoundKey** (without **MixColumns**).

## 4. Output of AES

The result of AES encryption is **ciphertext** — the encrypted form of the plaintext. It’s typically represented as a hex string or base64.

## 5. AES Decryption

Decryption is the reverse process of encryption, using the same key and applying inverse operations:

1. **Inverse SubBytes**
2. **Inverse ShiftRows**
3. **Inverse MixColumns**
4. **AddRoundKey**

The decryption algorithm recovers the original plaintext.
