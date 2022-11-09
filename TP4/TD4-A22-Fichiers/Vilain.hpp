#pragma once
#include  "Personnage.hpp"
#include <string>
#include <iostream>
#include <vector>

class Vilain : virtual public Personnage
{
public:
	Vilain() = default;

	Vilain(const std::string nom, const std::string titre, const std::string objectif) :
		Personnage(nom, titre),
		objectif_(objectif) 
	{}

	Vilain(const std::shared_ptr<Vilain> v) : 
		Personnage(v->nom_, v->parution_),
		objectif_(v->objectif_)
	{}
	 
	void afficher() {
		std::cout << color_ << " nom: " << nom_ << std::endl << "Parution: " << parution_ << std::endl << "Objectif : " << objectif_ << std::endl;
	}

	void changerCouleur(std::string couleur) {
		this->color_ = COLOR.find(couleur)->second;
	}

	void setObjectif(const std::string objectif) {
		this->objectif_ = objectif;
	}

	const std::string getObjetif() {
		return this->objectif_;
	}


protected:
	std::string objectif_;
};

