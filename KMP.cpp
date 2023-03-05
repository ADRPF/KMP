// Algoritmo em C de implementação de KMP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(char* pat, int M, int* lps);

// Imprimi os indices de ocorrrencia de pat em txt
void KMPSearch(char* pat, char* txt) //pat -> padrão, txt -> texto
{
    const int M = strlen(pat); // M -> tamanho do padrão
    int N = strlen(txt);       // N -> tamanho do texto

    // cria lps que armazenará o maior prefixo-sufixo próprio
    int* lps = (int*)malloc(M * sizeof(int));

    //Preprocessa o padrão (calcula o array lps)
    computeLPSArray(pat, M, lps);

    int i = 0; // indice para txt
    int j = 0; // indice para pat
    while ((N - i) >= (M - j)) { // loop é verdadeiro enquanto o tamanho do texto for maior que o tamanho do padrão
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found pattern at index %d ", i - j); // imprime a posição do padrão encontrado
            j = lps[j - 1];                              // passa para o indice do padrão o tamanho do prefixo-sufixo
        }else if (i < N && pat[j] != txt[i]) { // mismatch após j compações
            // Não compare caracteres em lps[0..j-1], eles serão iguais do mesmo jeito
            if (j != 0)
                j = lps[j - 1]; // enquanto j for diferente de zero verifica se os outros sufixos são possíveis matches
            else
                i = i + 1;
        }
    }
}

void computeLPSArray(char* pat, int M, int* lps)
{
    // tamanho do último prefixo sufixo
    int len = 0;

    lps[0] = 0; // lps[0] é sempre 0

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
                //note que não incremetamos i
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