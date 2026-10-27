#pragma once
#include <array>
#include <iostream>

// A vector of R^3 (positions and velocities).
class Vecteur3D {

private:
    std::array<double, 3> vecteur;

public:
    Vecteur3D(double x = 0, double y = 0, double z = 0);

    double get_coord(int indice) const;
    void set_coord(int indice, double coord);
    std::ostream& affiche(std::ostream& sortie) const;

    // True if every coordinate differs by less than err.
    bool compare(Vecteur3D const& autre, double err = 1e-10) const;

    Vecteur3D& operator+=(Vecteur3D const& autre);
    Vecteur3D& operator-=(Vecteur3D const& autre);
    Vecteur3D& operator*=(double scalaire);
    Vecteur3D& operator^=(Vecteur3D const& autre); // cross product
    Vecteur3D operator-() const;                   // opposite vector
    Vecteur3D& operator~();                        // normalises this vector in place

    double prod_scal(Vecteur3D const& autre) const; // dot product
    double norm() const;
    double norm2() const; // squared norm
    Vecteur3D unitaire() const;
};

std::ostream& operator<<(std::ostream& sortie, Vecteur3D const& vec);

bool operator==(Vecteur3D const& vec1, Vecteur3D const& vec2);
bool operator!=(Vecteur3D const& vec1, Vecteur3D const& vec2);

const Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2);
const Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2);
const Vecteur3D operator^(Vecteur3D vec1, Vecteur3D const& vec2); // cross product
double operator*(Vecteur3D const& vec1, Vecteur3D const& vec2);   // dot product
const Vecteur3D operator*(Vecteur3D vec1, double scalaire);
const Vecteur3D operator*(double scalaire, Vecteur3D vec1);
