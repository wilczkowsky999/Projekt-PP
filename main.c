#include "hero.h"

void czysc() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Blad! Podaj plik bazy danych jako argument.\n");
        return 1;
    }
    Hero* head = wczytaj(argv[1]);
    int opcja = 0;
    do {
        printf("\n==========================================");
        printf("\n    REJESTR GILDII POSZUKIWACZY PRZYGOD   ");
        printf("\n==========================================");
        printf("\n1. Rejestracja nowego czlonka");
        printf("\n2. Wyswietl pelna liste bohaterow");
        printf("\n3. Usun bohatera z ewidencji");
        printf("\n4. Modyfikuj dane bohatera");
        printf("\n5. Szukaj (po imieniu i poziomie)");
        printf("\n6. Sortuj liste alfabetycznie");
        printf("\n7. Zapisz i Wyjdz");
        printf("\n==========================================");
        printf("\nWybor: ");
        
        if (scanf("%d", &opcja) != 1) { czysc(); continue; }
        czysc();
        
        if (opcja == 1) {
            char i[101], r[50], k[50], s[20];
            int p, rep;
            printf("\n--- REJESTRACJA ---");
            printf("\nImie (unikalne): "); scanf("%100s", i); czysc();
            printf("Rasa (Czlowiek, Elf, Krasnolud, Ork, Tiefling): "); scanf("%49s", r); czysc();
            printf("Klasa (Wojownik, Mag, Kaplan, Lotrzyk, Lowca, Druid, Tropiciel, Alchemik, Bard): "); scanf("%49s", k); czysc();
            printf("Poziom: "); scanf("%d", &p); czysc();
            printf("Reputacja (0-100): "); scanf("%d", &rep); czysc();
            printf("Status (Aktywny, Misja, Ranny, Zaginiony, Zawieszony): "); scanf("%19s", s); czysc();
            head = dodaj(head, i, r, k, p, rep, s);
        } else if (opcja == 2) {
            wyswietl(head);
        } else if (opcja == 3) {
            char imie[101];
            printf("\nPodaj imie do usuniecia: "); scanf("%100s", imie);
            head = usun(head, imie);
        } else if (opcja == 4) {
            char imie[101];
            printf("\nPodaj imie do edycji: "); scanf("%100s", imie);
            edytuj(head, imie);
        } else if (opcja == 5) {
            char f[101]; int minP;
            printf("\nFraza imienia: "); scanf("%100s", f);
            printf("Minimalny poziom: "); scanf("%d", &minP);
            znajdz(head, f, minP);
        } else if (opcja == 6) {
            sortuj(head);
            printf("\n[INFO] Lista zostala posortowana alfabetycznie.");
        }
    } while (opcja != 7);

    zapisz(head, argv[1]);
    zwolnij_liste(head);
    printf("\n[INFO] Dane zapisane w %s. Powodzenia na szlaku!\n", argv[1]);
    return 0;
}