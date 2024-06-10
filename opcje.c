/********************************************************************/
/* COPYRIGHT (c) 2007-2020 KCiR                                     */
/* Zmodyfikowany kod zrodlowy opcje.c                               */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/

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

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->zamiana=0;
  wybor->rozciagniecie=0;
  wybor->minL=0;
  wybor->maxL=0;
  wybor->wyswietlenie=0;
  wybor->r=-1;
  wybor->g=0;
  wybor->b=0;
  wybor->s=0;
}

/*****************************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv                   */
/* i zapisuje je w strukturze wybor                                                      */
/* Skladnia opcji wywolania programu                                                     */
/*         program {[-i nazwa] [-o nazwa] [-z liczba liczba] [-r/g/b/s] [-h] [-d]}       */
/* Argumenty funkcji:                                                                    */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu                    */
/*         argv  -  tablica argumentow wywolania                                         */
/*         wybor -  struktura z informacjami o wywolanych opcjach                        */
/* PRE:                                                                                  */
/*      brak                                                                             */
/* POST:                                                                                 */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich                        */
/*      w strukturze wyb�r, do tego ustawia na 1 pola dla opcji, ktore                   */
/*	poprawnie wystapily w linii wywolania programu,                                      */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;                          */
/*	zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne                                 */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                                          */
/* UWAGA:                                                                                */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow                          */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL                          */
/*****************************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor) {
  int i, wminL, wmaxL;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	  wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	else                               /* otwieramy wskazany plik   */
	  wybor->plik_we=fopen(nazwa_pliku_we,"r");
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
    {
    wybor->nazwa_wyj=nazwa_pliku_wy;
	  wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
    }
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'z': {
      wybor->zamiana = 1;
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	      if (sscanf(argv[i],"%d",&wminL)==1)
	        wybor->minL=wminL;
        else
          return B_BRAKWARTOSCI;

        if(sscanf(argv[++i],"%d",&wmaxL)==1)
            wybor->maxL=wmaxL;
        else
            return B_BRAKWARTOSCI;
        } 
      else 
	      return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break; 
    }
    case 'r': {
      wybor->r=0;
      break;
    }
    case 'g': {
      wybor->g=1;
      break;
    }
    case 'b': {
      wybor->b=2;
      break;
    }
    case 's': {
      wybor->s=-1;
    }
    case 'h': {                 /* mamy wykonac konturowanie */
      wybor->rozciagniecie=1;
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
      break;
    }
    
    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  } /* koniec for */


  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}

