#include "Scytale.h"
#include <vector>
#include <sstream>

// Constructors and destructor
Scytale::Scytale() : Cipher(), m_key(0) {}
Scytale::Scytale(string message, bool isEncrypted, int key) 
    : Cipher(message, isEncrypted), m_key(key) {}
Scytale::~Scytale() {}

void Scytale::Encrypt() {
    if (GetIsEncrypted()) return;
    
    string message = GetMessage();
    size_t msgLength = message.length();
    if (m_key <= 0 || msgLength == 0) return;

    size_t rows = (msgLength + m_key - 1) / m_key; // Proper ceiling division
    
    vector<string> grid(rows, string(m_key, ' ')); // Initialize with spaces
    
    // Fill grid row-wise
    for (size_t i = 0; i < msgLength; ++i) {
        size_t row = i / m_key;
        size_t col = i % m_key;
        grid[row][col] = message[i]; // Preserve original character
    }
    
    // Read column-wise
    string encrypted;
    for (size_t col = 0; col < static_cast<size_t>(m_key); ++col) {
        for (size_t row = 0; row < rows; ++row) {
            encrypted += grid[row][col]; // Take all characters including spaces
        }
    }
    
    SetMessage(encrypted);
    ToggleEncrypted();
}

void Scytale::Decrypt() {
    if (!GetIsEncrypted()) return;
    
    string message = GetMessage();
    size_t msgLength = message.length();
    if (m_key <= 0 || msgLength == 0) return;

    size_t rows = (msgLength + m_key - 1) / m_key; // Same calculation as encrypt
    
    vector<string> grid(rows, string(m_key, ' ')); // Initialize with spaces
    
    // Fill grid column-wise
    size_t index = 0;
    for (size_t col = 0; col < static_cast<size_t>(m_key); ++col) {
        for (size_t row = 0; row < rows; ++row) {
            if (index < msgLength) {
                grid[row][col] = message[index++]; // Preserve all characters
            }
        }
    }
    
    // Read row-wise
    string decrypted;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < static_cast<size_t>(m_key); ++col) {
            decrypted += grid[row][col]; // Take all characters including spaces
        }
    }
    
    // Remove any padding spaces at the end (from grid initialization)
    while (!decrypted.empty() && decrypted.back() == ' ') {
        decrypted.pop_back();
    }
    
    SetMessage(decrypted);
    ToggleEncrypted();
}

string Scytale::ToString() { return "Scytale"; }

string Scytale::FormatOutput() {
    stringstream ss;
    ss << "s" << DELIMITER << (GetIsEncrypted() ? 1 : 0) << DELIMITER 
       << GetMessage() << DELIMITER << m_key;
    return ss.str();
}
