#include "hero.h"

int czy_istnieje(Hero* head, char* imie) {
    while (head) {
        if (strcmp(head->imie, imie) == 0) return 1;
        head = head->nastepny;
    }
    return 0;
}

Hero* dodaj(Hero* head, char* imie, char* rasa, char* klasa, int poziom, int reputacja, char* status) {
    if (czy_istnieje(head, imie)) {
        printf("\n[BLAD] Bohater o imieniu %s juz jest w rejestrze!\n", imie);
        return head;
    }
    Hero* nowy = (Hero*)malloc(sizeof(Hero));
    if (!nowy) return head;
    strncpy(nowy->imie, imie, 100);
    strncpy(nowy->rasa, rasa, 49);
    strncpy(nowy->klasa, klasa, 49);
    nowy->poziom = poziom;
    nowy->reputacja = (reputacja > 100) ? 100 : (reputacja < 0 ? 0 : reputacja);
    strncpy(nowy->status, status, 19);
    nowy->nastepny = head; 
    return nowy;
}

void edytuj(Hero* head, char* imie) {
    while (head) {
        if (strcmp(head->imie, imie) == 0) {
            printf("\n--- EDYCJA BOHATERA: %s ---\n", imie);
            printf("Nowa rasa: "); scanf("%49s", head->rasa);
            printf("Nowa klasa: "); scanf("%49s", head->klasa);
            printf("Nowy poziom: "); scanf("%d", &head->poziom);
            printf("Nowa reputacja (0-100): "); scanf("%d", &head->reputacja);
            printf("Nowy status: "); scanf("%19s", head->status);
            printf("\n[SUKCES] Dane zaktualizowane.\n");
            return;
        }
        head = head->nastepny;
    }
    printf("\n[BLAD] Nie znaleziono bohatera %s.\n", imie);
}

Hero* usun(Hero* head, char* imie) {
    Hero *obecny = head, *poprzedni = NULL;
    while (obecny) {
        if (strcmp(obecny->imie, imie) == 0) {
            if (strcmp(obecny->status, "misja") == 0) {
                printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Odmowa: Bohater %s jest na misji i nie moze byc usuniety!\n", imie);
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                return head;
            }
            if (!poprzedni) head = obecny->nastepny;
            else poprzedni->nastepny = obecny->nastepny;
            free(obecny);
            printf("\n[INFO] %s zostal wyrejestrowany z Gildii.\n", imie);
            return head;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }
    printf("\n[BLAD] Brak bohatera %s w bazie.\n", imie);
    return head;
}

void znajdz(Hero* head, char* imieP, int minP) {
    int f = 0;
    printf("\n--- WYNIKI WYSZUKIWANIA ---\n");
    while (head) {
        if (strstr(head->imie, imieP) && head->poziom >= minP) {
            printf(" %-15s | %-12s | %-10s | Lvl: %-3d | Status: %s\n", head->imie, head->klasa, head->rasa, head->poziom, head->status);
            f = 1;
        }
        head = head->nastepny;
    }
    if (!f) printf("Nie znaleziono bohatera spelniajacego kryteria.\n");
}

void sortuj(Hero* head) {
    if (!head || !head->nastepny) return;
    int zamiana;
    Hero *p1, *ost = NULL;
    do {
        zamiana = 0;
        p1 = head;
        while (p1->nastepny != ost) {
            if (strcmp(p1->imie, p1->nastepny->imie) > 0) {
                Hero temp;
                memmove(temp.imie, p1->imie, 101);
                memmove(temp.rasa, p1->rasa, 50);
                memmove(temp.klasa, p1->klasa, 50);
                temp.poziom = p1->poziom; temp.reputacja = p1->reputacja;
                memmove(temp.status, p1->status, 20);

                memmove(p1->imie, p1->nastepny->imie, 101);
                memmove(p1->rasa, p1->nastepny->rasa, 50);
                memmove(p1->klasa, p1->nastepny->klasa, 50);
                p1->poziom = p1->nastepny->poziom; p1->reputacja = p1->nastepny->reputacja;
                memmove(p1->status, p1->nastepny->status, 20);

                memmove(p1->nastepny->imie, temp.imie, 101);
                memmove(p1->nastepny->rasa, temp.rasa, 50);
                memmove(p1->nastepny->klasa, temp.klasa, 50);
                p1->nastepny->poziom = temp.poziom; p1->nastepny->reputacja = temp.reputacja;
                memmove(p1->nastepny->status, temp.status, 20);
                zamiana = 1;
            }
            p1 = p1->nastepny;
        }
        ost = p1;
    } while (zamiana);
}

void wyswietl(Hero* head) {
    if(!head) { printf("\nRejestr Gildii jest pusty.\n"); return; }
    printf("\n%-15s | %-12s | %-12s | %-4s | %-4s | %-12s\n", "IMIE", "RASA", "KLASA", "LVL", "REP", "STATUS");
    printf("------------------------------------------------------------------------------\n");
    while (head) {
        printf("%-15s | %-12s | %-12s | %-4d | %-4d | %-12s\n", head->imie, head->rasa, head->klasa, head->poziom, head->reputacja, head->status);
        head = head->nastepny;
    }
}

void zapisz(Hero* head, const char* plik) {
    FILE* f = fopen(plik, "w");
    if (!f) return;
    while (head) {
        fprintf(f, "%s;%s;%s;%d;%d;%s\n", head->imie, head->rasa, head->klasa, head->poziom, head->reputacja, head->status);
        head = head->nastepny;
    }
    fclose(f);
}

Hero* wczytaj(const char* plik) {
    FILE* f = fopen(plik, "r");
    if (!f) return NULL;
    Hero* head = NULL;
    char i[101], r[50], k[50], s[20];
    int p, rep;
    while (fscanf(f, " %100[^;];%49[^;];%49[^;];%d;%d;%19[^\n]", i, r, k, &p, &rep, s) == 6) {
        head = dodaj(head, i, r, k, p, rep, s);
    }
    fclose(f);
    return head;
}

void zwolnij_liste(Hero* head) {
    while (head) {
        Hero* tmp = head;
        head = head->nastepny;
        free(tmp);
    }
}