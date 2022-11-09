#pragma once

#include<iostream>

using namespace std;

class Affichable
{
public:
	virtual ~Affichable() = default;

	virtual ostream& afficher(ostream& os) const = 0;
	virtual ostream& changerCouleur(ostream& os, char couleur) const = 0;
};
