# Encryption & Hashing

## 1. Introduction to Security

Security enables protection of information and systems from unauthorized access, use, disclosure or destruction. It srtrives to achieve Confidentiality, Integrity and Availibility (CIA triad).

### 1.1 Security Principles

#### Confidentiality

Ensure that only authorized users can access sensitive data. This is achieved via encryption, passwords and access control.

#### Integrity

Ensures data hasn't been altered, deleted or tampered with, guareenting it's authentic and unchanged ffrom its source. This is achieved by hasing and digital signatures. 

#### Availibility

Ensures authorized users can access nformation and systems when needed. It is achieved through redundancy (backup systems, load balancing), fast recovery (disaster recovery plans, failover), firewall and security softwares.

### 1.2 Cyptographic Methods

#### 1.2.1 Symmetric Key Cryptography

- It is also known as *Private Key Cryptography*.
- The sender first encrypts their message using the shared key.
- The receiver decrypts the ciphertext using the same shared key.

Advantages:
- It is fast and efficient for large amounts of data.
- It is simple to implement.

Disadvantages:
- Key distribution is difficult since both parties must securely share the same key.
- Less secure if the key is exposed.
- For $n$ number of connections, $n-1$ keys are required.

Examples: Data Encryption Standard (DES), Advanced Encryption Standard (AES), Blowfish, Rivest Cipher 4 (RC4) etc.

#### 1.2.2 Asymmetric Key Cryptography

- It is also known as *Public Key Cryptography*.
- It uses a pair of keys for encryption/decryption.
    - **Public Key**: Shared openly and is used for encryption.
    - **Private Key**: Kept secret and is used for decryption.
- Sender encrypts the message using the receiver's public key.
- Only the receiver can decrypt it using their private key.
    
Advantages:
- Enhanced security, since keys are not shared.
- Supports digital signatures & secure key exchange.

Disadvantages:
- Slower than symmetric key cryptography.
- Computationally intensive.

Examples: Rivest-Shamir-Adleman (RSA) etc.

## 2. Encryption

Encryption is a reversible mathematical transformation that converts readable data (plaintext) into an unintelligible form (ciphertext) using a secret parameter (key), such that without the key, recovering the plaintext is computationally infeasible.

Formally,

$$
C = E_K(P)
$$
$$
P = D_K(C)
$$

Where,
- $P$ = Plaintext
- $C$ = Ciphertext
- $E$ = Encryption Algorithm
- $D$ = Decryption Algorithm
- $K$ = Key

The essence of encryption is to transform information such that secrecy depends ONLY on a small secret (the key) instead of hiding the method. According to **Kerckhoffs's Principle**:

> A cryptosystem should be secure even if everything about the system, except the key, is public.

---

### 2.1 Need for Encryption

Encryption exists because communication and storage happen in hostile environments. Cryptography assumes that:
- Attackers can observe traffic
- Attackers can copy data perfectly
- Attackers can replay messages
- Attackers can modify data
- Attackers may have massive computing power

### 2.2 What makes a good encryption algorithm

Claude Shannon asked a fundamental question about *How do we mathematically hide the relationship between plaintext, ciphertext and the key?*

He answered it:
1. Hiding the structure
2. Destroying patterns
3. Preventing statistical inference

Thus, he formalized this using two strong cipher properties:

#### 1) **Confusion**

**Confusion makes the relationship between the key and the ciphertext as complex and nonlinear as possible.** In other words, even if an attacker knows the algorithm and the ciphertext, they should not be able to infer anything useful about the key.

Confusion is ensured in the following ways:
- Nonlinear substitutions
- S-boxes
- Modular arithmetic
- Bitwise nonlinear functions

#### 2) **Diffusion**

**Diffusion spreads the influence of each plaintext bit across many ciphertext bits where changing one bit of plaintext should change many bits of ciphertext.** This is done with the aim of destroying statistical structure, thereby preventing *frequency analysis*, *pattern recognition*, *known-plaintext attacks* and *structural leakage*.