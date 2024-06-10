
#include "read_write.h"
#include "struktura.h"
#include "opcje.h"
#include "rozc.h"
#include "zamiana.h"
#include "display.h"
#include "zamianapgm.h"
#include "rozcpgm.h"
#include "ppmtopgm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    t_obraz piksele;
    t_opcje opcje;
    int zapisano=0;
    int zamiana=0;
    int kod_bledu=przetwarzaj_opcje(argc, argv, &opcje);
    fprintf(stderr,"%d\n",kod_bledu);
    czytaj(opcje.plik_we, &piksele);
    if(piksele.nrmag==3)
    {
    if(opcje.zamiana==1)
    {
        if(opcje.r==0)
        {
        int kolor=opcje.r;
        zmiana_poziomow(&piksele,&opcje,&zamiana, kolor);
        }
        if(opcje.g==1)
        {
        int kolor=opcje.g;
        zmiana_poziomow(&piksele,&opcje,&zamiana, kolor);
        }
        if(opcje.b==2)
        {
        int kolor=opcje.b;
        zmiana_poziomow(&piksele,&opcje,&zamiana, kolor);
        }
    }
    if(opcje.rozciagniecie==1)
    {
        if(opcje.r==0)
        {
        int kolor=opcje.r;
        rozciagniecie_histogramu(&piksele,kolor);
        }
        if(opcje.g==1)
        {
            int kolor=opcje.g;
            rozciagniecie_histogramu(&piksele,kolor);
        }
        if(opcje.b==2)
        {
            int kolor=opcje.b;
            rozciagniecie_histogramu(&piksele,kolor);
        }

    }
    }
    else if(piksele.nrmag==2)
    {
    if(opcje.zamiana==1)
    {
        zmiana_poziomowpgm(&piksele,&opcje,&zamiana);
    }
    if(opcje.rozciagniecie==1)
    {
       rozciagniecie_histogramupgm(&piksele);
    }   
    }
    if(opcje.s==-1)
    {
        ppmtopgm(&piksele);
    }

    nadpisz(opcje.plik_wy,&piksele,&zapisano);

    if(opcje.wyswietlenie==1)
    {
        wyswietl(opcje.nazwa_wyj);
    }
}