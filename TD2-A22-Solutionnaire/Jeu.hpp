#pragma once
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <string>
#include <memory>
#include <functional>

class Jeu
{
public:
	
	Jeu(string& titre, unsigned anneSortie, string& developpeur)
	{
		setAnneeSortie(anneSortie);
		setDeveloppeur(developpeur);
		setTitre(titre);
	}

	const std::string& getTitre() const { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }
	unsigned getAnneeSortie() const { return anneeSortie_; }
	void setAnneeSortie(unsigned annee) { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	
	Liste<Concepteur>& getConcepteurs() { return concepteurs_; }

	
	shared_ptr<Concepteur> trouverConcepteur(function<bool(shared_ptr<Concepteur>)> critere)
	{
		for (unsigned i = 0; i < concepteurs_.size(); i++)
		{
			if (critere(concepteurs_[i]))
				return concepteurs_[i];
		}
		return	nullptr;
	}

private:
	Liste<Concepteur> concepteurs_ = Liste<Concepteur>();
	unsigned anneeSortie_;
	std::string titre_;
	std::string developpeur_;
	
};
