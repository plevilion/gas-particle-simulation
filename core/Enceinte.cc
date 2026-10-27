#include <iostream>
#include "Enceinte.h"
using namespace std;

Enceinte::Enceinte(int hauteur, int largeur, int profondeur) {
    espace = {hauteur, largeur, profondeur};
}

int Enceinte::get(int indice) const {
    return espace[indice];
}

ostream& Enceinte::affiche(ostream& sortie) const {
    return sortie << "Box: " << espace[0] << " x " << espace[1] << " x " << espace[2];
}

void Enceinte::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
}

ostream& operator<<(ostream& sortie, Enceinte const& enceinte) {
    return enceinte.affiche(sortie);
}
