#include "Ong.h"
#include <sstream>

// Constructors and destructor remain the same
Ong::Ong() : Cipher() {}
Ong::Ong(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}
Ong::~Ong() {}

// Helper functions remain the same
bool Ong::IsVowel(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = c + ('a' - 'A');
    }
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool Ong::IsPunct(char c) {
    if (c == ' ') return true;
    return (c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || 
            c == ':' || c == '\'' || c == '"' || c == '(' || c == ')' ||
            c == '[' || c == ']' || c == '{' || c == '}');
}

void Ong::Encrypt() {
    if (GetIsEncrypted()) return;
    
    string message = GetMessage();
    string encrypted;
    size_t messageLength = message.length();
    
    // Converted range-based for loop to index-based
    for (size_t i = 0; i < messageLength; i++) {
        char current = message[i];
        
        if (IsVowel(current)) {
            encrypted += current;
            if (i + 1 < messageLength && !IsPunct(message[i+1])) {
                encrypted += '-';
            }
        }
        else if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) {
            encrypted += current;
            encrypted += ong;
            if (i + 1 < messageLength && !IsPunct(message[i+1])) {
                encrypted += '-';
            }
        }
        else {
            encrypted += current;
        }
    }
    
    SetMessage(encrypted);
    ToggleEncrypted();
}

void Ong::Decrypt() {
    if (!GetIsEncrypted()) return;
    
    string message = GetMessage();
    string decrypted;
    size_t i = 0;
    size_t messageLength = message.length();
    
    while (i < messageLength) {
        char current = message[i];
        
        if (IsPunct(current)) {
            decrypted += current;
            i++;
        }
        else if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) {
            decrypted += current;
            i++;
            
            // Check for "ong" suffix
            if (i + 2 < messageLength && 
                (message[i] == 'o' || message[i] == 'O') &&
                (message[i+1] == 'n' || message[i+1] == 'N') &&
                (message[i+2] == 'g' || message[i+2] == 'G')) {
                i += 3;
            }
            
            // Skip dashes
            if (i < messageLength && message[i] == '-') {
                i++;
            }
        }
        else {
            i++;
        }
    }
    
    SetMessage(decrypted);
    ToggleEncrypted();
}

// ToString and FormatOutput remain unchanged
string Ong::ToString() { return "Ong"; }

string Ong::FormatOutput() {
    stringstream ss;
    ss << "o" << DELIMITER << (GetIsEncrypted() ? 1 : 0) << DELIMITER 
       << GetMessage() << DELIMITER << " ";
    return ss.str();
}
