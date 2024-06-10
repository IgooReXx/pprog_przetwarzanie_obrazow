#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"struktura.h"

#define MAX 512       
#define DL_LINII 1024 



void rozciagniecie_histogramupgm(t_obraz *obraz)
{
  int minL =0;  /*Pomocnicze zmienne rzeczywistej maksymalnej i minimalnej jasnosci obrazu.*/
  int maxL =0;
  minL = obraz->obrazek[0][0];
  maxL = obraz->obrazek[0][0];
  for(int i=0; i<obraz->wymy; i++)    /*Petla przeszukujaca tablice*/
  {
    for(int j=1; j<obraz->wymx; j++)
    {
      if(obraz->obrazek[i][j]>maxL)
      {
        maxL=obraz->obrazek[i][j];
      }
      else if(obraz->obrazek[i][j]<minL)
      {
        minL=obraz->obrazek[i][j];
      }
    }
  }
  for(int i=0; i<obraz->wymy; i++) /*Operacja rozciagniecia histogramu.*/
  {
    for(int j=0; j<obraz->wymx; j++)
    {
      obraz->obrazek[i][j]=((obraz->obrazek[i][j]-minL)*(obraz->odcieni/(maxL-minL)));
    }
  }
}
