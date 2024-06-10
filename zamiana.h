#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struktura.h"
#include "opcje.h"

#define MAX 512       
#define DL_LINII 1024 


int zmiana_poziomow(t_obraz *obraz, t_opcje *opcje, int *zamiana, int kolor);
