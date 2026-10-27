#pragma once
#include <iostream>
#include <vector>
#include "Particule.h"
#include "Enceinte.h"
#include "GenerateurAleatoire.h"
#include "Dessinable.h"
#include "SupportADessin.h"

// The gas: a box and the particles it contains, with the time evolution
// (free flight, bounces on the walls, collisions between particles).
class Systeme : public Dessinable {
private:
    double epsilon = 1; // collision distance for collision1()
    double temperature; // in kelvin, sets the initial velocities
    Enceinte espace;
    GenerateurAleatoire random;

    // Owned particles (pointers, so that they can be of any subclass).
    std::vector<Particule*> collection;

    // Grid of unit cells used by collision2(): cellules[c] lists the
    // particles currently in cell c.
    std::vector<std::vector<size_t>> cellules;

    // Optional log of bounces and collisions (nullptr: no log).
    std::ostream* journal = nullptr;

    // Index in `cellules` of the cell containing particle p.
    size_t cellule(Particule const& p) const;

    Systeme& operator=(Systeme const& autre) = delete;
    Systeme(Systeme const& autre) = delete;

public:
    Systeme(double hauteur, double largeur, double profondeur, double temperature = 293.15,
            unsigned int graine = 123456);
    ~Systeme();

    std::ostream& afficher(std::ostream& sortie) const;
    void dessine_sur(SupportADessin& support) override;
    void set_journal(std::ostream& sortie);

    // Adds a copy of the particle.
    void ajouter_particule(const Particule& autre);
    // Adds a particle created with new; the system takes ownership.
    void ajouter_autrement(Particule* part);

    // Draws random positions (uniform in the box) and velocities
    // (Maxwell-Boltzmann at the system's temperature) for all particles.
    void initialiser();
    void tirer_pos(Particule& autre);
    void tirer_vit(Particule& autre);

    // One time step, with collisions between particles closer than epsilon
    // (all pairs are tested: O(n^2)).
    void evolue1(double dt);
    // One time step, with collisions between particles in the same unit cell
    // of the box (O(n)).
    void evolue2(double dt);

    // Runs nb_pas steps of evolue1 and draws the particles after each step.
    void simulation(double dt, unsigned int nb_pas, double epsilon, SupportADessin& support);

    // Moves every particle and reflects it on the walls it crossed.
    void choc_parois(double dt);
    void collision1();
    void collision2();
    void calcul_collision(Particule* num1, Particule* num2);
};

std::ostream& operator<<(std::ostream& sortie, Systeme const& systeme);
