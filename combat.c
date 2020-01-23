#include <stdio.h>
#include <stdlib.h>

int main() {
	int tour = 1;
	
	// Caractéristiques du héros
	int heros_pv = 100;
	int heros_pm = 10;
	int heros_pmMax = 10;
	int heros_pmRegen = 1;
	int heros_statutPoison = 0;
	int heros_dmgAtk = 10;
	int heros_dmgPoison = 4;
	int heros_coutPoison = 8;
	int heros_action = 0;
	
	// Caractéristiques du boss
	int boss_pv = 100;
	int boss_pm = 10;
	int boss_pmMax = 10;
	int boss_pmRegen = 1;
	int boss_statutPoison = 0;
	int boss_dmgAtk = 15;
	int boss_dmgPoison = 2;
	int boss_coutPoison = 6;
	int boss_action = 0;
	
	int dmg;
	
	while (heros_pv > 0 && boss_pv > 0) {
		printf("Tour %d\n", tour);
		// État du héros
		printf("HEROS: %d/100 %d/%d", heros_pv, heros_pm, heros_pmMax);
		if (heros_statutPoison)
			printf(" POISON");
		printf("\n");
		// État du boss
		printf("BOSS : %d/100", boss_pv);
		if (boss_statutPoison)
			printf(" POISON");
		printf("\n");
		printf("\n");
		
		// Choix du joueur
		printf("1 Attaquer | 2 Defendre | 3 Poison (%dPM) | 4 Antidote\n", heros_coutPoison);
		do {
			printf("> ");
			scanf("%d", &heros_action);
		} while (heros_action != 1 && heros_action != 2 && heros_action != 3 && heros_action != 4);
		printf("\n");
		
		// Choix du boss
		boss_action = rand()%3 + 1;
		
		// Action du joueur
		// 1 ATTAQUER
		if (heros_action == 1) {
			if (boss_action == 2) {
				printf("Vous attaquez le BOSS, mais celui-ci se defend.\n");
				dmg = heros_dmgAtk/4;
			} else {
				printf("Vous attaquez le BOSS.\n");
				dmg = heros_dmgAtk;
			}
			printf("> %d DMG\n", dmg);
			printf("> PV BOSS : %d => ", boss_pv);
			boss_pv -= dmg;
			printf("%d\n", boss_pv);
		// 2 DEFENDRE
		} else if (heros_action == 2) {
			printf("Vous vous preparez a defendre.\n");
		// 3 LANCER POISON
		} else if (heros_action == 3) {
			printf("Vous lancez un sort de poison sur le BOSS.\n");
			if (heros_pm >= heros_coutPoison) {
				printf("Le BOSS est empoisonne.\n");
				heros_pm -= heros_coutPoison;
				boss_statutPoison = 1;
			} else {
				printf("Vous n'avez pas assez de magie, le sort echoue.\n");
			}
		// BOIRE ANTIDOTE
		} else if (heros_action == 4) {
			printf("Vous buvez un antidote.\n");
			if (heros_statutPoison == 1) {
				printf("Vous etes gueri du poison.\n");
				heros_statutPoison == 0;
			}
		}
		printf("\n");
		
		// Action du boss
		if (boss_pv > 0) {
			// ATTAQUE
			if (boss_action == 1 || (boss_action == 3 && boss_pm < boss_coutPoison)) {
				if (heros_action == 2) {
					printf("Le BOSS frappe dans votre garde.\n");
					dmg = boss_dmgAtk/4;
				} else {
					printf("Le BOSS attaque.\n");
					dmg = boss_dmgAtk;
				}
				printf("> %d DMG\n", dmg);
				printf("> PV HEROS : %d => ", heros_pv);
				heros_pv -= dmg;
				printf("%d\n", heros_pv);
			// DEFENSE
			} else if (boss_action == 2) {
				printf("Le BOSS vous regarde intensement.\n");
			// POISON
			} else if (boss_action == 3) {
				printf("Le BOSS repand un gaz toxique.\n");
				printf("Vous etes empoisonne.\n");
				boss_pm -= boss_coutPoison;
				heros_statutPoison = 1;
			}
			printf("\n");
		}
		
		// Alération d'état du joueur
		if (heros_pv > 0) {
			if (heros_statutPoison) {
				printf("Le poison vous affaibli.\n");
				printf("> %d DMG\n", boss_dmgPoison);
				printf("> PV HEROS : %d => ", heros_pv);
				heros_pv -= boss_dmgPoison;
				printf("%d\n", heros_pv);
				printf("\n");
			}
		}
		
		// Altération d'état du BOSS
		if (boss_pv > 0) {
			if (boss_statutPoison) {
				printf("Le poison epuise le BOSS.\n");
				printf("> %d DMG\n", heros_dmgPoison);
				printf("> PV BOSS : %d => ", boss_pv);
				boss_pv -= heros_dmgPoison;
				printf("%d\n", boss_pv);
				printf("\n");
			}
		}
		
		// Résolution du tour
		heros_pm += 1;
		if (heros_pm > heros_pmMax) {
			heros_pm = heros_pmMax;
		}
		boss_pm += 1;
		if (boss_pm > boss_pmMax) {
			boss_pm = boss_pmMax;
		}
		tour += 1;
		printf("================================\n\n");
	}
	
	if (heros_pv <= 0) {
		printf("VOUS AVEZ PERDU\n");
	} else {
		printf("VICTOIRE !\n");
	}
	
	return 0;
}