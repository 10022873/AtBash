#include "Atbash.h"
#include <sstream>
#include <cctype>

// Default Constructor
Atbash::Atbash() : Cipher() {}

// Overloaded Constructor
Atbash::Atbash(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}

// Destructor
Atbash::~Atbash() {
    // No specific cleanup needed for Atbash
}

// Encrypt function
void Atbash::Encrypt() {
    if (m_isEncrypted) {
        return; // Already encrypted
    }

    string result;
    for (char c : m_message) {
        if (isalpha(c)) {
            if (isupper(c)) {
                result += 'Z' - (c - 'A');
            } else {
                result += 'z' - (c - 'a');
            }
        } else {
            result += c; // Leave non-alphabetic characters as-is
        }
    }
    m_message = result;
    ToggleEncrypted();
}

// Decrypt function (same as Encrypt for Atbash)
void Atbash::Decrypt() {
    if (!m_isEncrypted) {
        return; // Already decrypted
    }
    // Atbash decryption is the same as encryption
    Encrypt(); // This will also toggle the encryption status
}

// ToString function
string Atbash::ToString() {
    return "Atbash";
}

// FormatOutput function
string Atbash::FormatOutput() {
    stringstream ss;
    ss << "a" << DELIMITER << m_isEncrypted << DELIMITER << m_message << DELIMITER;
    return ss.str();
}
