
#include <stdio.h>
#include <stdlib.h>
#include "Kmp.c"
void leConsole(){
    char texto[10000];
    char padrao[50];
    fgets(texto, sizeof(texto), stdin);
    int numeroDePadroes = 0 ;
    scanf("%d", &numeroDePadroes);
    scanf (" %50[^\n]", padrao);
    int iterador = 0;
    separaPalavras(texto, padrao,numeroDePadroes,&iterador);
}
int main(){
    leConsole();
    printf("\n");
}
