#include "CipherTool.h"
#include <fstream>
#include <sstream>

// Constructor
CipherTool::CipherTool(string filename) : m_filename(filename) {}

// Destructor
CipherTool::~CipherTool() {
    for (Cipher* cipher : m_ciphers) {
        delete cipher;
    }
    m_ciphers.clear();
}

// Converts string to boolean
bool CipherTool::StringToBoolean(string input) {
    return input == "1";
}

// Loads ciphers from file
void CipherTool::LoadFile() {
    ifstream inputFile(m_filename);
    if (!inputFile.is_open()) {
        cout << "Could not open file: " << m_filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string type, encrypted, message, extra;
        
        getline(ss, type, DELIMITER);
        getline(ss, encrypted, DELIMITER);
        getline(ss, message, DELIMITER);
        getline(ss, extra, DELIMITER);

        bool isEncrypted = StringToBoolean(encrypted);

        if (type == "a") {  // Atbash
            m_ciphers.push_back(new Atbash(message, isEncrypted));
        } 
        else if (type == "s") {  // Scytale
            int key = stoi(extra);
            m_ciphers.push_back(new Scytale(message, isEncrypted, key));
        } 
        else if (type == "o") {  // Ong
            m_ciphers.push_back(new Ong(message, isEncrypted));
        }
    }
    inputFile.close();
}

// Displays all ciphers
void CipherTool::DisplayCiphers() {
    for (size_t i = 0; i < m_ciphers.size(); i++) {
        cout << i + 1 << ". " << m_ciphers[i]->ToString() << ": " 
             << *m_ciphers[i] << endl;
    }
}

// Encrypts or decrypts all ciphers
void CipherTool::EncryptDecrypt(bool encrypt) {
    int encrypted = 0;
    int decrypted = 0;
    
    for (Cipher* cipher : m_ciphers) {
        if (encrypt) {
            if (!cipher->GetIsEncrypted()) {  // Only encrypt if not already encrypted
                cipher->Encrypt();
                encrypted++;
            }
        } else {
            if (cipher->GetIsEncrypted()) {  // Only decrypt if currently encrypted
                cipher->Decrypt();
                decrypted++;
            }
        }
    }
    

    if (encrypted != 0){
      cout << "Encrypted: " << encrypted << endl;
    }
    if (decrypted != 0) {
      cout << "Decrypted: " << decrypted << endl;
    }
    if (encrypted == 0 && decrypted == 0) {
      cout << "You cannot encrypt/decrypt anthing" << endl;

    }
}

// Exports ciphers to file
void CipherTool::Export() {
  string m_exportedfile;
    cout << "What name do you want to give to your exported file?" << endl;
    cin >> m_exportedfile;
    ofstream outputFile(m_exportedfile);
    if (!outputFile.is_open()) {
        cout << "Could not open file for writing: " << m_exportedfile << endl;
        return;
    }

    for (Cipher* cipher : m_ciphers) {
        outputFile << cipher->FormatOutput() << endl;
    }
    outputFile.close();
    cout << "Ciphers exported to " << m_exportedfile << endl;
}

// Displays menu and gets user choice
int CipherTool::Menu() {
    int choice;
    cout << "\n1. Display All Ciphers" << endl;
    cout << "2. Encrypt All Ciphers" << endl;
    cout << "3. Decrypt All Ciphers" << endl;
    cout << "4. Export All Ciphers" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Main program loop
void CipherTool::Start() {
    LoadFile();
    int choice;
    do {
        choice = Menu();
        switch (choice) {
            case 1:
                DisplayCiphers();
                break;
            case 2:
                EncryptDecrypt(true);
                break;
            case 3:
                EncryptDecrypt(false);
                break;
            case 4:
                Export();
                break;
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 5);
}
