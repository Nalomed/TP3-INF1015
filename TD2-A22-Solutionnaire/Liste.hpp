#pragma once 
#include <cstddef>
#include <memory>
#include <cassert>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include <list>
using namespace std;

template<typename T>
class Liste {

public:
	Liste() = default;
	Liste() { nElements_ = 0; capacite_ = 1; elements_ = make_unique<shared_ptr<T>[]>(capacite_); }

	T ajouter(shared_ptr <T> d);
	T retirer(const T aRetirer);
	
	

	shared_ptr<T>& operator[](int index) { return elements_[index]; }

	shared_ptr<T> trouverElement(const function<bool(shared_ptr<T>)> critere);

	T changerCapacite(T nouvelleCapacite);
	
	
private:
	int nElements_ = 0;
	T capacite_ = 0;  // Pas besoin de déclarer explicitement un corps de constructeur avec ces initialisations.
	unique_ptr<shared_ptr<T>[]> elements_ = nullptr;
};

//definition des methodes :



template<typename T>
T Liste<T>::ajouter(shared_ptr <T> d)
{
	if (nElements_ == capacite_)
		changerCapacite(max(T(1), capacite_ * 2));
	elements_[nElements_++] = d;
}

template<typename T>
 Liste<T>::shared_ptr<T> trouverElement(const function<bool(shared_ptr<T>)> critere)
{
	for (int i = 0; i < nElements_; i++)
	{
		if (critere(elements_[i]))
			return  elements_[i];
	}
	return nullptr;
}

template<typename T>
T Liste<T>::retirer(const T aRetirer)
{
	for (T& d : enSpan()) {
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
	{
		unique_ptr<shared_ptr<T>[]> nouveauxElements = make_unique<shared_ptr<T>[]>(nouvelleCapacite);

		for (unsigned i = 0; i < nouvelleCapacite; ++i)
		{
			if (i < capacite_)
			{
				
				nouveauxElements[i] = move(elements_[i]);
			}
			else
			{
			
				nouveauxElements[i] = make_shared<T>();
			}
		}

		
		elements_ = move(nouveauxElements);
		capacite_ = nouvelleCapacite;
	}
}