#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encrypt(string plaintext, int key)
{
    string cipher = "";
    key = key % 26;
    
    for (char c : plaintext)
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            cipher += (c - base + key + 26) % 26 + base;
        }
        else
            cipher += c;
    return cipher;
}

string decrypt(string cipher, int key)
{
    return encrypt(cipher, -key);
}

int main()
{
    string plaintext;
    int key;
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    cout << "Enter the key (shift value): ";
    cin >> key;
    string cipher = encrypt(plaintext, key);
    cout << "Encrypted text: " << cipher << endl;
    string decrypted_text = decrypt(cipher, key);
    cout << "Decrypted text: " << decrypted_text << endl;

    return 0;
}