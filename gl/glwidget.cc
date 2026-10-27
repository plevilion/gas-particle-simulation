#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"
#include "Particule.h"
#include "Systeme.h"

// Three given particles (plus a tracer) in a 20 x 20 x 20 box (exercise P11)
GLWidget::GLWidget(Neon* neon, Argon* arg, Helium* hel, Traine* traine, QWidget* parent)
    : QOpenGLWidget(parent), c(20, 20, 20) {
    chronometre.restart();
    c.ajouter_autrement(neon);
    c.ajouter_autrement(arg);
    c.ajouter_autrement(hel);
    c.ajouter_autrement(traine);
    c.initialiser();
}

// n atoms of each gas plus a tracer, at random positions and velocities
GLWidget::GLWidget(int n, int largeur, int hauteur, int profondeur, QWidget* parent)
    : QOpenGLWidget(parent), c(largeur, hauteur, profondeur) {
    chronometre.restart();
    do {
        c.ajouter_autrement(new Neon());
        c.ajouter_autrement(new Argon());
        c.ajouter_autrement(new Helium());
        --n;
    } while (n > 0);
    c.ajouter_autrement(new Traine());
    c.initialiser();
}

// ======================================================================
void GLWidget::initializeGL() {
    vue.init();
    timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height) {
    // Draw on the whole window
    glViewport(0, 0, width, height);

    // Perspective projection, sent to the shader by VueOpenGL
    // (see http://www.songho.ca/opengl/gl_projectionmatrix.html)
    QMatrix4x4 matrice;
    matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
    vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    c.dessine_sur(vue);
}

// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event) {
    constexpr double petit_angle(5.0); // degrees
    constexpr double petit_pas(1.0);

    switch (event->key()) {

    case Qt::Key_Left:
        vue.rotate(petit_angle, 0.0, -1.0, 0.0);
        break;

    case Qt::Key_Right:
        vue.rotate(petit_angle, 0.0, +1.0, 0.0);
        break;

    case Qt::Key_Up:
        vue.rotate(petit_angle, -1.0, 0.0, 0.0);
        break;

    case Qt::Key_Down:
        vue.rotate(petit_angle, +1.0, 0.0, 0.0);
        break;

    case Qt::Key_PageUp:
    case Qt::Key_W:
        vue.translate(0.0, 0.0, petit_pas);
        break;

    case Qt::Key_PageDown:
    case Qt::Key_S:
        vue.translate(0.0, 0.0, -petit_pas);
        break;

    case Qt::Key_A:
        vue.translate(petit_pas, 0.0, 0.0);
        break;

    case Qt::Key_D:
        vue.translate(-petit_pas, 0.0, 0.0);
        break;

    case Qt::Key_R:
        vue.translate(0.0, -petit_pas, 0.0);
        break;

    case Qt::Key_F:
        vue.translate(0.0, petit_pas, 0.0);
        break;

    case Qt::Key_Q:
        vue.rotate(petit_angle, 0.0, 0.0, -1.0);
        break;

    case Qt::Key_E:
        vue.rotate(petit_angle, 0.0, 0.0, +1.0);
        break;

    case Qt::Key_Home:
        vue.initializePosition();
        break;

    case Qt::Key_Space:
        pause();
        break;
    };

    update(); // redraw
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);

    // Real time since the last step, in seconds. Capped so that a long pause
    // (window dragged, computer asleep) does not make particles jump too far.
    double dt = chronometre.elapsed() / 1000.0;
    if (dt > 0.1) {
        dt = 0.1;
    }
    chronometre.restart();

    // evolue2 uses the grid of cells for collisions; evolue1 tests all pairs
    c.evolue2(dt);
    update();
}

// ======================================================================
void GLWidget::pause() {
    if (timerId == 0) {
        // timer stopped: restart it
        timerId = startTimer(20);
        chronometre.restart();
    } else {
        // timer running: stop it
        killTimer(timerId);
        timerId = 0;
    }
}
