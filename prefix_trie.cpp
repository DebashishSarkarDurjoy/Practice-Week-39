#include <iostream>
#include <unordered_map>
#include <vector>

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
    Node* root;

    void suggestions_rec(Node* node, vector<string> &suggestions_vector) {
        if (node->isTerminal) {
            suggestions_vector.push_back(node->word);
        }

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
            if (temp->m.count(c) == 0) {
                Node *newNode = new Node(c);
                temp->m[c] = newNode;
            }
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
        vector<string> suggestions_vector;

        Node *temp = this->root;
        for (char c: word) {
            if (temp->m.count(c) == 0) return;
            temp = temp->m[c];
        }

        this->suggestions_rec(temp, suggestions_vector);

        for (auto word: suggestions_vector) {
            cout << word << " ";
        }
        cout << endl;
    }
};

int main(void) {
    string words[] = {"apple", "ape", "no", "new", "not", "never", "always"};

    Trie t;
    for (string word: words) {
        t.insert(word);
    }

    string search_word;
    cin >> search_word;

    while (search_word != "!") {
        t.suggestions(search_word);

        if (!t.search(search_word)) t.insert(search_word);

        cin >> search_word;
    }

    return 0;
}
