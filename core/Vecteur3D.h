#pragma once
#include <array>
#include <iostream>


class Vecteur3D {
	
	private:
	std::array <double,3> vecteur;

	
	public:
	double get_coord(int indice) const;
	void set_coord (int indice, double coord );
	std :: ostream& affiche(std::ostream& sortie) const;	
	bool compare(Vecteur3D  const& vecteur1, double err = 1e-10) const;	
    Vecteur3D& operator+=(Vecteur3D const& autre);
	Vecteur3D& operator-=(Vecteur3D const& autre);
	Vecteur3D& operator-();
    Vecteur3D& operator*=(double scalaire);
    double prod_scal(Vecteur3D const& autre) const;
    Vecteur3D& operator ~();
    Vecteur3D& operator ^=(Vecteur3D const& autre);
    double norm() const;
    double norm2() const;
    Vecteur3D unitaire();
	Vecteur3D( double x = 0, double y = 0, double z = 0);  
	

};


	std :: ostream& operator <<(std::ostream& sortie, Vecteur3D const& vec);

    bool operator==(Vecteur3D const& vec1, Vecteur3D const& vec2);
		
	bool operator!=(Vecteur3D const& vec1, Vecteur3D const& vec2);
	
	const Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2);
	
	const Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2);
	
	const Vecteur3D operator ^ (Vecteur3D vec1, Vecteur3D const& vec2);
	
	double operator *(Vecteur3D const& autre , Vecteur3D const& autre1);
	
	const Vecteur3D operator*(Vecteur3D vec1, double scalaire);
	
	const Vecteur3D operator*(double scalaire, Vecteur3D vec1);
