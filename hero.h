#ifndef HERO_H
#define HERO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hero {
    char imie[101];
    char rasa[50];
    char klasa[50];
    int poziom;
    int reputacja;
    char status[20];
    struct Hero* nastepny;
} Hero;

Hero* dodaj(Hero* head, char* imie, char* rasa, char* klasa, int poziom, int reputacja, char* status);
Hero* usun(Hero* head, char* imie);
void edytuj(Hero* head, char* imie);
void znajdz(Hero* head, char* imieP, int minP);
void sortuj(Hero* head);
void wyswietl(Hero* head);
void zapisz(Hero* head, const char* plik);
Hero* wczytaj(const char* plik);
void zwolnij_liste(Hero* head);

#endif