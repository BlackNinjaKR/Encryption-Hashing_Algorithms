# Encryption & Hashing

## 1. Encryption

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

### 1.1 Need for Encryption

Encryption exists because communication and storage happen in hostile environments. Cryptography assumes that:
- Attackers can observe traffic
- Attackers can copy data perfectly
- Attackers can replay messages
- Attackers can modify data
- Attackers may have massive computing power

### 1.2 What makes a good encryption algorithm

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