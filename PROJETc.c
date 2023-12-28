#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Structure pour repr�senter un voyageur
typedef struct {
    char nom[50];
    char prenom[50];
    char adresse[100];
    char email[50];
    int telephone;
} Voyageur;

// Structure pour repr�senter une r�servation
typedef struct {
    int numero;
    char destination[50];
    int nombrePlaces;
    float montant;
    char dateReservation[20];
    int dureeSejour;
    char moyenPaiement[30];
    Voyageur voyageur;
} Reservation;

// Structure pour repr�senter les d�tails d'un bus
typedef struct {
    char destination[50];
    int placesDisponibles;
    int numeroBus;
    char horaireDepart[20];
    char typeBus[20];
} BusDetails;

// Prototypes de fonctions
Voyageur creerVoyageur();
Reservation* creerReservation(int numero);
void afficherDetailsBus(BusDetails details[]);
void afficherReservation(Reservation *reservations, int nombreReservations);
void libererMemoire(Reservation *reservations, int nombreReservations);
void ModifierReservation(Reservation *reservations, int nombreReservations);
void annulerReservation(Reservation *reservations, int *nombreReservations);

int main() {
    Reservation *reservations = NULL;
    BusDetails listeDeBus[] = {
        {"Hammamet", 50, 101, "09:00", "Autobus"},
        {"Sidi bousaid", 40, 102, "10:30", "Minibus"},
        {"Tabarka", 40, 103, "12:00", "Autobus"},
        {"Djerba", 45, 104, "00:00", "Autobus"},
        {"Binzart", 30, 105, "12:00", "Minibus"},
        {"Douz", 55, 106, "08:00", "Autobus"},
        {"K�libia", 48, 107, "16:00", "Autobus"}
    };
    int nombreReservations = 0;
    int numeroReservation = 1;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Cr�er un nouveau compte voyageur\n");
        printf("2. Afficher les d�tails des bus\n");
        printf("3. Cr�er une nouvelle r�servation\n ");
        printf("4. Afficher  les d�tails d'une r�servation\n");
        printf("5. Modifier les d�tails d'une r�servation\n");
        printf("6. Annuler r�servation\n");
        printf("7. Quitter\n");

        int choix;
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                     reservations = realloc(reservations, (nombreReservations + 1) * sizeof(Reservation));
                     if (reservations == NULL) {
                            printf("Erreur d'allocation de m�moire.\n");
                            exit(EXIT_FAILURE);
    }

    // Cr�er un compte voyageur pour la r�servation actuelle
                     reservations[nombreReservations].voyageur = creerVoyageur();
                     nombreReservations++;

                       break;
            case 3:
                reservations = realloc(reservations, (nombreReservations + 1) * sizeof(Reservation));
                if (reservations == NULL) {
                    printf("Erreur d'allocation de m�moire.\n");
                    exit(EXIT_FAILURE);
                }
                reservations[nombreReservations] = *creerReservation(numeroReservation++);
                nombreReservations++;
                break;

            case 2:
                afficherDetailsBus(listeDeBus);
                break;
            case 4:
                afficherReservation(reservations, nombreReservations);
                break;
            case 5:
                 ModifierReservation(reservations, nombreReservations);
                break;
            case 6:
                annulerReservation(reservations, &nombreReservations);
                break;

            case 7:
                libererMemoire(reservations, nombreReservations);
                printf("Au revoir!\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    }

    return 0;
}
int estAlphabetique(const char *chaine) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (!isalpha(chaine[i])) {
            return 0;
        }
    }
    return 1;
}
void mettreAJourPlacesDisponibles(BusDetails *bus, Reservation *reservation, int nombreDeReservations) {

    bool busTrouve = false;

    for (int i = 0; i < nombreDeReservations; i++) {
        if (strcmp(bus->destination, reservation[i].destination) == 0) {
            bus->placesDisponibles -= reservation[i].nombrePlaces;
            busTrouve = true;
            break;
        }
    }

    if (!busTrouve) {
        printf("Erreur : Bus pour la destination %s non trouv�.\n", reservation->destination);
    }
}


// Fonction pour cr�er un nouveau compte voyageur
Voyageur creerVoyageur() {
    Voyageur nouveauVoyageur;
    do {
        printf("Entrez votre nom : ");
        scanf("%s", nouveauVoyageur.nom);

        if (!estAlphabetique(nouveauVoyageur.nom)) {
            printf("Le nom doit contenir uniquement des lettres. Veuillez saisir � nouveau.\n");
        }
    } while (!estAlphabetique(nouveauVoyageur.nom));
    do {
        printf("Entrez votre pr�nom : ");
        scanf("%s", nouveauVoyageur.prenom);

        if (!estAlphabetique(nouveauVoyageur.prenom)) {
            printf("Le pr�nom doit contenir uniquement des lettres. Veuillez saisir � nouveau.\n");
        }
    } while (!estAlphabetique(nouveauVoyageur.prenom));

    printf("Adresse: ");
    scanf("%s", nouveauVoyageur.adresse);
    printf("Email: ");
    scanf("%s", nouveauVoyageur.email);
    printf("Donnez le num�ro de t�l�phone ");
    scanf("%d",&nouveauVoyageur.telephone);
    return nouveauVoyageur;

}

// Fonction pour cr�er une nouvelle r�servation
Reservation* creerReservation(int numero) {
    Reservation *nouvelleReservation = malloc(sizeof(Reservation));
    if (nouvelleReservation == NULL) {
        printf("Erreur d'allocation de m�moire.\n");
        exit(EXIT_FAILURE);
    }

    nouvelleReservation->numero = numero;
    printf("Destination: ");
    scanf("%s", nouvelleReservation->destination);
    printf("Nombre de places: ");
    scanf("%d", &nouvelleReservation->nombrePlaces);
    printf("Montant: ");
    scanf("%f",&nouvelleReservation->montant);
    printf("Donnez la date de r�servation");
    scanf("%s",nouvelleReservation->dateReservation);
    printf("Donnez la dur�e de s�jour");
    scanf("%d",&nouvelleReservation->dureeSejour);
    printf("Donnez le moyen de paiement");
    scanf("%s",nouvelleReservation->moyenPaiement);

    return nouvelleReservation;
}

// Fonction pour afficher les d�tails des bus
void afficherDetailsBus(BusDetails *bus) {
    printf("D�tails des Bus :\n");

    for (int i = 0; i <7; i++) {
        printf("Bus #%d\n", bus[i].numeroBus);
        printf("Destination : %s\n", bus[i].destination);
        printf("Places disponibles : %d\n", bus[i].placesDisponibles);
        printf("Horaire de d�part : %s\n", bus[i].horaireDepart);
        printf("Type de bus : %s\n", bus[i].typeBus);
        printf("\n");
    }
}

// Fonction pour afficher  les d�tails d'une r�servation
void afficherReservation(Reservation *reservations, int nombreReservations) {
    int numeroReservation;
    printf("Num�ro de r�servation: ");
    scanf("%d", &numeroReservation);

    for (int i = 0; i < nombreReservations; ++i) {
        if (reservations[i].numero == numeroReservation) {
            printf("D�tails de la r�servation %d:\n", reservations[i].numero);
            printf("Voyageur: %s %s\n", reservations[i].voyageur.nom, reservations[i].voyageur.prenom);
            printf("Destination: %s\n", reservations[i].destination);
            printf("Nombre de places: %d\n", reservations[i].nombrePlaces);
            printf("Montant: %.2f\n", reservations[i].montant);
            printf("Date r�servation:%s\n",reservations[i].dateReservation);
            printf("Dur�e de s�jour: %d\n", reservations[i].dureeSejour);
            printf("Moyen de paiement:%s\n",reservations[i].moyenPaiement);



        }
    }
}
void ModifierReservation(Reservation *reservations, int nombreReservations) {
    int numeroReservation;
    printf("Num�ro de r�servation: ");
    scanf("%d", &numeroReservation);
            for (int i = 0; i < nombreReservations; ++i) {
                if (reservations[i].numero == numeroReservation) {
            printf("Nouvelle destination: ");
            scanf("%s", reservations[i].destination);
            printf("Nouveau nombre de places: ");
            scanf("%d", &reservations[i].nombrePlaces);
            printf("Nouveau montant: ");
            scanf("%f", &reservations[i].montant);
            printf("Nouvelle date de r�servation:");
            scanf("%s",reservations[i].dateReservation);
            printf("Nouvelle dur�e de s�jour:");
            scanf("%d",&reservations[i].dureeSejour);
            printf("Nouveau moyen de paiement:");
            scanf("%s",reservations[i].moyenPaiement);


}
            }
            }
void annulerReservation(Reservation *reservations, int *nombreReservations) {
    if (*nombreReservations == 0) {
        printf("Aucune r�servation n'a �t� effectu�e.\n");
    } else {
        int numeroReservation;
        printf("Entrez le num�ro de r�servation � annuler : ");
        scanf("%d", &numeroReservation);

        int index = -1;
        for (int i = 0; i < *nombreReservations; i++) {
            if (reservations[i].numero == numeroReservation) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // Supprimez la r�servation en d�calant les �l�ments du tableau
            for (int i = index; i < *nombreReservations - 1; i++) {
                reservations[i] = reservations[i + 1];
            }
            (*nombreReservations)--;
            printf("R�servation annul�e avec succ�s.\n");
        } else {
            printf("Aucune r�servation trouv�e avec le num�ro sp�cifi�.\n");
        }
    }
}

// Fonction pour lib�rer la m�moire allou�e pour les r�servations
void libererMemoire(Reservation *reservations, int nombreReservations) {
    for (int i = 0; i < nombreReservations; ++i) {
        free(&reservations[i]);
    }
    free(reservations);
}
