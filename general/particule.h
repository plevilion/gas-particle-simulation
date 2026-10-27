#pragma once 
#include <vector>
#include "Vecteur3D.h"
#include "Dessinable.h"
#include "SupportADessin.h"

class Particule : public Dessinable
{
	protected :
	
	Vecteur3D position;
	Vecteur3D vitesse;
	double masse;
	
	public : 
	virtual double get_u() = 0; // Renvoie la masse atomique associe au type de la particule
	Particule(Vecteur3D pos = {0, 0, 0}, Vecteur3D vit = {0, 0, 0}, double m = 0.0);
	virtual std::ostream& afficher(std::ostream& sortie) const;
	Particule(Particule const& part);
	virtual void evolue(double dt);
	Vecteur3D get_position() const;
	void set_position(int indice, double autre);
	Vecteur3D get_vitesse() const;
	void set_vitesse(int indice, double autre);
	void set_vitesse( Vecteur3D const& autre);
	bool rencontre(double epsilon, Particule const& Q) const;
	Vecteur3D vg( const Particule& autre) const;
	double get_masse() const;
	virtual ~Particule ();
	virtual Particule*  copie() const= 0; //copie polymorphique
};

std::ostream& operator<<(std::ostream& sortie, Particule const& particule);
	
	
	
class Neon : public Particule
{
	public : 
	double static constexpr u = 20.1797; // masse atomique
	double get_u() override;
	virtual std::ostream& afficher(std::ostream& sortie) const override;
	Neon(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse =u);
	virtual void dessine_sur(SupportADessin& support) override;	
	~Neon() override;
	Particule* copie() const override; // copie polymorphique
};

class Argon : public Particule
{
	public :
	double static constexpr u = 39.948; // masse atomique
	double get_u() override; 
	virtual std::ostream& afficher(std::ostream& sortie) const override;
	Argon(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse =u);
	virtual void dessine_sur(SupportADessin& support) override;	
	~Argon () override;
	Particule* copie() const override; // copie polymorphique
};

class Helium : public Particule
{
	public : 
	double static constexpr u = 4.002602; // masse atomique
	double get_u() override;
	virtual std::ostream& afficher(std::ostream& sortie) const override;
	Helium(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse =u);
	virtual void dessine_sur(SupportADessin& support) override;	
	~Helium () override;
	Particule* copie()  const override ; // copie polymorphique
};

class Traine : public Helium
{
	public : 
	std::vector<Vecteur3D> points_memorise;
	void evolue(double dt);
	virtual std::ostream& afficher(std::ostream& sortie) const override;
	Traine(Vecteur3D position = {0, 0, 0}, Vecteur3D vitesse = {0, 0, 0}, double masse =u);
	virtual void dessine_sur(SupportADessin& support) override;	
	~Traine () override;
	Particule* copie()  const override ; // copie polymorphique
};
