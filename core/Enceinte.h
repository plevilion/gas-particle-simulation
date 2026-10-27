#pragma once
#include <array>
#include <iostream>
#include "Dessinable.h"
#include "SupportADessin.h"

// The box containing the gas: [0, hauteur] x [0, largeur] x [0, profondeur].
class Enceinte : public Dessinable {
private:
    std::array<int, 3> espace;

public:
    Enceinte(int hauteur = 20, int largeur = 20, int profondeur = 20);

    // Size of the box along axis indice (0, 1 or 2).
    int get(int indice) const;

    std::ostream& affiche(std::ostream& sortie) const;
    void dessine_sur(SupportADessin& support) override;
};

std::ostream& operator<<(std::ostream& sortie, Enceinte const& enceinte);
