#include <iostream>
#include <memory>
#include <fstream>
#include "SHA256.h"
#include <sys/stat.h>

using namespace std;

// FUNCS
string read_file(const string &file_name);

void write_file(const string &file_name, const string &data);

string digest(string str, string key);

string sha256(const string &str);

void ui();


int main() {
    ui();
    return 0;
}

string read_file(const string &file_name) {
    string data;
    string line;
    ifstream file(file_name);
    while (getline(file, line)) {
        data += line + '\n';
    }
    file.close();
    cout << data.size() << " max: " << data.max_size();
    // for some reason it adds an extra character every time its written or read
    return data.substr(0, data.size() - 1);
}

void write_file(const string &file_name, const string &data) {
    ofstream file(file_name);
    file << data;
    file.close();
}

string digest(string str, string key) {
    for (int i = 0; i < str.size(); i++) {
        for (int l = 0; l < key.size(); l++) {
            str[i] = str[i] ^ key[l];
        }
    }
    return str;
}

string sha256(const string &str) {
    SHA256 sha;
    sha.update(str);
    uint8_t *digest = sha.digest();
    string hashed = SHA256::toString(digest);
    delete digest;
    return hashed;
}

void print_if_first_time(const char *file_name) {
    struct stat buffer{};
    if (stat(file_name, &buffer) != 0) {
        cout << "Hey seems like its your first time using this password manager\n";
        cout << "Don't be scared, just insert a master password bellow and follow instructions\n";
    }
}

void ui() {
    const char *SECRET_FILE = "secrets.txt";
    char const *SECRET_FILE_NOTEPAD_COMMAND = "notepad \"secrets.txt\"";

    print_if_first_time(SECRET_FILE);
    cout << "Password: ";
    string str;
    cin >> str;

    string password = sha256(str);
    string file_data = read_file(SECRET_FILE);
    write_file(SECRET_FILE, digest(file_data, password));
    cout << "Keep this window open, press enter to delete the contents of the file";
    cout << "When done editing passwords, save the file and close the notepad";
    system(SECRET_FILE_NOTEPAD_COMMAND);

    file_data = read_file(SECRET_FILE);
    write_file(SECRET_FILE, digest(file_data, password));
}
