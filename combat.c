#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Entite.h"

int main() {
	srand(time(NULL));
	int tour = 1;
	int dmg;
	Entite protagonistes[1];
	Entite ennemis[1];

	Entite heros;
	initEntite(&heros, GUERRIER);

	Entite boss;
	initEntite(&boss, SLIME);

	protagonistes[0] = heros;
	ennemis[0] = boss;
	
	while (heros.pv > 0 && boss.pv > 0) {
		printf("Tour %d\n", tour);
		// État du héros
		printf("HEROS: %d/100 %d/%d",  heros.pv,  heros.pm,  heros.pmMax);
		if ( heros.statutPoison)
			printf(" POISON");
		printf("\n");
		// État du boss
		printf("BOSS : %d/100", boss.pv);
		if (boss.statutPoison)
			printf(" POISON");
		printf("\n");
		printf("\n");
		
		// Choix du joueur
		printf("1 Attaquer | 2 Defendre | 3 Poison (%dPM) | 4 Antidote\n", heros.coutPoison);
		do {
			printf("> ");
			scanf("%d", & heros.action);
		} while ( heros.action != 1 &&  heros.action != 2 &&  heros.action != 3 &&  heros.action != 4);
		printf("\n");
		
		// Choix du boss
		boss.action = rand()%3 + 1;
		
		// Action du joueur
		// 1 ATTAQUER
		if ( heros.action == 1) {
			if (boss.action == 2) {
				printf("Vous attaquez le BOSS, mais celui-ci se defend.\n");
				dmg =  heros.dmgAtk/4;
			} else {
				printf("Vous attaquez le BOSS.\n");
				dmg =  heros.dmgAtk;
			}
			printf("> %d DMG\n", dmg);
			printf("> PV BOSS : %d => ", boss.pv);
			boss.pv -= dmg;
			printf("%d\n", boss.pv);
		// 2 DEFENDRE
		} else if ( heros.action == 2) {
			printf("Vous vous preparez a defendre.\n");
		// 3 LANCER POISON
		} else if ( heros.action == 3) {
			printf("Vous lancez un sort de poison sur le BOSS.\n");
			if ( heros.pm >=  heros.coutPoison) {
				printf("Le BOSS est empoisonne.\n");
				 heros.pm -=  heros.coutPoison;
				boss.statutPoison = 1;
			} else {
				printf("Vous n'avez pas assez de magie, le sort echoue.\n");
			}
		// BOIRE ANTIDOTE
		} else if ( heros.action == 4) {
			printf("Vous buvez un antidote.\n");
			if ( heros.statutPoison == 1) {
				printf("Vous etes gueri du poison.\n");
				 heros.statutPoison = 0;
			}
		}
		printf("\n");
		
		// Action du boss
		if (boss.pv > 0) {
			// ATTAQUE
			if (boss.action == 1 || (boss.action == 3 && boss.pm < boss.coutPoison)) {
				if ( heros.action == 2) {
					printf("Le BOSS frappe dans votre garde.\n");
					dmg = boss.dmgAtk/4;
				} else {
					printf("Le BOSS attaque.\n");
					dmg = boss.dmgAtk;
				}
				printf("> %d DMG\n", dmg);
				printf("> PV HEROS : %d => ",  heros.pv);
				 heros.pv -= dmg;
				printf("%d\n",  heros.pv);
			// DEFENSE
			} else if (boss.action == 2) {
				printf("Le BOSS vous regarde intensement.\n");
			// POISON
			} else if (boss.action == 3) {
				printf("Le BOSS repand un gaz toxique.\n");
				printf("Vous etes empoisonne.\n");
				boss.pm -= boss.coutPoison;
				 heros.statutPoison = 1;
			}
			printf("\n");
		}
		
		// Alération d'état du joueur
		if ( heros.pv > 0) {
			if ( heros.statutPoison) {
				printf("Le poison vous affaibli.\n");
				printf("> %d DMG\n", boss.dmgPoison);
				printf("> PV HEROS : %d => ",  heros.pv);
				 heros.pv -= boss.dmgPoison;
				printf("%d\n",  heros.pv);
				printf("\n");
			}
		}
		
		// Altération d'état du BOSS
		if (boss.pv > 0) {
			if (boss.statutPoison) {
				printf("Le poison epuise le BOSS.\n");
				printf("> %d DMG\n",  heros.dmgPoison);
				printf("> PV BOSS : %d => ", boss.pv);
				boss.pv -=  heros.dmgPoison;
				printf("%d\n", boss.pv);
				printf("\n");
			}
		}
		
		// Résolution du tour
		 heros.pm += 1;
		if ( heros.pm >  heros.pmMax) {
			 heros.pm =  heros.pmMax;
		}
		boss.pm += 1;
		if (boss.pm > boss.pmMax) {
			boss.pm = boss.pmMax;
		}
		tour += 1;
		printf("================================\n\n");
	}
	
	if ( heros.pv <= 0) {
		printf("VOUS AVEZ PERDU\n");
	} else {
		printf("VICTOIRE !\n");
	}
	
	return 0;
}