#include <iostream>
#include <array>
#include "particule.h"
#include "Vecteur3D.h"
#include "SupportADessin.h"
#include "Dessinable.h"
using namespace std;


  
 // Classe Particule 
  
  Particule::Particule(Vecteur3D pos, Vecteur3D vit, double m)
:position(pos), vitesse(vit), masse(m)
{}

Particule::Particule(Particule const& part)
: position(part.position), vitesse(part.vitesse), masse(part.masse)
{}  
  
  Particule :: ~Particule () {}

  void Particule :: evolue(double dt) { // l'evolution d'une particule reside en la mise a jour de sa position qui va varier selon le temp dt et la vitesse de la particule
	  position += dt * vitesse;
  }
 
  void Particule:: set_vitesse(int indice,double autre) {
	  vitesse.set_coord(indice, autre);
  }
 
  void Particule:: set_position(int indice,double autre) {
	  position.set_coord(indice, autre);
  }
 Vecteur3D Particule :: get_position() const {
	 return position;
 }
 
 Vecteur3D Particule :: get_vitesse() const {
	 return vitesse;
 }
 
 double  Particule:: get_masse() const {return masse;}
 
  Vecteur3D Particule:: vg( const Particule& autre) const{  // calcul de la vitesse vg ( necessaire pour les collisions)
	 return ((masse/(masse + autre.masse))*vitesse) + ((autre.masse/ (masse + autre.masse))*autre.vitesse);
  } 
	
 void Particule :: set_vitesse ( Vecteur3D const& autre) {
	 vitesse = autre;
 }
 
  bool Particule::rencontre(double epsilon, Particule const& Q) const { // cette fonction indique si la particule prise en parametre est a une distance inferieur de epslion de la particule de la classe
	  if((position-Q.position).norm() <= epsilon)  return true;  else return false;
  }
  
ostream& Particule::afficher(ostream& sortie) const // fonction permettant la definiton de l'operateur <<
{
	sortie << "pos : ";
	position.affiche(sortie);
	sortie << "; v : ";
	vitesse.affiche(sortie);
	sortie << "; m : " << masse << endl;
	return sortie;
}

ostream& operator<<(ostream& sortie, Particule const& particule) { return particule.afficher(sortie); }


//Classe Neon

Neon :: ~Neon () {
	cout << " Un neon a été détruit"  << endl;
}

ostream& Neon::afficher(ostream& sortie) const //surcharge
{
	sortie << "particule Néon : ";
	Particule::afficher(sortie);
	return sortie;
}

Neon::Neon(Vecteur3D position, Vecteur3D vitesse, double masse)
: Particule(position, vitesse, masse)
{}

double Neon:: get_u() {return u;}

void Neon::dessine_sur(SupportADessin& support)  { support.dessine(*this);  }

Particule* Neon:: copie() const {
	return new Neon(*this);
}


// class argon

ostream& Argon::afficher(ostream& sortie) const  //surcharge
{
	sortie << "particule Argon : ";
	Particule::afficher(sortie);
	return sortie;
}

Argon::Argon(Vecteur3D position, Vecteur3D vitesse, double masse)
: Particule(position, vitesse, masse)
{}

Argon :: ~Argon() {
	cout << " Un Argon a été détruit"  << endl;
}

void Argon::dessine_sur(SupportADessin& support)  { support.dessine(*this);  }

double Argon:: get_u() {return u;}

Particule* Argon:: copie() const {
	return new Argon(*this);
}

// classe Helium

Helium :: ~Helium() {
	cout << " Un Helium a été détruit"  << endl;
}

ostream& Helium::afficher(ostream& sortie) const  //surcharge
{
	sortie << "particule Helium : ";
	Particule::afficher(sortie);
	return sortie;
}

Helium::Helium(Vecteur3D position, Vecteur3D vitesse, double masse)
: Particule(position, vitesse, masse)
{}

void Helium::dessine_sur(SupportADessin& support)  { support.dessine(*this);  }

double Helium:: get_u() {return u;}

Particule* Helium:: copie() const {
	return new Helium(*this);
}

// classe Traine

Traine :: ~Traine() {
	cout << " Un Traine a été détruit"  << endl;
}

ostream& Traine::afficher(ostream& sortie) const 
{
	sortie << "particule trainée : ";
	Particule::afficher(sortie);
	return sortie;
}

Traine::Traine(Vecteur3D position, Vecteur3D vitesse, double masse)
: Helium(position, vitesse, masse)
{}

void Traine::dessine_sur(SupportADessin& support)  { support.dessine(*this);  }

Particule* Traine:: copie() const {
	return new Traine(*this);
}

void Traine::evolue(double dt) {
	points_memorise.push_back(position); // pour faire la trainee
	position += dt * vitesse; 

}



