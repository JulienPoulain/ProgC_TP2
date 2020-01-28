#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Entite.h"

#define NB_HEROS 3
#define NB_ENNEMIS 1

bool allEntitesDead(Entite[], int);
void afficherStatut(Entite);

int main() {
	srand(time(NULL));
	int tour = 1;
	int dmg;
	Entite heros[NB_HEROS];
	Entite ennemis[NB_HEROS];

	for (int i=0; i<NB_HEROS; i++) {
		Entite entite;
		initEntite(&entite, GUERRIER);
		heros[i] = entite;
	}

	Entite boss;
	initEntite(&boss, SLIME);
	ennemis[0] = boss;
	
	while ( !(allEntitesDead(heros, NB_HEROS) || allEntitesDead(ennemis, NB_ENNEMIS)) ) {

		printf("Tour %d\n", tour);
		printf("\n");

		// État des héros
		for (int i=0; i<NB_HEROS; i++) {
			printf("%d ", i);
			afficherStatut(heros[i]);
		}
		printf("\n");

		// État des ennemis
		for (int i=0; i<NB_ENNEMIS; i++) {
			printf("%d ", i);
			afficherStatut(ennemis[i]);
		}
		printf("\n");
		
		// Choix du joueur
		for (int i=0; i<NB_HEROS; i++) {
			if (heros[i].pv > 0) {
				printf("Heros %d : 1 Attaquer | 2 Defendre | 3 Poison (%dPM) | 4 Antidote\n", i+1, heros[i].coutPoison);
				do {
					printf("> ");
					scanf("%d", & heros[i].action);
				} while (heros[i].action != 1 && heros[i].action != 2 && heros[i].action != 3 && heros[i].action != 4);
				printf("\n");
			}
		}
		
		// Choix du boss
		for (int i=0; i<NB_ENNEMIS; i++) {
			if (ennemis[i].pv > 0) {
				ennemis[i].action = rand()%3 + 1;
			}
		}
		
		// Action du joueur
		for (int i=0; i<NB_HEROS; i++) {
			if (heros[i].pv > 0) {
				// 1 ATTAQUER
				if (heros[i].action == 1) {
					if (ennemis[0].action == 2) {
						printf("Vous attaquez le BOSS, mais celui-ci se defend.\n");
						dmg = heros[i].dmgAtk/4;
					} else {
						printf("Vous attaquez le BOSS.\n");
						dmg = heros[i].dmgAtk;
					}
					printf("> %d DMG\n", dmg);
					printf("> PV BOSS : %d => ", ennemis[0].pv);
					ennemis[0].pv -= dmg;
					printf("%d\n", ennemis[0].pv);
				// 2 DEFENDRE
				} else if (heros[i].action == 2) {
					printf("Vous vous preparez a defendre.\n");
				// 3 LANCER POISON
				} else if (heros[i].action == 3) {
					printf("Vous lancez un sort de poison sur le BOSS.\n");
					if (heros[i].pm >= heros[i].coutPoison) {
						printf("Le BOSS est empoisonne.\n");
						heros[i].pm -= heros[i].coutPoison;
						ennemis[0].statutPoison = 1;
					} else {
						printf("Vous n'avez pas assez de magie, le sort echoue.\n");
					}
				// 4 BOIRE ANTIDOTE
				} else if (heros[i].action == 4) {
					printf("Vous buvez un antidote.\n");
					if (heros[i].statutPoison == 1) {
						printf("Vous etes gueri du poison.\n");
						heros[i].statutPoison = 0;
					}
				}
				printf("\n");
			}
		}
		
		// Action des ennemis
		/////////////////////////
		// /!\ IA OBSOLETE /!\ //
		/////////////////////////
		for (int i=0; i<NB_ENNEMIS; i++) {
			if (ennemis[i].pv > 0) {
				// ATTAQUE
				if (ennemis[i].action == 1 || (ennemis[i].action == 3 && ennemis[i].pm < ennemis[i].coutPoison)) {
					if (heros[0].action == 2) {
						printf("Le BOSS frappe dans votre garde.\n");
						dmg = ennemis[i].dmgAtk/4;
					} else {
						printf("Le BOSS attaque.\n");
						dmg = ennemis[i].dmgAtk;
					}
					printf("> %d DMG\n", dmg);
					printf("> PV HEROS : %d => ", heros[0].pv);
					heros[0].pv -= dmg;
					printf("%d\n", heros[0].pv);
				// DEFENSE
				} else if (ennemis[i].action == 2) {
					printf("Le BOSS vous regarde intensement.\n");
				// POISON
				} else if (ennemis[i].action == 3) {
					printf("Le BOSS repand un gaz toxique.\n");
					printf("Vous etes empoisonne.\n");
					ennemis[i].pm -= ennemis[i].coutPoison;
					heros[0].statutPoison = 1;
				}
				printf("\n");
			}
		}
		
		// Alération d'état du joueur
		//////////////////////////////////
		// /!\ Dmg poison à adapter /!\ //
		//////////////////////////////////
		for (int i=0; i<NB_HEROS; i++) {
			if (heros[i].pv > 0) {
				if (heros[i].statutPoison) {
					printf("Le poison vous affaibli.\n");
					printf("> %d DMG\n", ennemis[i].dmgPoison);
					printf("> PV HEROS : %d => ", heros[i].pv);
					heros[i].pv -= ennemis[0].dmgPoison;
					printf("%d\n", heros[i].pv);
					printf("\n");
				}
			}
		}
		
		// Altération d'état des ennemis
		//////////////////////////////////
		// /!\ Dmg poison à adapter /!\ //
		//////////////////////////////////
		for (int i=0; i<NB_ENNEMIS; i++) {
			if (ennemis[i].pv > 0) {
				if (ennemis[i].statutPoison) {
					printf("Le poison epuise le BOSS.\n");
					printf("> %d DMG\n", heros[0].dmgPoison);
					printf("> PV BOSS : %d => ", ennemis[i].pv);
					ennemis[i].pv -= heros[0].dmgPoison;
					printf("%d\n", ennemis[i].pv);
					printf("\n");
				}
			}
		}
		
		// Résolution du tour
		for (int i=0; i<NB_HEROS; i++) {
			if (heros[i].pv > 0) {
				heros[i].pm += heros[i].pmRegen;
				printf("%d : +1\n", i);
				if (heros[i].pm > heros[i].pmMax) {
					heros[i].pm = heros[i].pmMax;
					printf("non\n");
				}
			}
		}
		for (int i=0; i<NB_ENNEMIS; i++) {
			if (ennemis[i].pv > 0) {
				ennemis[i].pm += 1;
				if (ennemis[i].pm > ennemis[i].pmMax) {
					ennemis[i].pm = ennemis[i].pmMax;
				}
			}
		}
		tour += 1;
		printf("================================\n\n");
	}
	
	if (allEntitesDead(heros, NB_HEROS)) {
		printf("VOUS AVEZ PERDU\n");
	} else {
		printf("VICTOIRE !\n");
	}
	
	return 0;
}

bool allEntitesDead(Entite e[], int tailleTab) {
	for (int i=0; i<tailleTab; i++) {
		if (e[i].pv > 0) {
			return false;
		}
	}
	return true;
}

void afficherStatut(Entite entite) {
	printf("%s: %d/100 PV | %d/%d PM", getCategorieName(entite.categorie), entite.pv, entite.pm, entite.pmMax);
	if ( entite.statutPoison)
		printf(" | POISON");
	printf("\n");
}