#pragma once
#include  "Personnage.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Vilain : virtual public Personnage
{
public:

	Vilain() = default;


	Vilain(const string& nom, const string& titre, const string& objectif) :
		Personnage(nom, titre),
		objectif_(objectif) 
	{}


	Vilain(const Vilain& vilain) : 
		Personnage(vilain.nom_, vilain.titreJeu_),
		objectif_(vilain.objectif_)
	{}
	 

	ostream& afficherVilain(ostream& os, char couleur) const;
	ostream& afficher(ostream& os) const override;


protected:
	string objectif_;
};

ostream& Vilain::afficherVilain(ostream& os, char couleur) const
{
	Personnage::changerCouleur(os, couleur) << " Objectif : " << objectif_ << endl;

	Personnage::changerCouleur(os, 'R');
	return os;
}

ostream& Vilain::afficher(ostream& os) const
{
	Personnage::changerCouleur(os, 'R');
	Personnage::afficher(os);
	afficherVilain(os, 'R');
	return os;
}

