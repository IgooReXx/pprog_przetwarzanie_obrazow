#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struktura.h"


#define MAX 512
#define DL_LINII 1024

int czytaj(FILE *plik_we, t_obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if  ((buf[0]!='P') || ((buf[1]!='2') && (buf[1]!='3')) || koniec) {  /* Czy jest magiczne "P2" lub "P3"? */
    fprintf(stderr,"Blad: To nie jest plik PPM\n");
    return(0);
  }
  else
  {
    if(buf[1]=='2')
    {
      obraz->nrmag=2;
    }
    else if(buf[1]=='3')
    {
      obraz->nrmag=3;
    }
    else
    {
      fprintf(stderr,"Blad wczytywania numeru magicznego");
    }
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&(obraz->wymx), &(obraz->wymy), &(obraz->odcieni))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  if(obraz->nrmag==2)
  {
    obraz->obrazek=(int**)malloc(obraz->wymy*sizeof(int*));
    for(int k=0; k<obraz->wymy;k++)
    {
      obraz->obrazek[k]=(int*)malloc(obraz->wymx*sizeof(int));
    }
    for (i=0;i<obraz->wymy;i++) 
    {
      for (j=0;j<obraz->wymx;j++)
      {
        if (fscanf(plik_we,"%d",&(obraz->obrazek[i][j]))!=1)
        {
	        fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
      }
    }
  }


  if(obraz->nrmag==3)
  {
  /* Definicja tablicy*/
  obraz->obrazek = (int**)malloc(obraz->wymx*sizeof(int*));
  for(int k=0; k<obraz->wymy;k++)
  {
    obraz->obrazek[k]=(int*)malloc(obraz->wymx*sizeof(int)*3);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_ppm*/
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx*3;j++) {
      if (fscanf(plik_we,"%d",&(obraz->obrazek[i][j]))!=1){
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  }
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                                   /* Zwroc liczbe wczytanych pikseli */

void nadpisz(FILE *plik_we,t_obraz *obraz, int *zapisano) 
{
  *zapisano = 1;
  if(obraz->nrmag==2)
  {
   fprintf(plik_we, "P2\n%d %d\n%d\n",obraz->wymx, obraz->wymy, obraz->odcieni);
  for (int i=0; i<(obraz->wymy); i++)
  {
    for (int j=0; j<obraz->wymx; j++)
    {
      fprintf(plik_we, "%d ", obraz->obrazek[i][j]);
    }
    fprintf(plik_we,"\n");
  }
  }
  else if(obraz->nrmag==3)
  {
  fprintf(plik_we, "P3\n%d %d\n%d\n",obraz->wymx, obraz->wymy, obraz->odcieni);
  for (int i=0; i<(obraz->wymy); i++)
  {
    for (int j=0; j<obraz->wymx*3; j++)
    {
      fprintf(plik_we, "%d ", obraz->obrazek[i][j]);
    }
    fprintf(plik_we,"\n");
  }
  }
}