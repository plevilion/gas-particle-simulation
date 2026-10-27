# 3D version of the simulation (Qt 5 or Qt 6, OpenGL).

TEMPLATE = app
TARGET = gas_gl
CONFIG += c++17
CONFIG -= app_bundle

QT += core gui opengl widgets
contains(QT_VERSION, ^6\\..*) {
    QT += openglwidgets
}

win32:LIBS += -lopengl32

INCLUDEPATH += ../core

SOURCES += \
    main.cc \
    glwidget.cc \
    vue_opengl.cc \
    glsphere.cc \
    ../core/Vecteur3D.cc \
    ../core/Particule.cc \
    ../core/Enceinte.cc \
    ../core/Systeme.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../core/Vecteur3D.h \
    ../core/Particule.h \
    ../core/Enceinte.h \
    ../core/Systeme.h \
    ../core/Dessinable.h \
    ../core/SupportADessin.h \
    ../core/GenerateurAleatoire.h

RESOURCES += \
    resource.qrc
