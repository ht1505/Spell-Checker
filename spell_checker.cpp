#include <bits/stdc++.h>
using namespace std;

struct Node
{
    bool isEnd = false;
    unordered_map<char, Node *> child;
};

class Trie
{
private:
    Node *root;

public:
    Trie() { root = new Node(); }

    void insert(const string &s)
    {
        Node *curr = root;
        for (char c : s)
        {
            if (curr->child.find(c) == curr->child.end())
                curr->child[c] = new Node();
            curr = curr->child[c];
        }
        curr->isEnd = true;
    }

    bool find(const string &s)
    {
        Node *curr = root;
        for (char c : s)
        {
            if (curr->child.find(c) == curr->child.end())
                return false;
            curr = curr->child[c];
        }
        return curr->isEnd;
    }
};

int main()
{
    Trie ob;

    string filename = "word/Aword.csv";
    ifstream file;
    int k = 10;
    for (int i = 0; i < 26; i++)
    {
        file.open(filename);
        if (!file)
        {
            cerr << "Error: cannot open " << filename << endl;
            return 1;
        }
        cout << "Open: " << filename << endl;
        string s;
        while (getline(file, s))
        {
            if (s.size())
                s.pop_back();
            ob.insert(s);
        }

        file.close();
        filename[5]++;
    }

    while (true)
    {
        string s;
        cout << "Enter: ";
        cin >> s;
        if (ob.find(s))
            cout << "Correct" << endl;
        else
            cout << "Incorrect" << endl;
    }

    return 0;
}
