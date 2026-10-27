#include <iostream>
#include <cmath>
#include <array>
#include "Vecteur3D.h"
using namespace std;

Vecteur3D::Vecteur3D(double x, double y, double z) {
    vecteur = {x, y, z};
}

void Vecteur3D::set_coord(int indice, double coord) {
    vecteur[indice] = coord;
}

double Vecteur3D::get_coord(int indice) const {
    return vecteur[indice];
}

// Used to define operator<<.
ostream& Vecteur3D::affiche(ostream& sortie) const {
    for (auto element : vecteur) {
        sortie << element << " ";
    }
    return sortie;
}

bool Vecteur3D::compare(Vecteur3D const& autre, double err) const {
    for (int i(0); i <= 2; ++i) {
        if (abs(vecteur[i] - autre.vecteur[i]) >= err) {
            return false;
        }
    }
    return true;
}

double Vecteur3D::prod_scal(Vecteur3D const& autre) const {
    double resultat(0);
    for (int i(0); i <= 2; ++i) {
        resultat += vecteur[i] * autre.vecteur[i];
    }
    return resultat;
}

double Vecteur3D::norm() const {
    return sqrt(norm2());
}

double Vecteur3D::norm2() const {
    return prod_scal(*this);
}

Vecteur3D Vecteur3D::unitaire() const {
    Vecteur3D resultat(*this);
    return ~resultat;
}

// Internal operators

Vecteur3D& Vecteur3D::operator*=(double scalaire) {
    for (int i(0); i <= 2; ++i) {
        vecteur[i] *= scalaire;
    }
    return *this;
}

Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& autre) {
    for (int i(0); i <= 2; ++i) {
        vecteur[i] += autre.vecteur[i];
    }
    return *this;
}

Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& autre) {
    for (int i(0); i <= 2; ++i) {
        vecteur[i] -= autre.vecteur[i];
    }
    return *this;
}

Vecteur3D& Vecteur3D::operator^=(Vecteur3D const& autre) {
    Vecteur3D copie(*this);
    vecteur[0] = copie.vecteur[1] * autre.vecteur[2] - copie.vecteur[2] * autre.vecteur[1];
    vecteur[1] = copie.vecteur[2] * autre.vecteur[0] - copie.vecteur[0] * autre.vecteur[2];
    vecteur[2] = copie.vecteur[0] * autre.vecteur[1] - copie.vecteur[1] * autre.vecteur[0];
    return *this;
}

Vecteur3D Vecteur3D::operator-() const {
    return Vecteur3D(-vecteur[0], -vecteur[1], -vecteur[2]);
}

Vecteur3D& Vecteur3D::operator~() {
    double n(norm());
    for (int i(0); i <= 2; ++i) {
        vecteur[i] /= n;
    }
    return *this;
}

// External operators

const Vecteur3D operator^(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1 ^= vec2;
}

double operator*(Vecteur3D const& vec1, Vecteur3D const& vec2) {
    return vec1.prod_scal(vec2);
}

ostream& operator<<(ostream& sortie, Vecteur3D const& vec) {
    return vec.affiche(sortie);
}

bool operator==(Vecteur3D const& vec1, Vecteur3D const& vec2) {
    return vec1.compare(vec2);
}

bool operator!=(Vecteur3D const& vec1, Vecteur3D const& vec2) {
    return not vec1.compare(vec2);
}

const Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1 += vec2;
}

const Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1 -= vec2;
}

const Vecteur3D operator*(Vecteur3D vec1, double scalaire) {
    return vec1 *= scalaire;
}

const Vecteur3D operator*(double scalaire, Vecteur3D vec1) {
    return vec1 *= scalaire;
}
