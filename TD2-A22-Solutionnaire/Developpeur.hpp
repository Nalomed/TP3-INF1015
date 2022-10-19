#pragma once
#include <string>
#include "ListeJeux.hpp"

class Developpeur
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	//TODO: Les méthodes à faire...
public:
	Developpeur(const std::string& nom = "");
	~Developpeur();

	void ajouterJeux(ListeJeux& listeJeux);
	const std::string& getNom() const { return paireNomJeux_.first; }

	void afficher() const;

private:
	unsigned compterJeuxDeveloppes(ListeJeux& listeJeux);  // L'énoncé ne dit pas si ça doit être public ou non.

	std::pair<std::string, ListeJeux> paireNomJeux_;
};
