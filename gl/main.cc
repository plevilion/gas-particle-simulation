#include <QApplication>
#include <vector>
#include "glwidget.h"
#include "Particule.h"
#include "Systeme.h"
#include "Vecteur3D.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    // on initialise le systeme avec 333 néons, 333 argons, 333 héliums et 1 trainée
    // ce constructeur admet également 3 paramètres pour la taille de l'enceinte qui sont à 100 par
    // défaut
    GLWidget w(333);
    w.show();
    return a.exec();
}
