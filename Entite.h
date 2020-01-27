// Entite.h
#ifndef ENTITE_H
#define ENTITE_H

typedef enum Categorie Categorie;
enum Categorie {
	// Classes de héros
	GUERRIER,
	MAGE,
	PRETRE,
	// Monstres
	LOUP,
	SLIME
};

typedef struct Entite Entite;
struct Entite {
	Categorie categorie;
	int pv;
	int pm;
	int pmMax;
	int pmRegen;
	int statutPoison;
	int dmgAtk;
	int dmgPoison;
	int coutPoison;
	int action;
};

void initEntite(Entite*, Categorie);

#endif