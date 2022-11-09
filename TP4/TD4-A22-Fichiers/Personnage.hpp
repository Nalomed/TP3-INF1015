#pragma once
#include <string> 
#include "Affichable.hpp"


using namespace std;

class Personnage : public Affichable
{
public:
	Personnage(void) = default;

	Personnage(const string& nom, const string& titreJeu) :
		nom_{ nom },
		titreJeu_{ titreJeu }
	{}

	const string& getNom() const { return nom_; }
	const string& getTitreJeu() const { return titreJeu_; }

	ostream& afficher(ostream& os) const override;
	ostream& changerCouleur(ostream& os, char couleur) const override;
protected:
	string nom_;
	string titreJeu_;
};

ostream& Personnage::afficher(ostream& os) const
{
	os << "Nom : " + nom_ << endl;
	os << "Parution : " + titreJeu_ << endl;
	return os;
}

ostream& Personnage::changerCouleur(ostream& os, char couleur) const
{
	switch (couleur)
	{
	case 'R': 
		return os << "\033[31m";
		break;
	case 'B': 
		return os << "\033[34m";
		break;
	case 'M': 
		return os << "\033[35m";
		break;
	default: //blanc
		return os << "\033[0m";
		break;
	}
}
