#include <bits/stdc++.h>

using namespace std;
const int N = 2000007; // N tem que ser 2 * 10^6 pois eh o tamanho maximo da string concatenada

int phi[N];

/* 
    A solucao do problema eh concatenar o prefixo com a string, usando um separador ('#', '!' ou qualquer caractere nao presente nas strings),
    e calcular a funcao phi em cima desta. Com isso, qualquer posicao p tal que phi[p] seja igual ao tamanho do prefixo significa que existe uma
    substring presente em ( p - b.size() + 1 )
*/

void calc_phi(string s) {
    phi[0] = phi[1] = 0;
    
    for(int i = 2; i <= (int) s.size(); i++) {
        int x = phi[i-1];
        
        while(x != 0 and s[x] != s[i-1]) {
            x = phi[x];
        }
        
        if(s[x] == s[i-1])
            phi[i] = x+1;
        else
            phi[i] = 0;
    }
}

int main() {
    int t;
    cin >> t;

    while(t--) {
        string a, b;
        cin >> a >> b;
        a = b + '#' + a; // concatena o prefixo com a string

        calc_phi(a);

        vector<int> ans; // vetor das posicoes
        for(int i = 0; i <= a.size(); ++i) {
            //  Se deu match, a posicao da substring na string concatenada eh j = i - b.size() + 1
            //  A posicao da substring na string original é k = j - b.size() - 1 (pois b.size() - 1 eh o tamanho do prefixo mais o separador)
            //  k = j - b.size() - 1 = i - b.size() + 1 - b.size() - 1 = i - 2 * b.size()
            if(phi[i] == b.size()) ans.push_back(i - 2 * b.size()); 
        }

        if(ans.size() == 0) cout << "Not Found\n";
        else {
            cout << ans.size() << endl;
            for(int i = 0; i < ans.size(); ++i) cout << (i? " " : "") << ans[i];
            cout << endl;
        }
        if(t) cout << endl;
    }
}