#include<iostream>
#include<cmath>
#include<random>

using namespace std;

class DiffieHellman {
private:
    long long p; // prime number
    long long g; // primitive root modulo p
    long long key; // private key of the user

public:
    DiffieHellman(long long prime, long long generator)
    {
        p = prime;
        g = generator;
        key = 0;
    }

    void set_key(long long x)
    {
        key = x;
    }

    long long power(long long base, long long exp, long long mod)
    {
        if (exp == 0)
            return 1;
        else if (exp == 1)
            return base % mod;
        
        // else
        //     return (pow(base, exp) % mod);

        // Optimized approach using exponentiation by squaring
        long long result = 1;
        if (base >= mod)
            base = base % mod;
        while (exp > 0) {
            // If exp is odd, multiply base with result
            if (exp % 2 == 1)
                result = (result * base) % mod;
            // Now exp must be even
            exp /= 2; // Floor division (Integer division)
            base = (base * base) % mod;
        }
        return result;
    }

    long long compute_key()
    {
        long long public_key = power(g, key, p);
        return public_key;
    }

    long long compute_shared_secret(long long intermediate_key)
    {
        long long shared_secret = power(intermediate_key, key, p);
        return shared_secret;
    }
};

int main()
{
    long long prime = 10007; // A large prime number
    long long generator = 666; // A primitive root modulo prime

    DiffieHellman alice(prime, generator), bob(prime, generator);

    alice.set_key(53);
    bob.set_key(312);

    long long alice_public_key = alice.compute_key();
    long long bob_public_key = bob.compute_key();

    cout << "Alice's Public Key: " << alice_public_key << endl;
    cout << "Bob's Public Key: " << bob_public_key << endl;

    long long alice_shared_secret = alice.compute_shared_secret(bob_public_key);
    long long bob_shared_secret = bob.compute_shared_secret(alice_public_key);

    cout << "Alice's Shared Secret: " << alice_shared_secret << endl;
    cout << "Bob's Shared Secret: " << bob_shared_secret << endl;

    return 0;
}