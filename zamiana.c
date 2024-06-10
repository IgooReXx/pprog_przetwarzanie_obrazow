#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"
#include "opcje.h"

#define MAX 512       
#define DL_LINII 1024
#define B_BLWARTOSCI -1


int zmiana_poziomow(t_obraz *obraz, t_opcje *opcje, int *zamiana, int kolor)
{
  int minlum = opcje->minL;  /*Pomocnicze zmienne okreslane przez uzytkownika w zakresie prawdziwych maksymalnych wartosci.*/
  int maxlum = opcje->maxL;
  if (minlum > obraz->odcieni || minlum < 0 || maxlum > obraz->odcieni || maxlum < 0 || minlum>maxlum)
  {
      fprintf(stderr,"%d\n",B_BLWARTOSCI);
      *zamiana = 0;
      return -1;
  }
  
  for(int i=0; i<obraz->wymy; i++)    /*Operacja zamiany poziomow.*/
  {
    for(int j=0; j<obraz->wymx*3; j++)
    {
      if(j%3==kolor)
      {
      if(obraz->obrazek[i][j]<=minlum)
      {
        obraz->obrazek[i][j]=0;
      }
      else if(obraz->obrazek[i][j]>minlum && obraz->obrazek[i][j]<maxlum)
      {
        obraz->obrazek[i][j]=((obraz->obrazek[i][j]-minlum)*(obraz->odcieni/(maxlum-minlum)));
      }
      else
      {
        obraz->obrazek[i][j]=obraz->odcieni;
      }
      }

    }
  }
  *zamiana=1;
  return 1;
}
