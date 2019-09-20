#include <bits/stdc++.h>

using namespace std;

bool valid = 1;

struct node {
	node *next[26]; ///Указатели на сыновей
	int num;
	node() {
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
		num = 0;
	}	
};

node *root = new node();

int sons(node *cnt) { ///Подсчет количества сыновей
	int ans = 0;
	for (int i = 0; i < 26; i++) {
		if (cnt -> next[i] != nullptr) {
			++ans;
		}
	}
	return ans;
}

void insert(string& word) { ///Вставка
	node *cnt = root;
	for (int i = 0; i < int(word.size()); i++) {
		char ch = word[i];
		if (cnt -> next[ch - 'a'] == nullptr) {
			cnt -> next[ch - 'a'] = new node();
		}
		cnt = cnt -> next[ch - 'a'];
	}
	cnt -> num += 1; ///Количество, слов заканчивающихся здесь увеличваем на 1
}

int exist(string word) {  ///Количество, слов равное word
	node *cnt = root;
	for (int i = 0; i < int(word.size()); i++) {
		char ch = word[i];
		if (cnt -> next[ch - 'a'] == nullptr) {
			return false;
		}
		cnt = cnt -> next[ch - 'a'];
	}
	return (cnt -> num);
}

bool away(node *cnt, string word, int index) {  ///Удаление одного экзепляра из бора
	if (index == int(word.size())) {
		if ((cnt -> num) == 0) {
			return 0;	
		}
		if (valid) {
			cnt -> num -= 1;
			valid = 0;
			if (cnt -> num != 0) {
				return 0;
			}
		}
		return (sons(cnt) == 0);
	}
	char ch = word[index];
	node *tmp = cnt -> next[ch - 'a'];
	if (tmp == nullptr) {
		return 0;
	}
	bool must = away(tmp, word, index + 1);
	if (must) {
		cnt -> next[ch - 'a'] = nullptr;
		return (sons(cnt) == 0);
	}
	return 0;
}

int main() {
	int q;
	cin >> q;
	while(q--) {
		string type, s;
		cin >> type;
		if (type == "insert") {
			cin >> s;
			insert(s);
		} else if (type == "delete") {
			cin >> s;
			valid = 1;
			away(root, s, 0);
		} else if (type == "count") {
			cin >> s;
			cout << exist(s) << '\n';
		}
	}
	return 0;
}