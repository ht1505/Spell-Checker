#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalpha(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

unordered_set<string> loadDictionary(const vector<string>& filenames) {
    unordered_set<string> dictionary;
    int filesProcessed = 0;
    int filesSkipped = 0;

    for (const string& filename : filenames) {
        ifstream file(filename);
        if (!file.is_open()) {
            filesSkipped++;
            continue;
        }

        string word;
        while (file >> word) {
            dictionary.insert(cleanWord(word));
        }
        file.close();
        filesProcessed++;
    }

    if (filesProcessed == 0) {
        cerr << "Error: Could not open any dictionary files." << endl;
        return dictionary;
    }

    return dictionary;
}

int main() {
    vector<string> dictionaryFiles = {
        "word/Aword.csv", "word/Bword.csv", "word/Cword.csv",
        "word/Dword.csv", "word/Eword.csv", "word/Fword.csv",
        "word/Gword.csv", "word/Hword.csv", "word/Iword.csv",
        "word/Jword.csv", "word/Kword.csv", "word/Lword.csv",
        "word/Mword.csv", "word/Nword.csv", "word/Oword.csv",
        "word/Pword.csv", "word/Qword.csv", "word/Rword.csv",
        "word/Sword.csv", "word/Tword.csv", "word/Uword.csv",
        "word/Vword.csv", "word/Wword.csv", "word/Xword.csv",
        "word/Yword.csv", "word/Zword.csv"
    };

    cout << "Loading dictionary..." << endl;
    unordered_set<string> dictionary = loadDictionary(dictionaryFiles);
    
    if (dictionary.empty()) {
        cerr << "Error: Dictionary loaded zero words. Please check your files and folder path." << endl;
        return 1;
    }
    
    cout << "Dictionary loaded with " << dictionary.size() << " words." << endl;

    string inputSentence;
    cout << "\nEnter a sentence to spell check (or 'quit' to exit):" << endl;

    while (getline(cin, inputSentence) && inputSentence != "quit") {
        if (inputSentence.empty()) {
            cout << "Please enter a sentence." << endl;
            continue;
        }
        stringstream ss(inputSentence);
        string word;
        bool hasMisspelled = false;

        while (ss >> word) {
            string cleaned = cleanWord(word);
            if (!cleaned.empty() && dictionary.find(cleaned) == dictionary.end()) {
                cout << "Misspelled word found: " << word << endl;
                hasMisspelled = true;
            }
        }

        if (!hasMisspelled) {
            cout << "All words are spelled correctly." << endl;
        }

        cout << "\n------------------------------------" << endl;
        cout << "Enter a new sentence (or 'quit' to exit):" << endl;
    }

    cout << "Exiting." << endl;
    return 0;
}
