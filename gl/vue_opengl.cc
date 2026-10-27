#include "vue_opengl.h"
#include "vertex_shader.h" // ids of the shader attributes
#include "Particule.h"
#include "Systeme.h"
#include "Enceinte.h"

// ======================================================================
void VueOpenGL::dessine(Neon const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // filled polygons

    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 1.0, 0.0, 0.0); // red
}
void VueOpenGL::dessine(Argon const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // filled polygons

    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 1.0, 0.0); // green
}
void VueOpenGL::dessine(Helium const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // filled polygons

    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 0.0, 1.0); // blue
}

void VueOpenGL::dessine(Traine const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // filled polygons

    QMatrix4x4 matrice;
    QMatrix4x4 matricetraine;

    // The particle
    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 0.5, 0.5);

    // Its trail
    matricetraine.setToIdentity();
    dessineTraine(matricetraine, a_dessiner);
}

void VueOpenGL::dessine(Systeme const& a_dessiner) {}

void VueOpenGL::dessine(Enceinte const& a_dessiner) {
    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get(0) / 2, a_dessiner.get(1) / 2, a_dessiner.get(2) / 2);
    matrice.scale((a_dessiner.get(0) / 2) + 1);
    dessineCube(matrice, 1.0, 0.0, 0.0);
}

// ======================================================================
void VueOpenGL::init() {
    /* Creates and activates the shader. It only draws coloured primitives
     * (no textures or lighting):
     * - the vertex shader multiplies each vertex ('sommet') by the
     *   'vue_modele' and 'projection' matrices and passes on its colour;
     * - the fragment shader applies that colour.
     */

    prog.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

    /* The two attributes of the shader (see vertex_shader.glsl).
     * Attribute 0 sends a new vertex to OpenGL, so it must be set last
     * (after the colour).
     */

    prog.bindAttributeLocation("sommet", SommetId);
    prog.bindAttributeLocation("couleur", CouleurId);

    // Activate the shader
    prog.bind();

    /* Depth test: objects in the background are partly hidden by those in
     * front. Back-face culling: only faces declared counter-clockwise are drawn.
     */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    sphere.initialize();
    initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition() {
    // Initial camera position
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -4.0);
    matrice_vue.rotate(60.0, 0.0, 1.0, 0.0);
    matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z) {
    /* Multiplies the view matrix on the LEFT, so that the latest change is
     * applied last (composition of functions).
     */
    QMatrix4x4 translation_supplementaire;
    translation_supplementaire.translate(x, y, z);
    matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) {
    // Multiplies the view matrix on the left
    QMatrix4x4 rotation_supplementaire;
    rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
    matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube(QMatrix4x4 const& point_de_vue, double col1, double col2, double col3) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);

    prog.setAttributeValue(CouleurId, col1, col2, col3);

    // face X = +1
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

    // face X = -1
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

    // edges joining the two faces
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

    glEnd();
}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue, double rouge, double vert,
                              double bleu) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu); // colour
    sphere.draw(prog, SommetId);                          // draw the sphere
}

void VueOpenGL::dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);

    // X axis
    if (en_couleur) {
        prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // red
    } else {
        prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // white
    }
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

    // Y axis
    if (en_couleur)
        prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // green
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

    // Z axis
    if (en_couleur)
        prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // blue
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

    glEnd();
}

void VueOpenGL::dessineTraine(QMatrix4x4 const& point_de_vue, Traine const& traine) {

    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINE_STRIP);

    for (auto const& point : traine.points_memorise) {
        glVertex3f(point.get_coord(0), point.get_coord(1), point.get_coord(2));
    }
    glEnd();
}
