# Understanding RSA (Rivest-Shamir-Adleman)

RSA is a widely used asymmetric encryption algorithm that uses a pair of keys for encryption and decryption: a **public key** for encryption and a **private key** for decryption. It is based on the mathematical problem of factoring large numbers and is widely used in applications like secure communications, digital signatures, and key exchange.

## 1. Inputs to RSA

RSA involves two main inputs:
- **Message (Plaintext)**: The data or message that you want to encrypt (for example, a text message).
- **Public Key**: The public key is used for encryption and is shared openly. It consists of:
  - **n (modulus)**: The product of two large prime numbers.
  - **e (public exponent)**: A number that is coprime with the totient of **n**.
  
In summary:
- **Message (M)**: The plaintext message you want to encrypt.
- **Public Key (n, e)**: The public key, which consists of the modulus **n** and the public exponent **e**.

### Example Inputs:
- **Plaintext message**: `"Hello"`
- **Public Key (n, e)**: `(3233, 17)` where `n = 3233` (modulus) and `e = 17` (public exponent).

## 2. Process of RSA (Key Generation, Encryption, and Decryption)

### Key Generation (for both Encryption and Decryption)

The RSA algorithm works through a few steps to generate keys:

1. **Choose two large prime numbers** `p` and `q`.  
   Example: `p = 61`, `q = 53`.
   
2. **Compute n**:  
   The modulus `n` is calculated by multiplying `p` and `q`:  
   \[
   n = p \times q
   \]
   Example: `n = 61 * 53 = 3233`.

3. **Compute Euler’s Totient Function** `φ(n)`:  
   Euler’s Totient Function of `n`, **φ(n)**, is calculated as:
   \[
   φ(n) = (p - 1) \times (q - 1)
   \]
   Example:  
   \[
   φ(n) = (61 - 1) \times (53 - 1) = 60 \times 52 = 3120
   \]

4. **Choose public exponent e**:  
   The number `e` is chosen such that `1 < e < φ(n)` and `gcd(e, φ(n)) = 1` (i.e., **e** must be coprime with **φ(n)**).  
   Commonly used values for **e** are 3, 17, or 65537.  
   Example: Choose **e = 17**.

5. **Compute private exponent d**:  
   The private key exponent **d** is calculated as the modular inverse of **e** modulo **φ(n)**:
   \[
   d \equiv e^{-1} \ (\text{mod} \ φ(n))
   \]
   This means that `d` is the number that satisfies the equation:  
   \[
   e \times d \equiv 1 \ (\text{mod} \ φ(n))
   \]
   Example: `d = 2753` (calculated using the extended Euclidean algorithm).

6. **Public Key and Private Key**:
   - **Public Key**: `(n, e) = (3233, 17)`
   - **Private Key**: `(n, d) = (3233, 2753)`

### Encryption

To encrypt a message **M**, you perform the following steps:

1. **Convert the plaintext message to an integer** **m**:  
   If the plaintext is a string, you need to convert it into a number. Typically, this is done by converting each character to its ASCII value and then combining them.

2. **Use the public key for encryption**:  
   The encryption is done by raising the message **m** to the power of **e** and taking the modulus **n**:
   \[
   c = m^e \ (\text{mod} \ n)
   \]
   Where **m** is the message, **e** is the public exponent, and **n** is the modulus.

### Example:
- Message **M**: `"HI"` (let's convert it to its ASCII values).
  - `H = 72`, `I = 73`.
  - Combine: **m = 72 73** = `7273`.
  
- Public Key: `(n = 3233, e = 17)`
- Encryption:  
  \[
  c = 7273^{17} \ (\text{mod} \ 3233) = 2201
  \]
  
So, the **ciphertext (c)** = `2201`.

### Decryption

To decrypt the ciphertext **c**, the following steps are performed:

1. **Use the private key for decryption**:  
   The decryption is done by raising the ciphertext **c** to the power of **d** (private exponent) and taking the modulus **n**:
   \[
   m = c^d \ (\text{mod} \ n)
   \]
   Where **c** is the ciphertext, **d** is the private exponent, and **n** is the modulus.

2. **Convert the decrypted integer back to plaintext**.

### Example:
- Ciphertext **c** = `2201`
- Private Key: `(n = 3233, d = 2753)`
- Decryption:
  \[
  m = 2201^{2753} \ (\text{mod} \ 3233) = 7273
  \]
- Convert `7273` back to the ASCII characters:  
  `72 = H`, `73 = I`  
  So, the decrypted message **M** = `"HI"`.

## 3. Output of RSA

The **output** of RSA consists of:
- **Ciphertext (c)**: The encrypted version of the plaintext message.
- **Decrypted Message (m)**: The original plaintext message after decryption.

### Example:
1. **Input Plaintext**: `"HI"`
2. **Output Ciphertext**: `2201`
3. **Decrypted Message**: `"HI"`

## 4. Verification of RSA

To verify RSA, you can check if the encryption and decryption processes are inverses of each other. This means:
- If you encrypt a message **m** and then decrypt it using the private key, you should get back the original message **m**.

### Verification Steps:
1. **Encryption**:  
   - Take the plaintext **m** and encrypt it using the public key:  
     \[
     c = m^e \ (\text{mod} \ n)
     \]
   
2. **Decryption**:  
   - Take the ciphertext **c** and decrypt it using the private key:  
     \[
     m = c^d \ (\text{mod} \ n)
     \]

3. **Check the Result**:  
   - If **m** (original message) equals the decrypted message, then RSA works correctly.

### Example:

- **Plaintext (m)** = `"HI"`, Public Key = `(3233, 17)`, Private Key = `(3233, 2753)`
  
1. **Encrypt the message** `"HI"` → `2201`.
2. **Decrypt the ciphertext** `2201` → `"HI"`.

Since the decrypted message matches the original plaintext, RSA is verified.

---

### Summary of RSA Steps:
1. **Inputs**:
   - Message **m**.
   - Public key **(n, e)**.
2. **Process**:
   - Key Generation (for both encryption and decryption).
   - Encryption: \( c = m^e \ (\text{mod} \ n) \).
   - Decryption: \( m = c^d \ (\text{mod} \ n) \).
3. **Output**:
   - **Ciphertext** (encrypted message).
   - **Decrypted Message** (original message).
4. **Verification**:
   - Encryption and decryption should reverse each other, i.e., the decrypted message should equal the original plaintext.

---
The end!