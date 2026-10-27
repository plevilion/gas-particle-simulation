#include <iostream>
#include "Particule.h"
#include "SupportADessin.h"
using namespace std;

// Particule

Particule::Particule(Vecteur3D pos, Vecteur3D vit, double m)
    : position(pos), vitesse(vit), masse(m) {}

void Particule::evolue(double dt) {
    position += dt * vitesse;
}

void Particule::set_vitesse(int indice, double valeur) {
    vitesse.set_coord(indice, valeur);
}

void Particule::set_vitesse(Vecteur3D const& v) {
    vitesse = v;
}

void Particule::set_position(int indice, double valeur) {
    position.set_coord(indice, valeur);
}

Vecteur3D Particule::get_position() const {
    return position;
}

Vecteur3D Particule::get_vitesse() const {
    return vitesse;
}

double Particule::get_masse() const {
    return masse;
}

Vecteur3D Particule::vg(Particule const& autre) const {
    return (masse / (masse + autre.masse)) * vitesse +
           (autre.masse / (masse + autre.masse)) * autre.vitesse;
}

bool Particule::rencontre(double epsilon, Particule const& autre) const {
    return (position - autre.position).norm() <= epsilon;
}

ostream& Particule::afficher(ostream& sortie) const {
    return sortie << "pos: " << position << "; v: " << vitesse << "; m: " << masse;
}

ostream& operator<<(ostream& sortie, Particule const& particule) {
    return particule.afficher(sortie);
}

// Neon

Neon::Neon(Vecteur3D position, Vecteur3D vitesse, double masse)
    : Particule(position, vitesse, masse) {}

Particule* Neon::copie() const {
    return new Neon(*this);
}

double Neon::get_u() const {
    return u;
}

ostream& Neon::afficher(ostream& sortie) const {
    sortie << "Neon    ";
    return Particule::afficher(sortie);
}

void Neon::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
}

// Argon

Argon::Argon(Vecteur3D position, Vecteur3D vitesse, double masse)
    : Particule(position, vitesse, masse) {}

Particule* Argon::copie() const {
    return new Argon(*this);
}

double Argon::get_u() const {
    return u;
}

ostream& Argon::afficher(ostream& sortie) const {
    sortie << "Argon   ";
    return Particule::afficher(sortie);
}

void Argon::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
}

// Helium

Helium::Helium(Vecteur3D position, Vecteur3D vitesse, double masse)
    : Particule(position, vitesse, masse) {}

Particule* Helium::copie() const {
    return new Helium(*this);
}

double Helium::get_u() const {
    return u;
}

ostream& Helium::afficher(ostream& sortie) const {
    sortie << "Helium  ";
    return Particule::afficher(sortie);
}

void Helium::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
}

// Traine

Traine::Traine(Vecteur3D position, Vecteur3D vitesse, double masse)
    : Helium(position, vitesse, masse) {}

Particule* Traine::copie() const {
    return new Traine(*this);
}

void Traine::evolue(double dt) {
    points_memorise.push_back(position); // keeps the trail
    position += dt * vitesse;
}

ostream& Traine::afficher(ostream& sortie) const {
    sortie << "Tracer  ";
    return Particule::afficher(sortie);
}

void Traine::dessine_sur(SupportADessin& support) {
    support.dessine(*this);
}
