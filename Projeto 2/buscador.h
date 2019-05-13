#ifndef BUSCADOR_H
#define BUSCADOR_H

// Busca por sequencia, intuitivo
/**/
int *busca_sequencia(char *texto, char *padrao, int tamTexto, int tamPadrao){
	int *buscador = new int[tamTexto];
	bool find = false;
	for(int i = 0; i < tamTexto; i++){
		for(int j = 0; j < tamPadrao; j++){
			if(texto[i+j] != padrao[j]){
				find = false;
				break;
			} else { find = true; }
		}

		if(find){ buscador[i] = 1; }
		else { buscador[i] = 0; }
	}
	return buscador;
}

// Busca por sequencia, usando KMP
/**/

int *calcular_pi(char *P, int m){
    int *pi = new int[m];
    int k, l;

    pi[0] = 0;
    
    for (int i = 1; i < m; i++){
        k = i - 1;
        while (true){
            l = pi[k];
            if (l == 0){
                if (P[0] == P[i]){
                    pi[i] = 1;
                    break;
                } else {
                    pi[i] = 0;
                    break;
                }
            }else{
                if (P[i] == P[l]){
                    pi[i] = l + 1;
                    break;
                }else k = l - 1;
            }
            
        }
        
    }
    return pi;
}

int *kmp(char *T, char *P, int n, int m){
    int *pi = calcular_pi(P, m);

    int *list = new int[n];
    for (int i = 0; i < n; i++)
        list[i] = 0;
    
    int i = 0, j = 0;

    while (i < n) {
        if (T[i] != P[j]) {
            if (j == 0) {
                ++i;
            } else j = pi[j - 1];
        } else {
            if (j == m - 1) {
                list[i - j] = 1;
                j = pi[j];
                ++i;
            } else {
                ++i; ++j;
            }
        }
    }
    return list;
}

#endif