#pragma once
#include <iostream>
#include "SupportADessin.h"
#include "Particule.h"
#include "Enceinte.h"
#include "Systeme.h"

class TextViewer : public SupportADessin {
public:
    TextViewer(std::ostream& flot) : flot(flot) {}
    virtual ~TextViewer() = default;
    TextViewer(TextViewer const&) = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&) = default;
    TextViewer& operator=(TextViewer&&) = default;

    virtual void dessine(Neon const& a_dessiner) override;
    virtual void dessine(Helium const& a_dessiner) override;
    virtual void dessine(Argon const& a_dessiner) override;
    virtual void dessine(Enceinte const& a_dessiner) override;
    virtual void dessine(Systeme const& a_dessiner) override;
    virtual void dessine(Traine const& a_dessiner) override;

private:
    std::ostream& flot;
};
