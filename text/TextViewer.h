#pragma once
#include <iostream>
#include "SupportADessin.h"
#include "Particule.h"
#include "Enceinte.h"
#include "Systeme.h"

// Draws the simulation as text on a stream (for example the terminal).
class TextViewer : public SupportADessin {
public:
    TextViewer(std::ostream& flot) : flot(flot) {}
    virtual ~TextViewer() = default;
    TextViewer(TextViewer const&) = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&) = default;
    TextViewer& operator=(TextViewer&&) = default;

    void dessine(Neon const& a_dessiner) override;
    void dessine(Helium const& a_dessiner) override;
    void dessine(Argon const& a_dessiner) override;
    void dessine(Enceinte const& a_dessiner) override;
    void dessine(Systeme const& a_dessiner) override;
    void dessine(Traine const& a_dessiner) override;

private:
    std::ostream& flot;
};
