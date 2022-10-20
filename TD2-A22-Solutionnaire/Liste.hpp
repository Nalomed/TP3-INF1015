#pragma once 
#include <cstddef>
#include "gsl/span"

template<typename T>
class Liste {
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
public:
	Liste() = default;
	~Liste();

	T ajouter(T  *d);
	T retirer(const T* aRetirer);

	T afficher() const;

private:
	T changerCapacite(T nouvelleCapacite);  // Pas dit si ça doit être public ou non.
	gsl::span<T*> enSpan() const { return { elements_, nElements_ }; }  // Pourrait être public.

	T nElements_ = 0;
	T capacite_ = 0;  // Pas besoin de déclarer explicitement un corps de constructeur avec ces initialisations.
	Developpeur** elements_ = nullptr;
};

//definition des methodes :
template<typename T>
Liste<T>::~Liste()
{
	delete[] elements_;
}

template<typename T>
T Liste<T>::afficher() const
{
	for (const T* d : enSpan())
		d->afficher();
}

template<typename T>
T Liste<T>::ajouter(T* d)
{
	if (nElements_ == capacite_)
		changerCapacite(max(T(1), capacite_ * 2));
	elements_[nElements_++] = d;
}

template<typename T>
T Liste<T>::retirer(const T* aRetirer)
{
	for (T*& d : enSpan()) {
		if (d == aRetirer) {
			if (nElements_ > 1)
				d = elements_[nElements_ - 1];
			nElements_--;
		}
	}
}

template<typename T>
T Liste<T>::changerCapacite(T nouvelleCapacite)
{
	// Copie du code de changerTailleListeJeux, ajusté pour la classe.
	assert(nouvelleCapacite >= nElements_); // On ne demande pas de supporter les réductions de nombre d'éléments.
	Developpeur** nouvelleListe = new Developpeur * [nouvelleCapacite];
	// Pas nécessaire de tester si liste.elements est nullptr puisque si c'est le cas, nElements est nécessairement 0.
	for (size_t i : iter::range(nElements_))
		nouvelleListe[i] = elements_[i];
	delete[] elements_;

	elements_ = nouvelleListe;
	capacite_ = nouvelleCapacite;
}