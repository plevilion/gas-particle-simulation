#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Particule.h"
#include "Systeme.h"
#include "Enceinte.h"

// ======================================================================
void VueOpenGL::dessine(Neon const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

    QMatrix4x4 matrice;
    dessineAxes(matrice);

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 1.0, 0.0, 0.0); // rouge
}
void VueOpenGL::dessine(Argon const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 1.0, 0.0); // vert
}
void VueOpenGL::dessine(Helium const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

    QMatrix4x4 matrice;

    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 0.0, 1.0); // bleu
}

void VueOpenGL::dessine(Traine const& a_dessiner) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

    QMatrix4x4 matrice;
    QMatrix4x4 matricetraine;

    // Déssine la particule
    matrice.setToIdentity();
    matrice.translate(a_dessiner.get_position().get_coord(0),
                      a_dessiner.get_position().get_coord(1),
                      a_dessiner.get_position().get_coord(2));
    matrice.scale(0.5);
    dessineSphere(matrice, 0.0, 0.5, 0.5);

    // Déssine sa trainée
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
    /* Initialise notre vue OpenGL.
     * Dans cet exemple, nous créons et activons notre shader.
     *
     * En raison du contenu des fichiers *.glsl, le shader de cet exemple
     * NE permet QUE de dessiner des primitives colorées
     * (pas de textures, brouillard, reflets de la lumière ou autres).
     *
     * Il est séparé en deux parties VERTEX et FRAGMENT.
     * Le VERTEX :
     * - récupère pour chaque sommet des primitives de couleur (dans
     *     l'attribut couleur) et de position (dans l'attribut sommet)
     * - multiplie l'attribut sommet par les matrices 'vue_modele' et
     *     'projection' et donne le résultat à OpenGL
     *   - passe la couleur au shader FRAGMENT.
     *
     * Le FRAGMENT :
     *   - applique la couleur qu'on lui donne
     */

    prog.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

    /* Identifie les deux attributs du shader de cet exemple
     * (voir vertex_shader.glsl).
     *
     * L'attribut identifié par 0 est particulier, il permet d'envoyer un
     * nouveau "point" à OpenGL
     *
     * C'est pourquoi il devra obligatoirement être spécifié et en dernier
     * (après la couleur dans cet exemple, voir plus bas).
     */

    prog.bindAttributeLocation("sommet", SommetId);
    prog.bindAttributeLocation("couleur", CouleurId);

    // Activation du shader
    prog.bind();

    /* Activation du "Test de profondeur" et du "Back-face culling"
     * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
     * partielement caché par d'autres objets.
     *
     * Le Back-face culling consiste à ne dessiner que les face avec ordre
     * de déclaration dans le sens trigonométrique.
     */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    sphere.initialize(); // initialise la sphère
    initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition() {
    // position initiale
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -4.0);
    matrice_vue.rotate(60.0, 0.0, 1.0, 0.0);
    matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z) {
    /* Multiplie la matrice de vue par LA GAUCHE.
     * Cela fait en sorte que la dernière modification apportée
     * à la matrice soit appliquée en dernier (composition de fonctions).
     */
    QMatrix4x4 translation_supplementaire;
    translation_supplementaire.translate(x, y, z);
    matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) {
    // Multiplie la matrice de vue par LA GAUCHE
    QMatrix4x4 rotation_supplementaire;
    rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
    matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube(QMatrix4x4 const& point_de_vue, double col1, double col2, double col3) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);

    prog.setAttributeValue(CouleurId, col1, col2, col3);

    // face coté X = +1
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

    prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);

    prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

    prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

    // face coté X = -1
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

    prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

    prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);

    // connecter les faces
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
    prog.setAttributeValue(CouleurId, rouge, vert, bleu); // met la couleur
    sphere.draw(prog, SommetId);                          // dessine la sphère
}

void VueOpenGL::dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur) {
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);

    // axe X
    if (en_couleur) {
        prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
    } else {
        prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
    }
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

    // axe Y
    if (en_couleur)
        prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

    // axe Z
    if (en_couleur)
        prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
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
