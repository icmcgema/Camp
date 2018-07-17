#include <bits/stdc++.h>

#define pb push_back

using namespace std;
const int N = 100007;

struct no {
	int nxt[10];
};

int ptr = 0;
no trie[N];

int cmp(string & a, string & b) {
	return a.size() > b.size();
}

// Retorna se a string s nao eh prefixo de ninguem
bool add(string & s) {
	int cur = 0;
	for(int i = 0; i < s.size(); ++i) {
		int j = s[i] - '0';
		if(trie[cur].nxt[j] == 0) { // nao ha nenhum nó ali
			trie[cur].nxt[j] = ++ptr;
		}
		cur = trie[cur].nxt[j];
	}
 	
 	// Se o ptr for igual ao cur, quer dizer que o noh de fim eh um novo noh, e ele nao eh usado por nenhuma outra string
 	// Logo, a string s nao eh prefixo de nenhuma outra
	return ptr == cur;
}

int main() {
	int t;
	cin >> t;

	while(t--) {
		int n;
		cin >> n;

		vector<string> v;
		for(int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			v.pb(s);
		}

		sort(v.begin(), v.end(), cmp); // Ordena as strings de maiores tamanhos para menores

		int flag = 0;
		for(int i = 0; i < n; ++i) {
			if(add(v[i]) == false) flag = 1;
		}

		cout << (flag? "NO" : "YES") << endl;

		// Limpa a trie
		memset(trie, 0, sizeof trie);
		ptr = 0;
	}


}