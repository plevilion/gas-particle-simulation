#pragma once
#include "Dessinable.h"
#include "SupportADessin.h"
#include <array>
#include "Particule.h"

class Enceinte : public Dessinable {

private:
    std::array<int, 3> espace;

public:
    virtual void dessine_sur(SupportADessin& support) override;

    std::ostream& affiche(std::ostream& sortie) const;

    Enceinte(int hauteur1 = 20, int largeur1 = 20, int profondeur1 = 20);

    int get(int indice) const;
};

std::ostream& operator<<(std::ostream& sortie, Enceinte enc);
