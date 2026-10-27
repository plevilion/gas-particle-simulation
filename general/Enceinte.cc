#include <iostream>
#include "Enceinte.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "particule.h"
#include <algorithm>
#include <array>
using namespace std;


Enceinte::Enceinte ( int hauteur1 , int largeur1 , int profondeur1 )
{espace[0] = hauteur1;
espace[1] = largeur1;
espace[2] = profondeur1;
}
	
void Enceinte::dessine_sur(SupportADessin& support) { support.dessine(*this);  }	
	
ostream& Enceinte::affiche(ostream& sortie) const { // Cette methode nous permet de definir l'operator <<
	sortie << "Enceinte : hauteur : " << espace[0] << "; largeur : " << espace[1]<< "; profondeur : " << espace[2] << endl;
	return sortie;
}

ostream& operator<<(ostream& sortie, Enceinte enc) { return enc.affiche(sortie); } // car la methode affiche renvoie bien un ostream&

int Enceinte:: get( int indice) const { return espace[indice];}
