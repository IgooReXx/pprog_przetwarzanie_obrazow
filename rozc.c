#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"
#include "opcje.h"

#define MAX 512       
#define DL_LINII 1024 



void rozciagniecie_histogramu(t_obraz *obraz, int kolor)
{
  int minLum=0;
  int maxLum=0;
  
  for(int i=0; i<obraz->wymy; i++)    /*Petla przeszukujaca tablice*/
  {
    for(int j=0; j<obraz->wymx*3; j++)
    {

      if(j%3==kolor)
      {
        if(obraz->obrazek[i][j]>maxLum)
        {
          maxLum=obraz->obrazek[i][j];
        }
        else if(obraz->obrazek[i][j]<minLum)
        {
          minLum=obraz->obrazek[i][j];
        }
      }
    }
  }
  for(int i=0; i<obraz->wymy; i++) /*Operacja rozciagniecia histogramu.*/
  {
    for(int j=0; j<obraz->wymx*3; j++)
    {
      if(j%3==kolor)
      {
      obraz->obrazek[i][j]=((obraz->obrazek[i][j]-minLum)*(obraz->odcieni/(maxLum-minLum)));
      }
    }
  }
}
