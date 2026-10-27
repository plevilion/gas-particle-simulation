#pragma once

#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include "SupportADessin.h"
#include "glsphere.h"

// Draws the simulation in 3D with OpenGL (spheres for atoms, lines for the box
// and the tracer's trail).
class VueOpenGL : public SupportADessin {
public:
    // Drawing methods (from SupportADessin)
    void dessine(Neon const& a_dessiner) override;
    void dessine(Argon const& a_dessiner) override;
    void dessine(Helium const& a_dessiner) override;
    void dessine(Enceinte const& a_dessiner) override;
    void dessine(Systeme const& a_dessiner) override;
    void dessine(Traine const& a_dessiner) override;

    // (Re)initialisation
    void init();
    void initializePosition();

    void setProjection(QMatrix4x4 const& projection) {
        prog.setUniformValue("projection", projection);
    }

    // Camera movements
    void translate(double x, double y, double z);
    void rotate(double angle, double dir_x, double dir_y, double dir_z);

    // Drawing helpers
    void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4(), double col1 = 1,
                     double col2 = 0, double col3 = 0);
    void dessineSphere(QMatrix4x4 const& point_de_vue, double rouge = 1.0, double vert = 1.0,
                       double bleu = 1.0);
    void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
    void dessineTraine(QMatrix4x4 const& point_de_vue, Traine const& traine);

private:
    // OpenGL shader program
    QOpenGLShaderProgram prog;
    GLSphere sphere;

    // Camera
    QMatrix4x4 matrice_vue;
};
