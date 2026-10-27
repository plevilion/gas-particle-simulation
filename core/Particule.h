#pragma once
#include <vector>
#include "Vecteur3D.h"
#include "Dessinable.h"
#include "SupportADessin.h"

// A gas particle: position, velocity and mass. Abstract: each gas is a subclass.
class Particule : public Dessinable {
protected:
    Vecteur3D position;
    Vecteur3D vitesse;
    double masse;

public:
    Particule(Vecteur3D pos = {0, 0, 0}, Vecteur3D vit = {0, 0, 0}, double m = 0.0);
    virtual ~Particule() = default;

    // Polymorphic copy, so that Systeme can store copies of any particle type.
    virtual Particule* copie() const = 0;

    // Molar mass of the gas (g/mol), used to draw initial velocities.
    virtual double get_u() const = 0;

    virtual std::ostream& afficher(std::ostream& sortie) const;

    // Moves the particle in a straight line for a time dt.
    virtual void evolue(double dt);

    Vecteur3D get_position() const;
    void set_position(int indice, double valeur);
    Vecteur3D get_vitesse() const;
    void set_vitesse(int indice, double valeur);
    void set_vitesse(Vecteur3D const& v);
    double get_masse() const;

    // True if the other particle is at distance at most epsilon.
    bool rencontre(double epsilon, Particule const& autre) const;

    // Velocity of the centre of mass of this particle and the other one.
    Vecteur3D vg(Particule const& autre) const;
};

std::ostream& operator<<(std::ostream& sortie, Particule const& particule);

class Neon : public Particule {
public:
    static constexpr double u = 20.1797; // molar mass (g/mol)
    Neon(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse = u);
    Particule* copie() const override;
    double get_u() const override;
    std::ostream& afficher(std::ostream& sortie) const override;
    void dessine_sur(SupportADessin& support) override;
};

class Argon : public Particule {
public:
    static constexpr double u = 39.948; // molar mass (g/mol)
    Argon(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse = u);
    Particule* copie() const override;
    double get_u() const override;
    std::ostream& afficher(std::ostream& sortie) const override;
    void dessine_sur(SupportADessin& support) override;
};

class Helium : public Particule {
public:
    static constexpr double u = 4.002602; // molar mass (g/mol)
    Helium(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse = u);
    Particule* copie() const override;
    double get_u() const override;
    std::ostream& afficher(std::ostream& sortie) const override;
    void dessine_sur(SupportADessin& support) override;
};

// A helium atom that records its past positions, drawn as a trail to show
// Brownian motion.
class Traine : public Helium {
public:
    std::vector<Vecteur3D> points_memorise;

    Traine(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse = u);
    Particule* copie() const override;
    void evolue(double dt) override;
    std::ostream& afficher(std::ostream& sortie) const override;
    void dessine_sur(SupportADessin& support) override;
};
