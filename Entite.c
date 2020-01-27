//Entite.c
#include <stdio.h>
#include <stdlib.h>

#include "Entite.h"

const char* getCategorieName(Categorie categorie) {
	switch (categorie) {
		case GUERRIER: 
			return "GUERRIER";
		case MAGE: 
			return "MAGE";
		case PRETRE: 
			return "PRETRE";
		case LOUP: 
			return "LOUP";
		case SLIME: 
			return "SLIME";
	}
}

void initEntite(Entite* entite, Categorie categorie) {
	switch (categorie) {
		case GUERRIER:
			entite->categorie = GUERRIER;
			entite->pv = 100;
			entite->pm = 10;
			entite->pmMax = 10;
			entite->pmRegen = 1;
			entite->statutPoison = 0;
			entite->dmgAtk = 10;
			entite->dmgPoison = 4;
			entite->coutPoison = 8;
			entite->action = 0;
			break;
		case SLIME:
			entite->categorie = SLIME;
			entite->pv = 100;
			entite->pm = 10;
			entite->pmMax = 10;
			entite->pmRegen = 1;
			entite->statutPoison = 0;
			entite->dmgAtk = 15;
			entite->dmgPoison = 2;
			entite->coutPoison = 6;
			entite->action = 0;
	}
}