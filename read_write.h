#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"


#define MAX 512
#define DL_LINII 1024

int czytaj(FILE *plik_we, t_obraz *obraz);
void nadpisz(FILE *plik_we,t_obraz *obraz, int *zapisano) ;

