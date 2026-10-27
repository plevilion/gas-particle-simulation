#pragma once

class Neon;
class Argon;
class Helium;
class Traine;
class Enceinte;
class Systeme;

class SupportADessin
{
	public:
	virtual ~SupportADessin() = default;
	SupportADessin(SupportADessin const&)            = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
    SupportADessin(SupportADessin&&)            = default;
    SupportADessin& operator=(SupportADessin&&) = default;
 
    SupportADessin() = default;

	virtual void dessine(Neon const&) = 0;
	virtual void dessine(Helium const&) = 0;
	virtual void dessine(Argon const&) = 0;
	virtual void dessine(Enceinte const&) = 0;
	virtual void dessine(Systeme const&) = 0;
	virtual void dessine(Traine const&) = 0;

};

