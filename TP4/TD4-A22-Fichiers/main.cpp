#include "lectureBinaire.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include "bibliotheque_cours.hpp"
#include <fstream>
#include<iostream>
#include "bibliotheque_cours.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
using namespace std;

ifstream ouvrirFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

void testsPourCouvertureLectureBinaire()
{
	istringstream iss("\xA0\x12\xA1\x21\x43\xA2\x98\xBA\xDC\xFE");
	assert(lireUintTailleVariable(iss) == 0x12);
	assert(lireUintTailleVariable(iss) == 0x4321);
	assert(lireUintTailleVariable(iss) == 0xFEDCBA98);

}

void ajouter(vector<Personnage>& personnages, const vector<Vilain> vilains, const vector<Heros> heros)
{
	for (int i = 0; i < heros.size(); ++i)
		personnages.push_back(heros[i]);

	for (int j = 0; j < vilains.size(); ++j)
		personnages.push_back(vilains[j]);
}
template <typename T>
void afficher(const vector<T> vect, const string& trait)
{
	for (int k = 0; k < vect.size(); ++k)
	{
		vect[k].afficher(cout);
		cout << trait << endl;
	}
}


int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	testsPourCouvertureLectureBinaire();

	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	// Ouverture des fichiers binaires
	ifstream fichierHeros = ouvrirFichierBinaire("heros.bin");
	ifstream fichierVilains = ouvrirFichierBinaire("vilains.bin");

	//TODO: Votre code pour le main commence ici (mais vous pouvez aussi ajouter/modifier du code avant si nécessaire)
	// 
	//creation des vecteurs
	vector<Heros> herosVecteur ;
	vector<Vilain> vilains;
	vector<Personnage> personnages;
	// Lire les heros

	int nombreHeros = lireUintTailleVariable(fichierHeros);
	for (int i = 0; i < nombreHeros; ++i)
	{
		string nom = lireString(fichierHeros);
		string titre = lireString(fichierHeros);
		string ennemi = lireString(fichierHeros);
		int nAllies = lireUintTailleVariable(fichierHeros);
		vector<string> allies;
		for (int j = 0; j < nAllies; ++j)
		{
			// ajouter chaque allie a l'attribut de l'heros
			allies.push_back(lireString(fichierHeros));
		}

		Heros heros = Heros(nom, titre, ennemi, allies);
		// ajouter le heros au vecteur
		herosVecteur.push_back(heros);
	}

	// Lire les vilains
	unsigned nVilains = lireUintTailleVariable(fichierVilains);
	for (unsigned i = 0; i < nVilains; ++i)
	{
		string nom = lireString(fichierVilains);
		string titre = lireString(fichierVilains);
		string objectif = lireString(fichierVilains);

		Vilain vilain = Vilain(nom, titre, objectif);
		// ajouter le vilain au vecteur
		vilains.push_back(vilain);
	}

	// Afficher vecteur d'heros
	afficher(herosVecteur, trait);

	// Afficher vecteur de vilains
	afficher(vilains, trait);

	// Ajouter tout le vilains et heros au vecteur de personnages
	ajouter(personnages, vilains, herosVecteur);

	// Afficher vecteur de personnages
	afficher(personnages, trait);

	// Creer un VilainHeros a partir du 3e vilain et 1er heros
	VilainHeros vilainHeros = VilainHeros(vilains[2], herosVecteur[0]);

	// Afficher VilainHeros en console
	vilainHeros.afficher(cout);
	cout << trait << endl;

	// Ajouter  VilainHeros au vecteur de personnages
	personnages.push_back(vilainHeros);

	// Afficher vecteur de personnages
	afficher(personnages, trait);
}
