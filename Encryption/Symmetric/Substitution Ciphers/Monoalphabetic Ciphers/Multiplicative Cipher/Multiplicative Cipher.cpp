#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int mul_inverse(int a, int m)
{
    a %= m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

int encrypt(char c, int key)
{
    if (!isalpha(c))
        return c;

    char base = isupper(c) ? 'A' : 'a';
    int x = c - base;
    int encrypted = (x * key) % 26;

    return base + encrypted;
}

int decrypt(char c, int key)
{
    if (!isalpha(c))
        return c;

    int inv = mul_inverse(key, 26);
    if (inv == -1)
    {
        cout << "Invalid key! No multiplicative inverse.\n";
        exit(1);
    }

    char base = isupper(c) ? 'A' : 'a';
    int x = c - base;
    int decrypted = (x * inv) % 26;

    return base + decrypted;
}

int main()
{
    string msg = "Hello, World!", cipher = "", decrypted = "";
    int key = 7;

    for (char c : msg)
        cipher += (char)encrypt(c, key);

    for (char c : cipher)
        decrypted += (char)decrypt(c, key);

    cout << "Cipher: " << cipher << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}