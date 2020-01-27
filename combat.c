#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Entite.h"

#define NB_HEROS 3
#define NB_ENNEMIS 1

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
	
	while (heros[0].pv > 0 && boss.pv > 0) {

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
		printf("1 Attaquer | 2 Defendre | 3 Poison (%dPM) | 4 Antidote\n", heros[0].coutPoison);
		do {
			printf("> ");
			scanf("%d", & heros[0].action);
		} while ( heros[0].action != 1 &&  heros[0].action != 2 &&  heros[0].action != 3 &&  heros[0].action != 4);
		printf("\n");
		
		// Choix du boss
		boss.action = rand()%3 + 1;
		
		// Action du joueur
		// 1 ATTAQUER
		if ( heros[0].action == 1) {
			if (boss.action == 2) {
				printf("Vous attaquez le BOSS, mais celui-ci se defend.\n");
				dmg =  heros[0].dmgAtk/4;
			} else {
				printf("Vous attaquez le BOSS.\n");
				dmg =  heros[0].dmgAtk;
			}
			printf("> %d DMG\n", dmg);
			printf("> PV BOSS : %d => ", boss.pv);
			boss.pv -= dmg;
			printf("%d\n", boss.pv);
		// 2 DEFENDRE
		} else if ( heros[0].action == 2) {
			printf("Vous vous preparez a defendre.\n");
		// 3 LANCER POISON
		} else if ( heros[0].action == 3) {
			printf("Vous lancez un sort de poison sur le BOSS.\n");
			if ( heros[0].pm >=  heros[0].coutPoison) {
				printf("Le BOSS est empoisonne.\n");
				 heros[0].pm -=  heros[0].coutPoison;
				boss.statutPoison = 1;
			} else {
				printf("Vous n'avez pas assez de magie, le sort echoue.\n");
			}
		// BOIRE ANTIDOTE
		} else if ( heros[0].action == 4) {
			printf("Vous buvez un antidote.\n");
			if ( heros[0].statutPoison == 1) {
				printf("Vous etes gueri du poison.\n");
				 heros[0].statutPoison = 0;
			}
		}
		printf("\n");
		
		// Action du boss
		if (boss.pv > 0) {
			// ATTAQUE
			if (boss.action == 1 || (boss.action == 3 && boss.pm < boss.coutPoison)) {
				if ( heros[0].action == 2) {
					printf("Le BOSS frappe dans votre garde.\n");
					dmg = boss.dmgAtk/4;
				} else {
					printf("Le BOSS attaque.\n");
					dmg = boss.dmgAtk;
				}
				printf("> %d DMG\n", dmg);
				printf("> PV HEROS : %d => ",  heros[0].pv);
				 heros[0].pv -= dmg;
				printf("%d\n",  heros[0].pv);
			// DEFENSE
			} else if (boss.action == 2) {
				printf("Le BOSS vous regarde intensement.\n");
			// POISON
			} else if (boss.action == 3) {
				printf("Le BOSS repand un gaz toxique.\n");
				printf("Vous etes empoisonne.\n");
				boss.pm -= boss.coutPoison;
				 heros[0].statutPoison = 1;
			}
			printf("\n");
		}
		
		// Alération d'état du joueur
		if ( heros[0].pv > 0) {
			if ( heros[0].statutPoison) {
				printf("Le poison vous affaibli.\n");
				printf("> %d DMG\n", boss.dmgPoison);
				printf("> PV HEROS : %d => ",  heros[0].pv);
				 heros[0].pv -= boss.dmgPoison;
				printf("%d\n",  heros[0].pv);
				printf("\n");
			}
		}
		
		// Altération d'état du BOSS
		if (boss.pv > 0) {
			if (boss.statutPoison) {
				printf("Le poison epuise le BOSS.\n");
				printf("> %d DMG\n",  heros[0].dmgPoison);
				printf("> PV BOSS : %d => ", boss.pv);
				boss.pv -=  heros[0].dmgPoison;
				printf("%d\n", boss.pv);
				printf("\n");
			}
		}
		
		// Résolution du tour
		 heros[0].pm += 1;
		if ( heros[0].pm >  heros[0].pmMax) {
			 heros[0].pm =  heros[0].pmMax;
		}
		boss.pm += 1;
		if (boss.pm > boss.pmMax) {
			boss.pm = boss.pmMax;
		}
		tour += 1;
		printf("================================\n\n");
	}
	
	if ( heros[0].pv <= 0) {
		printf("VOUS AVEZ PERDU\n");
	} else {
		printf("VICTOIRE !\n");
	}
	
	return 0;
}

void afficherStatut(Entite entite) {
	printf("%s: %d/100 PV | %d/%d PM", getCategorieName(entite.categorie), entite.pv, entite.pm, entite.pmMax);
	if ( entite.statutPoison)
		printf(" | POISON");
	printf("\n");
}