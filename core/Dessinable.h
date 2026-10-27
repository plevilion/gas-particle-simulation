#pragma once

class SupportADessin;

// Anything that can be drawn (particles, the box, the system).
// dessine_sur(support) calls support.dessine(*this), so the right drawing code
// is chosen from both the object's type and the support's type (double dispatch).
class Dessinable {
public:
    virtual ~Dessinable() = default;
    Dessinable(Dessinable const&) = default;
    Dessinable& operator=(Dessinable const&) = default;
    Dessinable(Dessinable&&) = default;
    Dessinable& operator=(Dessinable&&) = default;

    Dessinable() = default;

    virtual void dessine_sur(SupportADessin&) = 0;
};
