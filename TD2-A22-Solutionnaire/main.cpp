#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"

#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

using namespace std;
using namespace iter;
using namespace gsl;

#pragma region "Fonctions de base pour vous aider"
template <typename T>
T lireType(istream& fichier)
{
	T valeur{};
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}
#define erreurFataleAssert(message) assert(false&&(message)),terminate()
static const uint8_t enteteTailleVariableDeBase = 0xA0;
size_t lireUintTailleVariable(istream& fichier)
{
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase+0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase+1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase+2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement.");
	}
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion

//TODO: Fonction qui cherche un concepteur par son nom dans une ListeJeux.
// Cette fonction renvoie le pointeur vers le concepteur si elle le trouve dans
// un des jeux de la ListeJeux. En cas contraire, elle renvoie un pointeur nul.
shared_ptr<Concepteur> trouverConcepteur(Liste<Jeu>& listeJeux, string nom)
{
	for (int i = 0; i < listeJeux.size(); i++)
	{
		auto concepteur = listeJeux[i]->trouverConcepteur([&](shared_ptr<Concepteur> c) -> bool { return c->getNom() == nom; });

		if (concepteur != nullptr)
			return concepteur;
	}
	return nullptr;
}

shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj,istream& fichier)
{
	string nom = lireString(fichier);
	unsigned anneeNaissance = lireUint16(fichier);
	string pays = lireString(fichier);

	auto concepteur = chercherConcepteur(lj, nom);

	if (concepteur != nullptr)
		return concepteur;

	return make_shared<Concepteur>(nom, anneeNaissance, pays);
}



shared_ptr<Jeu> lireJeu(istream& fichier, Liste<Jeu>& lj)
{
	
	string titre = lireString(fichier);
	unsigned anneeSortie = int(lireUintTailleVariable(fichier));
	string developpeur = lireString(fichier);
	unsigned nConcepteurs = lireUintTailleVariable(fichier);
	
	auto jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);

	for (unsigned i = 0; i < nConcepteurs; i++)
		jeu->getConcepteurs().ajouter(lireConcepteur(lj, fichier));

	return jeu;
	
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	size_t nElements = lireUintTailleVariable(fichier);
	Liste<Jeu> listeJeux;
	for([[maybe_unused]] size_t n : iter::range(nElements))
	{
		ajouterJeu(listeJeux, lireJeu(fichier, listeJeux)); //
	}

	return listeJeux; 
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion

	Liste<Jeu> lj = creerListeJeux("jeux.bin"); 

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << lj;
	cout << "troisieme jeu de la liste(indice 2) :" << 
		lj.operator[](2)->getTitre() << endl;
	cout << "Nom du 2e concepteur du 3e jeu dans la liste : " << lj.operator[](2)->getConcepteurs().operator[](1)->getNom() << endl;

	string concepteurCherche = "Yoshinori Kitase";
	cout << "Adresse de Yoshinori dans jeu 1 : " << lj[0]->trouverConcepteur([&](shared_ptr<Concepteur> c) -> bool { return c->getNom() == concepteurCherche; }) << endl;
	cout << "Adresse de Yoshinori dans jeu 2 : " << lj[1]->trouverConcepteur([&](shared_ptr<Concepteur> c) -> bool { return c->getNom() == concepteurCherche; }) << endl;
	cout << "Annee de naissance de Yoshinori : " << lj[0]->trouverConcepteur([&](shared_ptr<Concepteur> c) -> bool { return c->getNom() == concepteurCherche; })->getAnneeNaissance() << endl;
	Jeu copieJeu = *lj[2];
	copieJeu.getConcepteurs()[1] = lj[0]->getConcepteurs()[0];
	cout << "Jeu à l'indice 2 : \n" << lj[2]->getConcepteurs() << endl;
	cout << "Copie du jeu à l'indice 2 modifiee : \n" << copieJeu.getConcepteurs() << endl;
	cout << "Adresse du premier concepteur du jeu : " << lj[2]->getConcepteurs()[0] << endl;
	cout << "Adresse du premier concepteur de la copie du jeu : " << copieJeu.getConcepteurs()[0] << endl;





	
	
}
