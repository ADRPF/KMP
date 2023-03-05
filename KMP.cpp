// Algoritmo em C de implementa��o de KMP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char* pat, int M, int* lps);

// Imprimi os indices de ocorrrencia de pat em txt
void KMPSearch(char* pat, char* txt) //pat -> padr�o, txt -> texto
{
    const int M = strlen(pat); // M -> tamanho do padr�o
    int N = strlen(txt);       // N -> tamanho do texto

    // cria lps que armazenar� o maior prefixo-sufixo pr�prio
    int* lps = (int*)malloc(M * sizeof(int));

    //Preprocessa o padr�o (calcula o array lps)
    computeLPSArray(pat, M, lps);

    int i = 0; // indice para txt
    int j = 0; // indice para pat
    while ((N - i) >= (M - j)) { // loop � verdadeiro enquanto o tamanho do texto for maior que o tamanho do padr�o
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found pattern at index %d ", i - j); // imprime a posi��o do padr�o encontrado
            j = lps[j - 1];                              // passa para o indice do padr�o o tamanho do prefixo-sufixo
        }else if (i < N && pat[j] != txt[i]) { // mismatch ap�s j compa��es
            // N�o compare caracteres em lps[0..j-1], eles ser�o iguais do mesmo jeito
            if (j != 0)
                j = lps[j - 1]; // enquanto j for diferente de zero verifica se os outros sufixos s�o poss�veis matches
            else
                i = i + 1;
        }
    }
}

void computeLPSArray(char* pat, int M, int* lps)
{
    // tamanho do �ltimo prefixo sufixo
    int len = 0;

    lps[0] = 0; // lps[0] � sempre 0

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            
            if (len != 0) {
                len = lps[len - 1];
                //note que n�o incremetamos i
            }
            else // (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main()
{
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";
    KMPSearch(pat, txt);
    return 0;
}