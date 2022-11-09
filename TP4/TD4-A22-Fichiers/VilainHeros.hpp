#pragma once
#include "Heros.hpp"
#include "Vilain.hpp"
#include <string>
using namespace std;

class VilainHeros : public Vilain, public Heros
{

public:
	VilainHeros() = default;

	VilainHeros(const Vilain vilain, const Heros hero) : 
		Personnage(vilain.nom_ + "-" + hero.nom_, vilain.titreJeu_ + "-" + hero.titreJeu_),
		Vilain(v),
		Heros(h),
		missionSpeciale_(vilain.objectif_ + " dans le monde de " + hero.titreJeu_)
	{}


	void afficher() {
		cout << color_ << " nom: " << nom_ << endl << " Parution : " << parution_ << endl << "Ennemi : " << ennemi_
			<< endl << " Objectif : " << objectif_ << endl << " Mission speciale : " << missionSpeciale_ << endl << "Alliés :" << endl;

		for (auto allie : allies_) {
			cout << color_ << allie << endl;
		}
	}

	void changerCouleur(string couleur) {
		Vilain::changerCouleur(couleur);
		Heros::changerCouleur(couleur);
	}

private:
	std::string missionSpeciale_;

};

