#define HERO_H
#ifndef HERO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hero {
    char name[101];
    char race[50];
    char class_name[50];
    int level;
    int reputation;
    char status[20];
    struct Hero* next;
} Hero;

Hero* add_hero(Hero* head, char* name, char* race, char* cls, int lvl, int rep, char* stat);
Hero* delete_hero(Hero* head, char* name);
void find_by_name(Hero* head, char* name);
void find_by_level(Hero* head, int min_lvl);
void sort_by_level(Hero* head); 
void display_all(Hero* head);

void save_to_file(Hero* head, const char* filename);
Hero* load_from_file(const char* filename);
void free_list(Hero* head);

#endif