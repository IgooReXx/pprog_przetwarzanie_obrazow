#pragma once
#include "struktura.h"
#include<stdlib.h>
void ppmtopgm(t_obraz *obraz)
{
  int **buf;
  buf = (int**)malloc(obraz->wymx*sizeof(int*));
  for(int k=0; k<obraz->wymy;k++)
  {
    buf[k]=(int*)malloc(obraz->wymx*sizeof(int));
  }
  for (int i=0;i<obraz->wymy;i++)
  {
    int g=0;
    for (int j=0;j<obraz->wymx;j++) 
    {
        fprintf(stderr,"%d\n",g);

        buf[i][j]= (obraz->obrazek[i][g]+obraz->obrazek[i][g+1]+obraz->obrazek[i][g+2])/3;
        g+=3;
    }
  }
  for(int k=0; k<obraz->wymy; k++)
  {
    free(obraz->obrazek[k]);
  }
  free(obraz->obrazek);

  obraz->obrazek=(int**)malloc(obraz->wymy*sizeof(int*));
    for(int k=0; k<obraz->wymy;k++)
    {
      obraz->obrazek[k]=(int*)malloc(obraz->wymx*sizeof(int));
    }

    for(int i=0; i<obraz->wymy;i++)
    {
        for(int j=0; j<obraz->wymx; j++)
        {
            obraz->obrazek[i][j]=buf[i][j];
        }
    }
    for(int k=0; k<obraz->wymy; k++)
  {
    free(buf[k]);
  }
  free(buf);
    obraz->nrmag=2;
}