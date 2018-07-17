#include <bits/stdc++.h>

using namespace std;

const int N = 6120007;

struct no {
	int nxt[2];
	int cnt; // conta quantos caras passam por aquele bit
};

int ptr;
no trie[N];

/*
	A solucao deste problema eh adicionar os numeros na trie. Isso funciona olhando pra string binaria do numero (de 0s e 1s),
	e adicionando essa string. A partir disto, podemos responder uma query de forma gulosa. 
	Vamos supor que estamos resolvendo a query para x. Os primeiros elementos da trie correspondem aos bits mais significativos
	dos numeros contidos ali. Se o no atual da trie tiver os filhos 0 e 1, temos que escolher o oposto do bit de x, porque isso
	vai resultar em um bit 1 na resposta. Fazemos isso ate chegar ao final da trie.
*/

void add(int x) {
	int cur = 0;
	for(int i = 30; i >= 0; --i) {
		int bit = (x >> i)&1;
		if(trie[cur].nxt[bit] == 0) {
			trie[cur].nxt[bit] = ++ptr;
		}
		cur = trie[cur].nxt[bit];
		trie[cur].cnt++;
	}
}

void rem(int x) {
	int cur = 0, prev = 0;
	for(int i = 30; i >= 0; --i) {
		int bit = (x >> i)&1;
		cur = trie[cur].nxt[bit];
		trie[cur].cnt--;
		if(trie[cur].cnt == 0) {
			trie[prev].nxt[bit] = 0; //remove da trie
			break;
		}
		prev = cur;
	}
}

int query(int x) {
	int cur = 0, ans = 0;

	for(int i = 30; i >= 0; --i) {
		int bit = (x >> i)&1;
		if(trie[cur].nxt[!bit]) {
			ans |= (1 << i);
			cur = trie[cur].nxt[!bit];
		} else {
			cur = trie[cur].nxt[bit];
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	int q;
	cin >> q;

	add(0);

	while(q--) {
		char op;
		int x;
		cin >> op >> x;

		if(op == '+') {
			add(x); // adiciona o numero x na trie
		} else if(op == '-') {
			rem(x); // remove o numero x da trie
		} else {
			cout << query(x) << endl;
		}
	}
}