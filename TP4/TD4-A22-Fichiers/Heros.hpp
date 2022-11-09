#pragma once
#include "Personnage.hpp"
#include <vector>

using namespace std;

class Heros : virtual public Personnage
{
public:
	
	Heros(void) = default;

	
	Heros(const string& nom, const string& titre, const string& ennemi, const vector<string> allies) :
		Personnage(nom, titre),
		ennemi_{ ennemi },
		nomsAllies_{ allies }
	{}

	
	Heros(const Heros& heros) :
		Personnage(heros.nom_, heros.titreJeu_),
		ennemi_{ heros.ennemi_ },
		nomsAllies_{ heros.nomsAllies_ }
	{}

	const string& getEnnemi() const { return ennemi_; }
	const vector<string>& getAllies() const { return nomsAllies_; }

	ostream& afficherHero(ostream& os, char couleur) const;
	ostream& afficher(ostream& os) const override;

protected:
	vector<string> nomsAllies_;
	string ennemi_;
};

ostream& Heros::afficherHero(ostream& os, char couleur) const
{
	Personnage::changerCouleur(os, couleur) << "Ennemi : " << ennemi_ << endl;
	os << "Allies : " << endl;

	for (auto i = 0; i < nomsAllies_.size(); ++i)
		os << "\t" << nomsAllies_[i] << endl;

	Personnage::changerCouleur(os, ' ');
	return os;
}

ostream& Heros::afficher(ostream& os) const
{
	Personnage::changerCouleur(os, 'B');
	Personnage::afficher(os);
	afficherHero(os, 'B');
	return os;
}