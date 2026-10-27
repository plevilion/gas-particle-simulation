#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "Systeme.h"
using namespace std;

Systeme::Systeme(double hauteur, double largeur, double profondeur, double temperature,
                 unsigned int graine)
    : temperature(temperature), espace(hauteur, largeur, profondeur),
      random(GenerateurAleatoire(graine)),
      cellules(size_t(espace.get(0)) * size_t(espace.get(1)) * size_t(espace.get(2))) {}

Systeme::~Systeme() {
    for (auto element : collection) {
        delete element;
    }
}

ostream& Systeme::afficher(ostream& sortie) const {
    return sortie << "System of " << collection.size() << " particles";
}

ostream& operator<<(ostream& sortie, Systeme const& systeme) {
    return systeme.afficher(sortie);
}

void Systeme::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
    espace.dessine_sur(support);
    for (auto const& element : collection) {
        element->dessine_sur(support);
    }
}

void Systeme::set_journal(ostream& sortie) {
    journal = &sortie;
}

void Systeme::ajouter_particule(const Particule& autre) {
    collection.push_back(autre.copie()); // polymorphic copy
}

void Systeme::ajouter_autrement(Particule* part) {
    collection.push_back(part);
}

// Initial state

void Systeme::tirer_pos(Particule& autre) {
    for (int i(0); i < 3; ++i) {
        autre.set_position(i, random.uniforme(0, espace.get(i)));
    }
}

void Systeme::tirer_vit(Particule& autre) {
    // Each velocity component follows a normal distribution of variance RT/M
    // (R = 8.314472 J/(mol K), M = molar mass of the gas): Maxwell-Boltzmann.
    double ecart_type(sqrt(8.314472 / autre.get_u() * temperature));
    for (int i(0); i < 3; ++i) {
        autre.set_vitesse(i, random.gaussienne(0.0, ecart_type));
    }
}

void Systeme::initialiser() {
    for (auto& element : collection) {
        tirer_pos(*element);
        tirer_vit(*element);
    }
}

// Time evolution

void Systeme::evolue1(double dt) {
    choc_parois(dt);
    collision1();
}

void Systeme::evolue2(double dt) {
    choc_parois(dt);
    collision2();
}

void Systeme::simulation(double dt, unsigned int nb_pas, double epsilon_, SupportADessin& support) {
    epsilon = epsilon_;
    for (unsigned int pas(1); pas <= nb_pas; ++pas) {
        if (journal) {
            *journal << "\n=== Step " << pas << " ===" << endl;
        }
        evolue1(dt);
        for (auto const& element : collection) {
            element->dessine_sur(support);
        }
    }
}

void Systeme::choc_parois(double dt) {
    for (size_t k(0); k < collection.size(); ++k) {
        Particule& p(*collection[k]);
        p.evolue(dt);

        // For each axis, a particle that left the box is reflected back inside
        // and the corresponding velocity component changes sign.
        for (int i(0); i < 3; ++i) {
            double taille(espace.get(i));
            if (p.get_position().get_coord(i) > taille) {
                if (journal) {
                    *journal << "Particle " << k + 1 << " bounces on face " << 2 * i + 1 << endl;
                }
                p.set_position(i, 2 * taille - p.get_position().get_coord(i));
                p.set_vitesse(i, -p.get_vitesse().get_coord(i));
            }
            if (p.get_position().get_coord(i) < 0) {
                if (journal) {
                    *journal << "Particle " << k + 1 << " bounces on face " << 2 * i + 2 << endl;
                }
                p.set_position(i, -p.get_position().get_coord(i));
                p.set_vitesse(i, -p.get_vitesse().get_coord(i));
            }
        }
    }
}

// Collisions between particles

void Systeme::collision1() {
    for (size_t i(0); i + 1 < collection.size(); ++i) {
        // Particles after i that are closer than epsilon
        vector<size_t> voisines;
        for (size_t j(i + 1); j < collection.size(); ++j) {
            if (collection[i]->rencontre(epsilon, *collection[j])) {
                voisines.push_back(j);
            }
        }
        if (!voisines.empty()) {
            // i collides with one of them, chosen at random
            size_t k(min(size_t(random.uniforme(0, voisines.size())), voisines.size() - 1));
            calcul_collision(collection[i], collection[voisines[k]]);
            if (journal) {
                *journal << "Particles " << i + 1 << " and " << voisines[k] + 1 << " collide"
                         << endl;
            }
        }
    }
}

size_t Systeme::cellule(Particule const& p) const {
    size_t indices[3];
    for (int k(0); k < 3; ++k) {
        // Cell coordinate along axis k, kept inside the grid
        long taille(espace.get(k));
        long c(long(floor(p.get_position().get_coord(k))));
        indices[k] = size_t(max(0L, min(c, taille - 1)));
    }
    return (indices[0] * size_t(espace.get(1)) + indices[1]) * size_t(espace.get(2)) + indices[2];
}

void Systeme::collision2() {
    // The box is split into unit cells. Each cell lists its particles in
    // increasing order. Each particle then collides with a random particle
    // among those that come after it in the same cell.
    vector<size_t> cellule_de(collection.size());
    for (size_t i(0); i < collection.size(); ++i) {
        cellule_de[i] = cellule(*collection[i]);
        cellules[cellule_de[i]].push_back(i);
    }

    for (size_t i(0); i < collection.size(); ++i) {
        vector<size_t> const& occupants(cellules[cellule_de[i]]);
        auto apres_i(upper_bound(occupants.begin(), occupants.end(), i));
        size_t nb_suivants(occupants.end() - apres_i);
        if (nb_suivants > 0) {
            size_t k(min(size_t(random.uniforme(0, nb_suivants)), nb_suivants - 1));
            size_t e(*(apres_i + k));
            calcul_collision(collection[i], collection[e]);
            if (journal) {
                *journal << "Particles " << i + 1 << " and " << e + 1 << " collide" << endl;
            }
        }
    }

    for (size_t c : cellule_de) {
        cellules[c].clear();
    }
}

void Systeme::calcul_collision(Particule* num1, Particule* num2) {
    // In the centre-of-mass frame, num2's velocity keeps its norm but gets a
    // uniformly random direction; num1's velocity follows from momentum
    // conservation. Momentum and kinetic energy are both conserved.
    Vecteur3D vg(num2->vg(*num1));
    Vecteur3D vp(num2->get_vitesse() - vg);

    double n(vp.norm());
    double z(random.uniforme(-n, n));
    double phi(random.uniforme(0, 2 * M_PI));
    double r(sqrt(max(0.0, n * n - z * z)));
    Vecteur3D v0(r * cos(phi), r * sin(phi), z);

    num2->set_vitesse(v0 + vg);
    num1->set_vitesse(vg - (num2->get_masse() / num1->get_masse()) * v0);
}
