//
//  Kmp.h
//  ep2Aed
//
//  Created by Lucas Bordinhon Capalbo on 13/06/17.
//  Copyright © 2017 Lucas Bordinhon Capalbo. All rights reserved.
//

#ifndef Kmp_h
#define Kmp_h

#include <stdio.h>
#include <string.h>
#include <assert.h>


int *funcaoDeFalha(char* p);
int KMPMatch(char* texto , char* p, int * i, int * j);
int *ChamaKMP(char* texto , char* p , int numeroDePadroes,int *controle);
char *novaString(char* texto, int posicao);
char **split(char frase[], char separador);
void separaPalavras(char *texto, char *padrao, int numeroDePadroes, int *iterador);
#endif /* Kmp_h */
