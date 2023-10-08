#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node {
public:
    char data;
    unordered_map<char, Node*> m;
    bool isTerminal;
    string word;

    Node (char data) {
        this->data = data;
        this->isTerminal = false;
    }
};

class Trie {
private: 
    Node *root;

    void suggestions_rec(Node* node, vector<string> &suggestions_vector) {
        if (node->isTerminal) suggestions_vector.push_back(node->word);
        for (auto it = node->m.begin(); it != node->m.end(); it++) {
            suggestions_rec(it->second, suggestions_vector);
        }
    }

public:
    Trie() {
        this->root = new Node('\0');
    }

    void insert(string word) {
        Node *temp = this->root;
        for (char c: word) {
            if (temp->m.count(c) == 0) temp->m[c] = new Node('\0');
            temp = temp->m[c];
        }
        temp->isTerminal = true;
        temp->word = word;
    }

    bool search(string word) {
        Node *temp = this->root;
        for (char c: word) {
            if (temp->m.count(c) == 0) return false;
            temp = temp->m[c];
        }
        return temp->isTerminal;
    }

    
    void suggestions(string word) {
        Node *temp = this->root;
        for (char c: word) {
            if (temp->m.count(c) == 0) return;
            temp = temp->m[c];
        }

        vector<string> suggestions_vector;
        suggestions_rec(temp, suggestions_vector);

        for (string suggestion: suggestions_vector) {
            cout << suggestion << " ";
        }
        cout << endl;
        return;
    }

};

int main(void) {
    vector<string> words = {"ape", "apple", "hero", "always", "winning", "imperative"};

    Trie t;
    for (string word: words) {
        t.insert(word);
    }

    string input;
    cin >> input;
    while (input != "!") {
        t.suggestions(input);
        if (!t.search(input)) t.insert(input);
        cin >> input;
    }

    return 0;
}