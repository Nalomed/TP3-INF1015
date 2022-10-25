#pragma once
#include <string>
#include "ListeJeux.hpp"

class Concepteur
{
public:
	//TODO: Un constructeur par défaut et un constructeur paramétré.
	Concepteur() { setAnneeNaissance(0); }
	Concepteur(const std::string& nom, int anne, const std::string& pays)
	{
		setAnneeNaissance(anne);
		setNom(nom);
		setPays(pays);
	}
	const std::string& getNom() const { return nom_; }
	void setNom(const std::string& nom) { nom_ = nom; }
	int getAnneeNaissance() const { return anneeNaissance_; }
	void setAnneeNaissance(int annee) { anneeNaissance_ = annee; }
	const std::string& getPays() const { return pays_; }
	void setPays(const std::string& pays) { pays_ = pays; }

private:
	std::string nom_;
	unsigned anneeNaissance_;
	std::string pays_;
};

