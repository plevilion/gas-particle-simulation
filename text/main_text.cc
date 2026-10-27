#include <iostream>
#include <array>
#include <vector>
#include "particule.h"
#include "Textviewer.h"
#include "Vecteur3D.h"
#include "Enceinte.h"
#include "systeme.h"
#include "GenerateurAleatoire.h"


using namespace std;

int main ()
{
	TextViewer ecran(cout);   // déclare le support à dessin (le terminal dans ce cas là)
	
	// déclare les particules, les ajoute, puis les initialise aléatoirement 
	Helium hel;
	Neon neo;
	Argon arg;
	
	
	Systeme systeme(20, 20 ,20);
	systeme.ajouter_particule(hel);
	systeme.ajouter_particule(neo);
	systeme.ajouter_particule(arg);
	
	systeme.initialiser();
	
	// afficher la composition du système
	systeme.dessine_sur(ecran);
	
	// lance la simulation 10 fois avec dt=1 et epsilon = 1
	systeme.simulation(1, 10, 1);

	
	return 0;
}
