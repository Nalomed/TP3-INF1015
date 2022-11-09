#pragma once
#include "Heros.hpp"
#include "Vilain.hpp"
#include <string>

class VilainHeros : public Vilain, public Heros
{

public:
	VilainHeros() = default;

	VilainHeros(const std::shared_ptr<Vilain> v, const std::shared_ptr<Heros> h) : 
		Personnage(v->getNom() + "-" + h->getNom(), v->getParution() + "-" + h->getParution()),
		Vilain(v),
		Heros(h),
		missionSpeciale_(v->getObjetif() + " dans le monde de " + h->getParution())
	{}


	void afficher() {
		std::cout << color_ << " nom: " << nom_ << std::endl << " Parution : " << parution_ << std::endl << "Ennemi : " << ennemi_
			<< std::endl << " Objectif : " << objectif_ << std::endl << " Mission speciale : " << missionSpeciale_ << std::endl << "Alliés :" << std::endl;

		for (auto allie : allies_) {
			std::cout << color_ << allie << std::endl;
		}
	}

	void changerCouleur(std::string couleur) {
		Vilain::changerCouleur(couleur);
		Heros::changerCouleur(couleur);
	}

private:
	std::string missionSpeciale_;

};

