#include<iostream>
#include<cmath>
#include<string>

using namespace std;

const long long p = 467; // prime number
const long long g = 2; // primitive root modulo p
const long long priv_key = 6; // private key of the user

long long power(long long base, long long exp, long long mod)
{
    if (exp == 0)
        return 1;
    else if (exp == 1)
        return base % mod;
    
    // Optimized approach using exponentiation by squaring
    long long result = 1;
    if (base >= mod)
        base = base % mod;
    while (exp > 0)
    {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1)
            result = (result * base) % mod;
        // Now exp must be even
        exp /= 2; // Floor division (Integer division)
        base = (base * base) % mod;
    }
    return result;
}

int random_generator(long long p)
{
    return rand() % (p - 2) + 1;
}

long long* encrypt(long long message, long long intermediate_key)
{
    long long k = random_generator(p);
    long long c1 = power(g, k, p);
    long long c2 = (message * power(intermediate_key, k, p)) % p;
    long long* cipher = new long long[2];
    cipher[0] = c1;
    cipher[1] = c2;
    return cipher;
}

long long decrypt(long long* cipher, long long key)
{
    long long c1 = cipher[0];
    long long c2 = cipher[1];
    long long message = (c2 * power(c1, p - 1 - key, p)) % p;
    return message;
}

long long* str_to_ascii(string str)
{
    long long* ascii_arr = new long long[str.length()];
    for (size_t i = 0; i < str.length(); i++)
        ascii_arr[i] = (long long)str[i];
    return ascii_arr;
}

string ascii_to_str(long long* ascii_arr, size_t length)
{
    string str = "";
    for (size_t i = 0; i < length; i++)
        str += (char)ascii_arr[i];
    return str;
}

int main()
{
    long long intermediate_key = power(g, priv_key, p);
    string message = "Hi! This is Elgamal implementation in C++";
    long long* ascii_arr = str_to_ascii(message);
    size_t length = message.length();
    long long** cipher_arr = new long long*[length];
    for (size_t i = 0; i < length; i++)
        cipher_arr[i] = encrypt(ascii_arr[i], intermediate_key);
    
    cout << "Cipher Text: ";
    for (size_t i = 0; i < length; i++)
        cout << "(" << cipher_arr[i][0] << ", " << cipher_arr[i][1] << ")";

    string decrypted_message = "";
    for (size_t i = 0; i < length; i++)
    {
        long long decrypted_char = decrypt(cipher_arr[i], priv_key);
        decrypted_message += (char)((int)decrypted_char);
    }
    
    cout << "\n" << "Decrypted Message: " << decrypted_message << endl;

    delete[] ascii_arr;
    for (size_t i = 0; i < length; i++)
        delete[] cipher_arr[i];
    delete[] cipher_arr;

    return 0;
}