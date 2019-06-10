#ifndef BUSCADOR_H
#define BUSCADOR_H

// Busca por sequencia, intuitivo
/*Ao encontrar a sequencia no texto igual ao padrão guarda a posição que isso aconteceu, 
* para dizer que ali tem uma ocorrencia.
*/
void *busca_sequencia(const char *texto, const char *padrao, int *ocorrencia){
    bool achou = false;
	for(int i = 0; texto[i] != '\0'; i++){
        achou = true;
		for(int j = 0; padrao[j] != '\0'; j++){
			if(texto[i+j] != padrao[j]){ achou = false; break; }
		}
		if(achou){ *ocorrencia = i; ocorrencia++; }
	}
    *ocorrencia = -1;
}

// Calculo do PI para ser usado no KMP
/**/
int *calcular_pi(const char *padrao){
    const char *aux = padrao;
    int m = 0;
    while (*aux != '\0'){ m++; aux++; }

    int *pi = new int[m];
    int k, l;

    pi[0] = 0;
    for (int i = 1; i < m; i++){
        k = i - 1;
        while (true){
            l = pi[k];
            if (l == 0){
                if (padrao[0] == padrao[i]){ pi[i] = 1; break; } 
                else { pi[i] = 0; break; }
            } else {
                if (padrao[i] == padrao[l]){ pi[i] = l + 1; break; } 
                else k = l - 1;
            }    
        }
    }

    return pi;
}

// Busca por sequencia, usando KMP
/*Faz alguma coisa
* Recebe: T (Texto), P (Padrão), ocorrencias(Vetor com a posição em que ocorre um padrão)
*/
void *kmp(const char *T, const char *P, int *ocorrencias){
    int *pi = calcular_pi(P);

    int i = 0, j = 0;

    while (T[i] != '\0') {
        if (T[i] != P[j]) {
            if (j == 0) {
                ++i;
            } else j = pi[j - 1];
        } else {
            if (P[j+1] != '\0') {
                *ocorrencias = i - j;
                ++ocorrencias;
                j = pi[j];
                ++i;
            } else {
                ++i; ++j;
            }
        }
    }
    *ocorrencias = -1;
}

#endif