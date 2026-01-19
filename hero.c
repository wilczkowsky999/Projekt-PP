#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hero.h"

Hero* add_hero(Hero* head, char* name, char* race, char* cls, int lvl, int rep, char* stat) {
    Hero* new_hero = (Hero*)malloc(sizeof(Hero));
    if (!new_hero) return head;

    strncpy(new_hero->name, name, 100);
    strncpy(new_hero->race, race, 49);
    strncpy(new_hero->class_name, cls, 49);
    new_hero->level = lvl;
    new_hero->reputation = rep;
    strncpy(new_hero->status, stat, 19);
    
    new_hero->next = head; 
    return new_hero;
}

Hero* delete_hero(Hero* head, char* name) {
    Hero *curr = head, *prev = NULL;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (strcmp(curr->status, "na misji") == 0) {
                printf("!!! BLOKADA: Bohater %s jest na misji - nie mozna usunac!\n", name);
                return head;
            }
            if (!prev) head = curr->next;
            else prev->next = curr->next;
            free(curr);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    return head;
}

void find_hero(Hero* head, char* name_part, int min_lvl) {
    int found = 0;
    while (head) {
        if (strstr(head->name, name_part) != NULL && head->level >= min_lvl) {
            printf("- %s (%s, LVL: %d)\n", head->name, head->race, head->level);
            found++;
        }
        head = head->next;
    }
    if (found == 0) printf("Brak wynikow.\n");
}

void sort_by_level(Hero* head) {
    if (!head) return;
    int swapped;
    Hero *ptr1;
    Hero *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->level < ptr1->next->level) {
                int tempL = ptr1->level;
                ptr1->level = ptr1->next->level;
                ptr1->next->level = tempL;

                int tempR = ptr1->reputation;
                ptr1->reputation = ptr1->next->reputation;
                ptr1->next->reputation = tempR;

                char temp[101];
                strcpy(temp, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, temp);
                
                strcpy(temp, ptr1->race);
                strcpy(ptr1->race, ptr1->next->race);
                strcpy(ptr1->next->race, temp);

                strcpy(temp, ptr1->class_name);
                strcpy(ptr1->class_name, ptr1->next->class_name);
                strcpy(ptr1->next->class_name, temp);

                strcpy(temp, ptr1->status);
                strcpy(ptr1->status, ptr1->next->status);
                strcpy(ptr1->next->status, temp);
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void display_all(Hero* head) {
    if (!head) return;
    printf("\n%-20s | %-10s | %-5s | %-15s\n", "IMIE", "KLASA", "LVL", "STATUS");
    printf("------------------------------------------------------------\n");
    while (head) {
        printf("%-20s | %-10s | %-5d | %-15s\n", head->name, head->class_name, head->level, head->status);
        head = head->next;
    }
}

void save_to_file(Hero* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;
    while (head) {
        fprintf(f, "%s;%s;%s;%d;%d;%s\n", head->name, head->race, head->class_name, head->level, head->reputation, head->status);
        head = head->next;
    }
    fclose(f);
}

Hero* load_from_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;
    Hero* head = NULL;
    char n[101], r[50], c[50], s[20];
    int l, rep;
    while (fscanf(f, " %100[^;];%49[^;];%49[^;];%d;%d;%19[^\n]", n, r, c, &l, &rep, s) == 6) {
        head = add_hero(head, n, r, c, l, rep, s);
    }
    fclose(f);
    return head;
}

void free_list(Hero* head) {
    while (head) {
        Hero* tmp = head;
        head = head->next;
        free(tmp);
    }
}