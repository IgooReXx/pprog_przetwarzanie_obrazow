#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"
#include"opcje.h"
#define MAX 512       
#define DL_LINII 1024
#define B_BLWARTOSCI -1


int zmiana_poziomowpgm(t_obraz *obraz,t_opcje *opcje, int *zamiana)
{
  int minL =opcje->minL;  /*Pomocnicze zmienne okreslane przez uzytkownika w zakresie prawdziwych maksymalnych wartosci.*/
  int maxL =opcje->maxL;

  if (minL > obraz->odcieni || minL< 0 || maxL > obraz->odcieni || maxL < 0 || minL>maxL)
  {
      fprintf(stderr,"%d\n",B_BLWARTOSCI);
      *zamiana = 0;
      return -1;
  }
  
  for(int i=0; i<obraz->wymy; i++)    /*Operacja zamiany poziomow.*/
  {
    for(int j=0; j<obraz->wymx; j++)
    {
      if(obraz->obrazek[i][j]<=minL)
      {
        obraz->obrazek[i][j]=0;
      }
      else if(obraz->obrazek[i][j]>minL && obraz->obrazek[i][j]<maxL)
      {
        obraz->obrazek[i][j]=((obraz->obrazek[i][j]-minL)*(obraz->odcieni/(maxL-minL)));
      }
      else
      {
        obraz->obrazek[i][j]=obraz->odcieni;
      }

    }
  }
  return 1;
}
