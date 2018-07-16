#include <bits/stdc++.h>

#define pb push_back

using namespace std;
const int N = 1000007;

struct no {
	int nxt[26];
	int end; // 1 se existe uma string terminando ali, e 0 caso contrario
};

int ptr = 0;
no trie[N];

// Adiciona a string s na trie
void add(string & s) {
	int cur = 0;
	for(int i = 0; i < s.size(); ++i) {
		int j = s[i] - 'a';
		if(trie[cur].nxt[j] == 0) { // nao ha nenhum nó ali
			trie[cur].nxt[j] = ++ptr;
		}
		cur = trie[cur].nxt[j];
	}
	trie[cur].end = 1;
}

// Retorna o noh (da trie) em que a string s termina, ou -1 se ele nao existir.
int find_pos(string & s) {
	int cur = 0;

	for(int i = 0; i < s.size(); ++i) {
		int j = s[i] - 'a';
		if(trie[cur].nxt[j] == 0) return -1;
		cur = trie[cur].nxt[j];
	}
	return cur;
}

// imprime todas as palavras da trie que sao provenientes do noh p e retorna o numero de palavras impressas. String s eh a string atual
int words(string s, int p, int first) {
	int cnt = 0;
	if(!first and trie[p].end) {
		cnt++;
		cout << s << endl;
	}
	
	for(int i = 0; i < 26; ++i) {
		if(trie[p].nxt[i]) cnt += words(s + char('a' + i), trie[p].nxt[i], 0);
	}
	return cnt;
}

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		add(s);
	}

	int k; cin >> k;
	for(int i = 0; i < k; ++i) {
		string s;
		cin >> s;

		cout << "Case #" << i+1 << ":\n";
		int p = find_pos(s);
		int tot = p == -1? 0 : words(s, p, 1);
		if(tot == 0) {
			cout << "No match." << endl;
		}
	}

}