#include <iostream>
#include <array>
#include "SupportADessin.h"
#include "TextViewer.h"
#include "Particule.h"
#include "Enceinte.h"
#include "Systeme.h"

using namespace std;

void TextViewer::dessine(Argon const& a_dessiner) {
    flot << a_dessiner << endl;
}

void TextViewer::dessine(Neon const& a_dessiner) {
    flot << a_dessiner << endl;
}

void TextViewer::dessine(Helium const& a_dessiner) {
    flot << a_dessiner << endl;
}

void TextViewer::dessine(Enceinte const& a_dessiner) {
    flot << a_dessiner << endl;
}

void TextViewer::dessine(Systeme const& a_dessiner) {
    flot << a_dessiner << endl;
}

void TextViewer::dessine(Traine const& a_dessiner) {
    flot << a_dessiner << endl;
}
