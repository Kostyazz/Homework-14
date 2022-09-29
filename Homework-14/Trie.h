#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int ALPHABET_SIZE = 26;
const int MAX_COMPLETE_COUNT = 10;

class Trie
{
public:
	struct Node {
		Node();
		~Node();
		struct Node *children[ALPHABET_SIZE];
		bool isEndOfWord;
	};
	Trie();
	~Trie();
	void addWord(string key);
	void initialize(string filename);
	Node* findText(string text);
	vector<string> autoComplete(string text);
private:
	Node* root;
};

