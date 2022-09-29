#include "Trie.h"


Trie::Node::Node() :isEndOfWord(false)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		children[i] = nullptr;
	}
}

Trie::Node::~Node()
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (children[i]) {
			delete children[i];
		}
	}
}


Trie::Trie() : root(new Node)
{
}

Trie::~Trie()
{
	delete root;
}

void Trie::addWord(string key)
{
	Node* current = root;
	for (char c : key) {
		if (!current->children[c - 'a']) {
			current->children[c - 'a'] = new Node;
		}
		current = current->children[c - 'a'];
	}
	current->isEndOfWord = true;
}

void Trie::initialize(string filename)
{
	fstream file;
	file.open(filename, ios::in);
	if (!file) {
		throw exception("ERROR: dictionary file not found");
	} else {
		while (!file.eof()) {
			string word;
			getline(file, word);
			addWord(word);
		}
	}
}

Trie::Node* Trie::findText(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	Node* current = root;
	for (char c : text) {
		if (!current->children[c - 'a']) {
			return nullptr;
		}
		else {
			current = current->children[c - 'a'];
		}
	}
	return current;
}

vector<string> Trie::autoComplete(string text)
{
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	vector<string> answer;
	Node* current = findText(text);
	if (!current) {
		answer.push_back("Text not found in dictionary");
		return answer;
	}
	int count = 0;
	queue<Node*> qn;
	queue<string> qs;
	qn.push(current);
	qs.push(text);
	while (count < MAX_COMPLETE_COUNT && !qn.empty()) {
		current = qn.front();
		qn.pop();
		text = qs.front();
		qs.pop();
		if (current->isEndOfWord) {
			answer.push_back(text);
			count++;
		}
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (current->children[i]) {
				qn.push(current->children[i]);
				qs.push(text + char('a' + i));
			}
		}
	}
	return answer;
}