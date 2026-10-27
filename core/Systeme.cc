#include <iostream>
#include <string>
#include <vector>
#include "Vecteur3D.h"
#include "Systeme.h"
#include "Particule.h"
#include "Enceinte.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include <cmath>
using namespace std;

Systeme::~Systeme() {
    for (auto element : collection) {
        delete element;
    }
}

Systeme ::Systeme(double hauteur1, double largeur1, double profondeur1, double temperature1,
                  unsigned int graine)
    : temperature(temperature1), espace(hauteur1, largeur1, profondeur1),
      random(GenerateurAleatoire(graine)),
      tab(hauteur1, vector<vector<deque<size_t>>>(largeur1, vector<deque<size_t>>(profondeur1))) {}

ostream& Systeme::afficher(ostream& sortie) const {
    sortie << "Le systeme est constitué de " << collection.size()
           << " particules, contenues dans l'enceinte suivante :" << endl;
    return sortie;
}

void Systeme ::ajouter_particule(const Particule& autre) {
    collection.push_back(autre.copie()); // on utilise ici la copie polymorphique
}
void Systeme::ajouter_autrement(Particule* part) {
    collection.push_back(part);
}

void Systeme::supprimer() {

    for (auto& element : collection) {
        delete element;
    }
}

ostream& operator<<(ostream& sortie, Systeme const& system) {
    return system.afficher(sortie);
}

void Systeme::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
    espace.dessine_sur(support);
    for (auto const& element : collection) {
        element->dessine_sur(support);
    }
}

void Systeme ::evolue1(double dt) { // cette fonction fait evoluer notre systeme en utilisant cette
                                    // fois la methode collision de l'exercice p9
    cout << "=======---------" << endl;
    choc_parois(dt);
    collision1();
    for (auto const& element : collection) {
        cout << *element;
    }
}

void Systeme::simulation(double dt, unsigned int fois, double epsilon_) {
    cout << "la simulation commence" << endl;
    int nb(fois);
    epsilon = epsilon_;
    do { // on fait evoluer notre systeme "fois" fois
        this->evolue1(dt);
        --nb;
    } while (nb > 0);
}

void Systeme::tirer_pos(Particule& autre) {
    for (int i(0); i < 3; ++i) {
        autre.set_position(
            i,
            random.uniforme(0, espace.get(i))); // pour tirer la coordonnee i, on tire aleatoirement
                                                // un double entre 0 et espace.get(i)
    }
}

void Systeme::tirer_vit(Particule& autre) {
    for (int i(0); i < 3; ++i) {
        autre.set_vitesse(
            i, random.gaussienne(
                   0.0, sqrt(((8.314472) / autre.get_u()) *
                             temperature))); // on tire la coordonnee i a selon une gaussienne
                                             // implemente dans GenerateurAleatoire.h
    }
}

void Systeme::initialiser() {
    for (auto& element : collection) {
        tirer_pos(*element);
        tirer_vit(*element);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

void Systeme::choc_parois(
    double dt) { // cette fonction gere les chocs des particules sur les parois

    for (size_t k(0); k < collection.size(); ++k) {
        collection[k]->evolue(dt);

        int indice(1);
        for (int i(0); i < 3;
             ++i) { // On regarde pour chaques coordonnes si cette derniere
                    // sort de l'einceinte en verifiant qu'elle ne depasse pas une des parois

            if ((collection[k]->get_position().get_coord(i) > espace.get(i))) {
                cout << "La particule " << k + 1 << " rebondit sur la face " << indice << endl;
                collection[k]->set_position(
                    i, espace.get(i) -
                           abs(espace.get(i) -
                               collection[k]->get_position().get_coord(
                                   i))); // la position est la distance de la parois moins la
                                         // distance que la particule a depasse de l'enceinte
                collection[k]->set_vitesse(i, -collection[k]->get_vitesse().get_coord(
                                                  i)); // La vitesse devient oppose a la vitesse
                                                       // avant la rebond contre la parois
            }

            ++indice;

            if ((collection[k]->get_position().get_coord(i) < 0)) {
                cout << "La particule " << k + 1 << " rebondit sur la face " << indice << endl;
                collection[k]->set_position(
                    i, -collection[k]->get_position().get_coord(
                           i)); // la distance que la particule hors de l'einceinte est simplement
                                // sa coordonnee en valeur absolue
                collection[k]->set_vitesse(i, -collection[k]->get_vitesse().get_coord(
                                                  i)); // La vitesse devient oppose a la vitesse
                                                       // avant la rebond contre la parois
            }
            ++indice;
        }
    }
}

void Systeme::collision1() { // cette fonction gere la collision entre particules selon la methode
                             // de l'exercice p9
    for (size_t i(0); i < collection.size() - 1; ++i) {
        vector<int> temp; // on cree un tableau dans lequel on mettra les indices des particules qui
                          // sont a une distance d'au plus epsilon avec collection[i]
        for (size_t j(i + 1); j < collection.size(); ++j) {
            if (collection[i]->rencontre(epsilon, *collection[j])) {
                temp.push_back(j);
            }
        }
        if (!temp.empty()) {
            int randomindex(random.uniforme(
                0,
                temp.size())); // On choisi un entier au hasards entre 0 et temp.size() ce qui nous
                               // permet de tirer aleatoirement un indice dans notre tableau temp.
            int p(temp[randomindex]); // La particule choisit pour etre en collision avec
                                      // collection[i] est donc collection[p]

            cout << "La particule " << p + 1 << " entre en collision avec une autre particule"
                 << endl;
            cout << "Avant le choc : " << endl;
            cout << " part " << p + 1 << " : " << *collection[p] << endl;
            cout << " autre : " << *collection[i] << endl;

            calcul_collision(collection[i], collection[p]);

            cout << "Après le choc : " << endl;
            cout << " part " << p + 1 << " : " << *collection[p] << endl;
            cout << " autre : " << *collection[i] << endl;
        }
    }
}

void Systeme::collision2() { // cette fonction gere la collision entre particules selon la methode
                             // de l'exercice p14
    for (size_t i(0); i < collection.size();
         ++i) { // on assimile un indice a chaques particule et on le push_back dans le tableau
                // correspondant a la position de la particule
        unsigned int x = collection[i]->get_position().get_coord(0);
        unsigned int y = collection[i]->get_position().get_coord(1);
        unsigned int z = collection[i]->get_position().get_coord(2);
        tab[x][y][z].push_back(i);
    }
    for (size_t i(0); i < collection.size();
         ++i) { // on enleve le premier element de notre tableau qui est l'indice correspondant a
                // collection[i]
        unsigned int x = collection[i]->get_position().get_coord(0);
        unsigned int y = collection[i]->get_position().get_coord(1);
        unsigned int z = collection[i]->get_position().get_coord(2);
        tab[x][y][z].pop_front(); // on a ici enleve collection[i] car pop_front enleve le premier
                                  // element du deque

        if (not tab[x][y][z].empty()) { // ce qui implique qu'il y a au moins une autre molecules en
                                        // plus de collection[i] dans la cas [x][y][z]
            size_t randomindex = random.uniforme(
                0, tab[x][y][z].size() -
                       1); // index au hazard parmi les différentes molecules dans le tableau
                           // [x][y][z] pour faire la collisions avec collection[i]
            size_t e = tab[x][y][z][randomindex]; // La particule choisit pour etre en collision
                                                  // avec collection[i] est donc collection[p]

            cout << "La particule " << e + 1 << " entre en collision avec une autre particule"
                 << endl;
            cout << "Avant le choc : " << endl;
            cout << " part " << e + 1 << " : " << *collection[e] << endl;
            cout << " autre : " << *collection[i] << endl;

            calcul_collision(collection[i], collection[e]);

            cout << "Après le choc : " << endl;
            cout << " part " << e + 1 << " : " << *collection[e] << endl;
            cout << " autre : " << *collection[i] << endl;
        }
    }
}

void Systeme::calcul_collision(Particule* num1, Particule* num2) {

    Vecteur3D vg(num2->vg(*num1));
    Vecteur3D vp(num2->get_vitesse() - vg);

    double z(random.uniforme(-vp.norm(), vp.norm()));
    double phi(random.uniforme(0, 2 * M_PI));
    double r(sqrt(vp.norm() * vp.norm() - z * z));

    Vecteur3D v0(
        r * cos(phi), r * sin(phi),
        z); // on tire au hasard v0 en l'initalisant avec les attributs tiree aleatoirements

    num2->set_vitesse(v0 + vg); // on redefinit la vitesse de num1 et de num2
    num1->set_vitesse(vg - (num2->get_masse() / num1->get_masse() * v0));
}

void Systeme ::evolue2(double dt) { // cette fonction fait evoluer notre systeme en utilisant cette
                                    // fois la methode collision de l'exercice p13
    // cout << "=======---------" << endl;
    choc_parois(dt);
    collision2();

    /*for(auto const& element: collection) {
            cout << *element;
    }*/
}
