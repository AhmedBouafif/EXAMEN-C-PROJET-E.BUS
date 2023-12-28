#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Structure pour représenter un voyageur
typedef struct {
    char nom[50];
    char prenom[50];
    char adresse[100];
    char email[50];
    int telephone;
} Voyageur;

// Structure pour représenter une réservation
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

// Structure pour représenter les détails d'un bus
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
        {"Kélibia", 48, 107, "16:00", "Autobus"}
    };
    int nombreReservations = 0;
    int numeroReservation = 1;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Créer un nouveau compte voyageur\n");
        printf("2. Afficher les détails des bus\n");
        printf("3. Créer une nouvelle réservation\n ");
        printf("4. Afficher  les détails d'une réservation\n");
        printf("5. Modifier les détails d'une réservation\n");
        printf("6. Annuler réservation\n");
        printf("7. Quitter\n");

        int choix;
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                     reservations = realloc(reservations, (nombreReservations + 1) * sizeof(Reservation));
                     if (reservations == NULL) {
                            printf("Erreur d'allocation de mémoire.\n");
                            exit(EXIT_FAILURE);
    }

    // Créer un compte voyageur pour la réservation actuelle
                     reservations[nombreReservations].voyageur = creerVoyageur();
                     nombreReservations++;

                       break;
            case 3:
                reservations = realloc(reservations, (nombreReservations + 1) * sizeof(Reservation));
                if (reservations == NULL) {
                    printf("Erreur d'allocation de mémoire.\n");
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
                printf("Choix invalide. Veuillez réessayer.\n");
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
        printf("Erreur : Bus pour la destination %s non trouvé.\n", reservation->destination);
    }
}


// Fonction pour créer un nouveau compte voyageur
Voyageur creerVoyageur() {
    Voyageur nouveauVoyageur;
    do {
        printf("Entrez votre nom : ");
        scanf("%s", nouveauVoyageur.nom);

        if (!estAlphabetique(nouveauVoyageur.nom)) {
            printf("Le nom doit contenir uniquement des lettres. Veuillez saisir à nouveau.\n");
        }
    } while (!estAlphabetique(nouveauVoyageur.nom));
    do {
        printf("Entrez votre prénom : ");
        scanf("%s", nouveauVoyageur.prenom);

        if (!estAlphabetique(nouveauVoyageur.prenom)) {
            printf("Le prénom doit contenir uniquement des lettres. Veuillez saisir à nouveau.\n");
        }
    } while (!estAlphabetique(nouveauVoyageur.prenom));

    printf("Adresse: ");
    scanf("%s", nouveauVoyageur.adresse);
    printf("Email: ");
    scanf("%s", nouveauVoyageur.email);
    printf("Donnez le numéro de téléphone ");
    scanf("%d",&nouveauVoyageur.telephone);
    return nouveauVoyageur;

}

// Fonction pour créer une nouvelle réservation
Reservation* creerReservation(int numero) {
    Reservation *nouvelleReservation = malloc(sizeof(Reservation));
    if (nouvelleReservation == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    nouvelleReservation->numero = numero;
    printf("Destination: ");
    scanf("%s", nouvelleReservation->destination);
    printf("Nombre de places: ");
    scanf("%d", &nouvelleReservation->nombrePlaces);
    printf("Montant: ");
    scanf("%f",&nouvelleReservation->montant);
    printf("Donnez la date de réservation");
    scanf("%s",nouvelleReservation->dateReservation);
    printf("Donnez la durée de séjour");
    scanf("%d",&nouvelleReservation->dureeSejour);
    printf("Donnez le moyen de paiement");
    scanf("%s",nouvelleReservation->moyenPaiement);

    return nouvelleReservation;
}

// Fonction pour afficher les détails des bus
void afficherDetailsBus(BusDetails *bus) {
    printf("Détails des Bus :\n");

    for (int i = 0; i <7; i++) {
        printf("Bus #%d\n", bus[i].numeroBus);
        printf("Destination : %s\n", bus[i].destination);
        printf("Places disponibles : %d\n", bus[i].placesDisponibles);
        printf("Horaire de départ : %s\n", bus[i].horaireDepart);
        printf("Type de bus : %s\n", bus[i].typeBus);
        printf("\n");
    }
}

// Fonction pour afficher  les détails d'une réservation
void afficherReservation(Reservation *reservations, int nombreReservations) {
    int numeroReservation;
    printf("Numéro de réservation: ");
    scanf("%d", &numeroReservation);

    for (int i = 0; i < nombreReservations; ++i) {
        if (reservations[i].numero == numeroReservation) {
            printf("Détails de la réservation %d:\n", reservations[i].numero);
            printf("Voyageur: %s %s\n", reservations[i].voyageur.nom, reservations[i].voyageur.prenom);
            printf("Destination: %s\n", reservations[i].destination);
            printf("Nombre de places: %d\n", reservations[i].nombrePlaces);
            printf("Montant: %.2f\n", reservations[i].montant);
            printf("Date réservation:%s\n",reservations[i].dateReservation);
            printf("Durée de séjour: %d\n", reservations[i].dureeSejour);
            printf("Moyen de paiement:%s\n",reservations[i].moyenPaiement);



        }
    }
}
void ModifierReservation(Reservation *reservations, int nombreReservations) {
    int numeroReservation;
    printf("Numéro de réservation: ");
    scanf("%d", &numeroReservation);
            for (int i = 0; i < nombreReservations; ++i) {
                if (reservations[i].numero == numeroReservation) {
            printf("Nouvelle destination: ");
            scanf("%s", reservations[i].destination);
            printf("Nouveau nombre de places: ");
            scanf("%d", &reservations[i].nombrePlaces);
            printf("Nouveau montant: ");
            scanf("%f", &reservations[i].montant);
            printf("Nouvelle date de réservation:");
            scanf("%s",reservations[i].dateReservation);
            printf("Nouvelle durée de séjour:");
            scanf("%d",&reservations[i].dureeSejour);
            printf("Nouveau moyen de paiement:");
            scanf("%s",reservations[i].moyenPaiement);


}
            }
            }
void annulerReservation(Reservation *reservations, int *nombreReservations) {
    if (*nombreReservations == 0) {
        printf("Aucune réservation n'a été effectuée.\n");
    } else {
        int numeroReservation;
        printf("Entrez le numéro de réservation à annuler : ");
        scanf("%d", &numeroReservation);

        int index = -1;
        for (int i = 0; i < *nombreReservations; i++) {
            if (reservations[i].numero == numeroReservation) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            // Supprimez la réservation en décalant les éléments du tableau
            for (int i = index; i < *nombreReservations - 1; i++) {
                reservations[i] = reservations[i + 1];
            }
            (*nombreReservations)--;
            printf("Réservation annulée avec succès.\n");
        } else {
            printf("Aucune réservation trouvée avec le numéro spécifié.\n");
        }
    }
}

// Fonction pour libérer la mémoire allouée pour les réservations
void libererMemoire(Reservation *reservations, int nombreReservations) {
    for (int i = 0; i < nombreReservations; ++i) {
        free(&reservations[i]);
    }
    free(reservations);
}
