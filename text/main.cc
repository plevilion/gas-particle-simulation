#include <iostream>
#include "Particule.h"
#include "Systeme.h"
#include "TextViewer.h"
using namespace std;

// Terminal version: three atoms in a 20 x 20 x 20 box, ten steps of the
// simulation, with every bounce and collision printed.
int main() {
    TextViewer ecran(cout);

    Systeme systeme(20, 20, 20);
    systeme.ajouter_particule(Helium());
    systeme.ajouter_particule(Neon());
    systeme.ajouter_particule(Argon());
    systeme.initialiser(); // random positions and velocities
    systeme.set_journal(cout);

    cout << "Initial state" << endl;
    systeme.dessine_sur(ecran);

    // 10 steps with dt = 1; particles closer than 1 collide
    systeme.simulation(1, 10, 1, ecran);

    return 0;
}
