#include <iostream>
#include "Trie.h"

int main()
{
	Trie trie;
	try
	{
		cout << "Initializing... Please wait." << endl;
		trie.initialize("words_alpha.txt");
	}
	catch (exception ex) {
		cerr << ex.what();
		return 1;
	}

	cout << "Enter some english letters and program will show possible completions" << endl;
	while (1) {
		string text;
		getline(cin, text);
		vector<string> autos = trie.autoComplete(text);
		for (string a : autos) {
			cout << '>' << a << endl;
		}
	}
	return 0;
}
