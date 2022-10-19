#pragma once
#include <cstddef>
#include "gsl/span"
// La déclaration suivante plutôt qu'un #include "Jeu.hpp" est nécessaire sinon il y aurait une boucle d'inclusion (ListeJeux.hpp > Jeu.hpp > ListeConcepteurs.hpp > Concepteur.hpp > ListeJeux.hpp), la boucle serait arrêtée par le "pragma once" mais ListeJeux ne serait alors pas déclaré lors de la compilation de Concepteur.
struct Jeu;  // Déclaration avancée ("forward declaration") pour pouvoir utilise le nom du type avant qu'il soit complètement défini.

struct ListeJeux
{
	std::size_t nElements, capacite;
	Jeu** elements;
};

gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste);
void changerTailleListeJeux(ListeJeux& liste, std::size_t nouvelleCapacite);
void ajouterJeu(ListeJeux& liste, Jeu* jeu);
