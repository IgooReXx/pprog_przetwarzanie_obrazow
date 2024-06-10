#pragma once
#include<stdio.h>
#include<string.h>
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  char *nazwa_wyj;
  int zamiana,rozciagniecie,wyswietlenie,r,g,b,s;      /* opcje */
  int minL,maxL;              /* wartosc progu dla opcji zamiany poziomow */ 
} t_opcje;
void wyzeruj_opcje(t_opcje * wybor);
int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor);

