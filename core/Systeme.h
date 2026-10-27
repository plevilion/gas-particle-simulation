#pragma once
#include "Particule.h"
#include "Enceinte.h"
#include <vector>
#include "GenerateurAleatoire.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include <cmath>
#include <deque>


class Systeme : public Dessinable {
	
	private:
	
	double epsilon = 1;
	double temperature;
	Enceinte espace;
	GenerateurAleatoire random; 

	std::vector<std::vector<std::vector<std::deque<size_t>>>> tab;
	std:: vector <Particule*> collection;
	
	Systeme& operator =(Systeme const& autre) = delete;
	Systeme (Systeme const& autre) = delete;

	public:
	
	Systeme(double hauteur1, double largeur1, double profondeur1, double temperature1 = 293.15,unsigned int graine=123456);
	~Systeme();
	std::ostream& afficher(std::ostream& sortie) const;
	void ajouter_particule(const Particule& autre);
	void ajouter_autrement(Particule* part);
	void supprimer();
	void simulation(double dt, unsigned int fois, double epsilon_);
	
	virtual void dessine_sur(SupportADessin& support) override;	

	void tirer_pos( Particule& autre);
	void tirer_vit( Particule& autre);
	void initialiser();

	void evolue1(double dt);
	void evolue2(double dt);
	
	void choc_parois(double dt);
	
	void collision1();
	void collision2();

	void calcul_collision( Particule* num1, Particule* num2);
};

std::ostream& operator<<(std::ostream& sortie, Systeme const& system);

