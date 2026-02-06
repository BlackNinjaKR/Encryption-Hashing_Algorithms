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

### 2.3 Mathametics

#### Modular Arithmetic

The division relationship ($a = q \times n + r$) has two inputs ($a$ and $n$) and two outputs ($q$ and $r$). In modular arithmetic, we are interested in only one of the outputs, the remainder $r$. In other words, we want to know what is the value of $r$ when we divide a by $n$. The **modulo** ($mod$) operator takes an integer $a$ from set $\mathbf{Z}$ and a positive modulus $n$. The operator then returns a *non-negative* residue/remainder $r$.

$$
E.g.:\quad 27\text{ }mod\text{ }5=2 \quad \quad 36\text{ }mod\text{ }12=0 \quad \quad -18\text{ }mod\text{ }14=10 \quad \quad -7\text{ }mod\text{ }10=3
$$

##### Set of Residues or Additive Group of Integers Modulo n ($Z_n$):

The result of the modulo operation with modulus $n$ is always an integer between $0$ and $(n-1)$:

$$

\boxed{Z_n = \{0,1,2,3,..,(n-1)\} }
$$
$$
Z_2 = \{0, 1\} \quad Z_6 = \{0, 1, 2, 3, 4, 5\} \quad Z_{11} = \{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10\}
$$

##### Multiplicative Group of Integers Modulo n ($Z_n^*$)

All natural numbers less than n which are coprime to n. It is subset of numbers coprime to n (GCD = 1).

$$
\boxed{\Zeta^*_n = \{x \in \Zeta_n | gcd(x,n) = 1\}}
$$

$$OR$$

$$
\boxed{\Zeta^*_n = \{x | 1 \le x \le n-1, gcd(x,n) = 1\}}
$$

$$Z_{10}^* = \{1,3,7,9\} \quad Z_6^* = \{1,5\} \quad Z_{12}^* = \{1,5,7,11\} \quad Z_{11}^* = \{1,2,3,4,5,6,7,8,9,10\}$$

##### Congruence:

In Cryptography we use congruency instead of equality since mapping $\mathbf{Z}$ to $\mathbf{Z_n}$ isn't one-to-one. Infinite members of $\mathbf{Z}$ can map to one member of $\mathbf{Z_n}$. For example, the result of $2\text{ }mod\text{ } 10 = 2$, $12\text{ } mod\text{ } 10 = 2$, $22 \text{ }mod\text{ } 2 = 2$ and so on. In modular arithmetic, integers like $2$, $12$ and $22$ are called congruent $mod$ $10$. To show that two integers are congruent, we use the **congruence operator** ($\equiv$).

##### Operations in $Z_n$:

$$
Addition:\text{ }(a+b)\text{ }mod\text{ }n = c\\
Substraction: \text{ }(a-b)\text{ }mod\text{ }n = c\\
Multiplication: \text{ }(a \times b)\text{ }mod\text{ }n = c
$$

##### Properties:

$$
\text{First Property: }(a+b)\text{ }mod\text{ }n = [(a\text{ }mod\text{ }n)+(b\text{ }mod\text{ }n)]\text{ }mod\text{ }n\\
\text{Second Property: }(a-b)\text{ }mod\text{ }n = [(a\text{ }mod\text{ }n)-(b\text{ }mod\text{ }n)]\text{ }mod\text{ }n\\
\text{Third Property: }(a\times b)\text{ }mod\text{ }n = [(a\text{ }mod\text{ }n)\times(b\text{ }mod\text{ }n)]\text{ }mod\text{ }n\\
10^n\text{ }mod\text{ }x=(10\text{ }mod\text{ }x)^n\text{ }mod\text{ }x
$$

##### Inverses:

###### Additive Inverse

$$
a+b\equiv 0\text{ }(mod\text{ }n)
$$

In modular arithmetic, each integer has an additive inverse. The sum of an integer and its additive inverse is congruent to 0 modulo $n$. The additive inverse can be calculated by $b = n - a$.


###### Multiplicative Inverse

$$
a\times b\equiv 1\text{ }(mod\text{ }n)
$$

In modular arithmetic, an integer may or may not have a multiplicative inverse. When it does, the product of the integer and its multiplicative inverse is congruent to $1 mod\text{ }n$. It can be proved that a has a multiplicative inverse in $Z_n$ if and only if $gcd (n, a) = 1$. In this case, $a$ and $n$ are said to be **relatively prime** or **coprime**.