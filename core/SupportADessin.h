#pragma once

class Neon;
class Argon;
class Helium;
class Traine;
class Enceinte;
class Systeme;

// Something particles can be drawn on: the terminal (TextViewer) or the 3D
// OpenGL view (VueOpenGL). One dessine() overload per drawable type.
class SupportADessin {
public:
    virtual ~SupportADessin() = default;
    SupportADessin(SupportADessin const&) = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
    SupportADessin(SupportADessin&&) = default;
    SupportADessin& operator=(SupportADessin&&) = default;

    SupportADessin() = default;

    virtual void dessine(Neon const&) = 0;
    virtual void dessine(Helium const&) = 0;
    virtual void dessine(Argon const&) = 0;
    virtual void dessine(Enceinte const&) = 0;
    virtual void dessine(Systeme const&) = 0;
    virtual void dessine(Traine const&) = 0;
};
