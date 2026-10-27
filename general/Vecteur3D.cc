
#include <iostream>
#include <cmath>
#include <array>
#include "Vecteur3D.h"
using namespace std;



    		
    
    //Constructeur
     		
    Vecteur3D::Vecteur3D(double x, double y, double z) {
		vecteur = { x, y, z};
	}
		
	
	// defintion methode class
	
	void Vecteur3D::set_coord (int indice, double coord ){
		
		vecteur[indice] = coord;
	}
	
	double Vecteur3D::get_coord(int indice) const {
		return vecteur[indice];
	}

	
	ostream& Vecteur3D::affiche(ostream& sortie) const { //methode permettant la definition de l'operateur <<
		for ( auto element : vecteur) {
			sortie << element << " ";
		}
		return sortie;
	}
		
	bool Vecteur3D::compare(Vecteur3D const& vecteur1, double err) const {
		//Verifie que chaque coordonnees de l'instance courant est egale a celles du vecteur1
		return ( (abs(vecteur[0] - vecteur1.vecteur[0] < err) and (abs(vecteur[1]-vecteur1.vecteur[1]) < err) and (abs(vecteur[2]-vecteur1.vecteur[2]) < err)));
	}	

  double Vecteur3D::prod_scal(Vecteur3D  const& autre) const{
	  double resultat(0);
	  for (int i(0); i <= 2; ++i) {
		  resultat += vecteur[i] * autre.vecteur[i];
	  }
    return resultat;
	}

  
   double Vecteur3D::norm() const {
	   return sqrt(vecteur[0]*vecteur[0] + vecteur[1]*vecteur[1] + vecteur[2]*vecteur[2]);
   }
   
   double Vecteur3D::norm2 () const {
	   return norm() *norm();
   }
   
   Vecteur3D Vecteur3D::unitaire() {
	   Vecteur3D resultat;
	   for(int i(0); i <= 2; ++i) {
		   resultat.set_coord(i, vecteur[i]/norm());
	   }
	   return resultat;
   }
	  
	//operateur interne
	
	  Vecteur3D& Vecteur3D::operator*=(double scalaire){
	   for (int i(0); i <= 2; ++i) {
			vecteur[i] = scalaire*vecteur[i];
	   }
   return *this;
	}
	
	 Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& autre) {
		for (int i(0); i <= 2; ++i) {
			vecteur[i] = vecteur[i] + autre.vecteur[i];
		}
	return *this;
	}
	
	Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& autre) {
		for (int i(0); i <= 2; ++i) {
			vecteur[i] = vecteur[i] - autre.vecteur[i];
		}
	return *this;
	}
	
	Vecteur3D& Vecteur3D::operator ^=(Vecteur3D const& autre) {
	  Vecteur3D resultat(vecteur[0],vecteur[1],vecteur[2]);
	  
		  vecteur[0] = (resultat.vecteur[1]*autre.vecteur[2] - resultat.vecteur[2]*autre.vecteur[1]); 
		  vecteur[1] = (resultat.vecteur[2]*autre.vecteur[0] - resultat.vecteur[0]*autre.vecteur[2]);
		  vecteur[2] = (resultat.vecteur[0]*autre.vecteur[1] - resultat.vecteur[1]*autre.vecteur[0]);
	  
	  return *this;
  }	

	Vecteur3D& Vecteur3D::operator-() {
		for (int i(0); i <= 2; ++i) {
			vecteur[i] = -vecteur[i];
		}
		return *this;
	}
	
	Vecteur3D& Vecteur3D::operator ~() {
		  Vecteur3D resultat;
		 for(int i(0); i <= 2; ++i) {
			vecteur[i] = (vecteur[i]/norm());
		  }
		 return *this;
	}


	//operateur externe
	
	const Vecteur3D operator ^ (Vecteur3D vec1, Vecteur3D const& vec2) { return vec1 ^= vec2; }
	
	double operator *(Vecteur3D const& autre , Vecteur3D const& autre1) { return autre.prod_scal(autre1); }
	
	ostream& operator<<(ostream& sortie, Vecteur3D const& vec) { return vec.affiche(sortie);  } // car la methode affiche renvoie bien un ostream&
	
	bool operator==(Vecteur3D const& vec1, Vecteur3D const& vec2) { return vec1.compare(vec2); }
		
	bool operator!=(Vecteur3D const& vec1, Vecteur3D const& vec2) { return not vec1.compare(vec2); }
	
	const Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2) { return vec1+=vec2; }
	
	const Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2) { return vec1-=vec2; }
	
	const Vecteur3D operator*(Vecteur3D vec1, double scalaire) { return vec1*=scalaire; }
	
	const Vecteur3D operator*(double scalaire, Vecteur3D vec1) { return vec1*=scalaire; }

	
