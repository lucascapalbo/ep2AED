//
//  Kmp.c
//  ep2Aed
//
//  Created by Lucas Bordinhon Capalbo on 13/06/17.
//  Copyright © 2017 Lucas Bordinhon Capalbo. All rights reserved.
//

#include "Kmp.h"

int* funcaoDeFalha(char* p){
    int tamanhoPadrao = (int)strlen(p);
    //(int)(sizeof(p)/ sizeof(p[0]));
    int falha[tamanhoPadrao];
    int i =1;
    int j = 0;
    falha[0] = 0;
    while (i<tamanhoPadrao) {
        if (p[i] == p[j]) {
            falha[i]= j+1;
            i++;
            j++;
        }else if(j>0){
            j = falha[j-1];
        }else {
            falha[i]=0;
            i++;
        }
    }
    return falha;
}

int KMPMatch(char* texto , char* p , int * i, int * j){
    int tamanhoPadrao = (int)strlen(p);
    int tamanhoTexto =(int)strlen(texto);
    int* falha = funcaoDeFalha(p);
    *j = 0;
    while (*i < tamanhoTexto) {
        if(texto[*i] == p[*j]){ //match
            if(*j == tamanhoPadrao - 1){
                return (*i-*j);
            } else{
                (*i)++;
                (*j)++;
            }
        }
        else{ //mismatch
            if(*j>0){
                (*j) = falha[*j-1];
            } else{
                (*i)++;
            }
        }
    }
    return -1;
}

int* ChamaKMP(char* texto , char* p, int numeroDePadroes,int *controle){
    //chama o KMP match, para buscar todas as palavras no texto
    //Falta arrumar quando a palavra for a primeira;
    static int resposta[20];
    int iKmp = 0;
    int jKmp = 0;
    int iterador = 0;
    int i = KMPMatch(texto, p, &iKmp, &jKmp);
    if(texto[strlen(p)] == ' '){
        resposta[0] = i;
        iterador++;
    }
    else{
        resposta[0] = -1;
        iterador++;
    }
    while (i < strlen(texto) && i != -1){
        i = KMPMatch(texto, p , &iKmp,&jKmp);
        if(texto[i-1] == ' '){
            //eh realmente uma palavra, e nao apenas uma silaba de uma.
            resposta[iterador] = i;
            iterador++;
        }
    }
    *controle = iterador;
    return resposta;
}


char** split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    
    /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
    count++;
    
    result = malloc(sizeof(char*) * count);
    
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    
    return result;
}
void separaPalavras(char *texto, char *padrao, int numeroDePadroes, int *controle){
    //utiliza o split para separar as palavras, separando-as por espacos
    int i = 0;
    if(numeroDePadroes == 1){
        int *resposta = ChamaKMP(texto, padrao, numeroDePadroes, controle);
        while(i < *controle){
            if(resposta[0] == -1)//nao existe a palavra
                printf("%d", resposta[0]);
            else  if(resposta[i] != -1){
                printf("%d ", resposta[i]);
            }
            i++;
        }printf("\n");
    }else{
        char* palavras = strtok(padrao," ");
        while(palavras) {
            // puts(palavras);
            int *resposta = ChamaKMP(texto, palavras,numeroDePadroes, controle);
            while(i < *controle){
                if(resposta[0] == -1)//nao existe a palavra
                    printf("%d", resposta[0]);
                else if(resposta[i] != -1){
                    printf("%d ", resposta[i]);
                }
                i++;
            }printf("\n");
            i = 0;
            palavras = strtok(NULL, " ");
        }
    }
}

char* novaString(char* texto, int posicao){
    //retorna a nova string que deve ser buscada pelo kmp, excluindo a parte ja visitada
    char novoTexto[strlen(texto) - posicao];
    int i = 0;
    for (i = posicao; i < strlen(texto); i++) {
        novoTexto[i] = texto[i];
        printf("%c",novoTexto[i]);
    }
    return novoTexto;
}
