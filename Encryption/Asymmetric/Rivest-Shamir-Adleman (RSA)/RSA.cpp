#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// const long Prime1 = 18121;
// const long Prime2 = 37649;
const long Prime1 = 239;
const long Prime2 = 167;
const long n = Prime1 * Prime2;
const long Phi_n = (Prime1 - 1) * (Prime2 - 1);

//return factors of a number
vector<int> factorize(int n)
{
    vector<int> factors;
    for (int i = 1; i <= n; ++i)
        if (n % i == 0)
            factors.push_back(i);
    return factors;
}

// Check if a number is prime
bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

//Check if two numbers are coprime
long gcd(long a, long b)
{
    while (b != 0)
    {
        long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool are_coprime(int a, int b)
{
    return gcd(a, b) == 1;
}

//Function to select e
long select_e(long Phi_n)
{
    long e = 3; // Start with a small odd prime
    while (e < Phi_n)
    {
        if (are_coprime(e, Phi_n))
            return e;
        e += 2; // Increment by 2 to ensure e remains odd
    }
    throw runtime_error("Failed to find suitable e");
}

//Function to compute mod inverse
long mod_inverse(long e, long phi)
{
    try
    {
        for (long x = 1; x < phi; x++)
            if (e*x % phi == 1)
                return x;
        throw runtime_error("Modular inverse does not exist");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return -1;
}

// Modular exponentiation: computes (base^exp) % mod efficiently
// Uses binary exponentiation (exponentiation by squaring) to avoid overflow
// and reduce computation time from O(exp) to O(log exp)
long modexp(long base, long exp, long mod)
{
    long result = 1;
    base %= mod;  // Reduce base to prevent overflow in initial multiplication

    while (exp > 0) {
        // If the least significant bit of exp is 1, multiply result by current base
        if (exp & 1)
            result = (result * base) % mod;
        // Square the base and reduce modulo to keep values manageable
        base = (base * base) % mod;
        // Right shift exp by 1 bit (equivalent to dividing by 2)
        exp >>= 1;
    }
    return result;
}


double encrypt(long message, long e, long n)
{
    return modexp(message, e, n);
}

double decrypt(long ciphertext, long d, long n)
{
    return modexp(ciphertext, d, n);
}

// Main function
int main()
{
    // Choose e such that 1 < e < Phi_n and e is coprime to Phi_n
    const long e = select_e(Phi_n);
    if (gcd(e, Phi_n) != 1)
        throw runtime_error("Bad e");
    cout << "Public key (e, n): (" << e << ", " << n << ")" << endl;

    const long d = mod_inverse(e, Phi_n);
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;

    string message_input;
    cout << "Enter a message: ";
    getline(cin, message_input);
    cout << "Original message: " << message_input << endl;
    
    // Transform to character array
    vector<char> message_chars(message_input.begin(), message_input.end());
    // Convert character array to number array
    vector<long> message_numbers;
    for (char c : message_chars)
        message_numbers.push_back(static_cast<long>(c));

    vector<long> encrypted_messages;
    for (long msg_num : message_numbers)
    {
        if (msg_num >= n)
        {
            cerr << "Message number " << msg_num << " is too large for the current n." << endl;
            return 1;
        }
        long encrypted = encrypt(msg_num, e, n);
        encrypted_messages.push_back(encrypted);
    }

    cout << "Encrypted message numbers: ";
    for (long enc_msg : encrypted_messages)
        cout << enc_msg << " ";
    cout << endl;

    vector<char> decrypted_messages;
    for (long enc_msg : encrypted_messages)
    {
        long decrypted = decrypt(enc_msg, d, n);
        decrypted_messages.push_back(static_cast<char>(decrypted));
    }
    cout << "Decrypted message numbers: ";
    for (char dec_msg : decrypted_messages)
        cout << dec_msg << " ";
    cout << endl;
};