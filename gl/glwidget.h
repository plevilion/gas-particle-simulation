#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include "vue_opengl.h"
#include "Particule.h"
#include "Systeme.h"

// The window. Keyboard and timer events are handled by overriding the virtual
// methods of QOpenGLWidget.
class GLWidget : public QOpenGLWidget {
public:
    // Three given particles (plus a tracer) in a 20 x 20 x 20 box
    GLWidget(Neon* neon, Argon* arg, Helium* hel, Traine* traine, QWidget* parent = nullptr);
    // n atoms of each gas plus a tracer, at random positions
    GLWidget(int n, int largeur = 100, int hauteur = 100, int profondeur = 100,
             QWidget* parent = nullptr);
    virtual ~GLWidget() = default;

private:
    // The three key methods of QOpenGLWidget
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;

    // Events
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void timerEvent(QTimerEvent* event) override;

    void pause();

    // What the system draws itself on
    VueOpenGL vue;

    int timerId;
    // Measures the real time between two steps (dt)
    QElapsedTimer chronometre;

    // The simulated gas
    Systeme c;
};
