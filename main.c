#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hero.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Blad: Podaj nazwe pliku bazy jako argument!\n");
        return 1;
    }

    char* filename = argv[1];
    Hero* list = load_from_file(filename);
    int choice;
    char n[101], r[50], c[50], s[20], search_n[101];
    int l, rep, min_l;

    do {
        printf("\n--- GILDIA BOHATEROW ---\n");
        printf("1. Dodaj bohatera\n");
        printf("2. Wyswietl wszystkich\n");
        printf("3. Usun bohatera\n");
        printf("4. Szukaj (nazwa + lvl)\n");
        printf("5. Sortuj po poziomie\n");
        printf("6. Zapisz i Wyjdz\n");
        printf("Wybor: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Imie: "); scanf("%s", n);
                printf("Rasa: "); scanf("%s", r);
                printf("Klasa: "); scanf("%s", c);
                printf("Poziom i Reputacja: "); scanf("%d %d", &l, &rep);
                printf("Status: "); scanf("%s", s);
                list = add_hero(list, n, r, c, l, rep, s);
                break;
            case 2:
                display_all(list);
                break;
            case 3:
                printf("Podaj imie do usuniecia: "); scanf("%s", n);
                list = delete_hero(list, n);
                break;
            case 4:
                printf("Fragment imienia: "); scanf("%s", search_n);
                printf("Minimalny poziom: "); scanf("%d", &min_l);
                find_hero(list, search_n, min_l);
                break;
            case 5:
                sort_by_level(list);
                display_all(list);
                break;
            case 6:
                save_to_file(list, filename);
                printf("Dane zapisane. Do widzenia!\n");
                break;
        }
    } while (choice != 6);

    free_list(list);
    return 0;
}