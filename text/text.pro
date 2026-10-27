# Terminal version of the simulation. It does not use Qt.

TEMPLATE = app
TARGET = gas_text
CONFIG += console c++17
CONFIG -= qt app_bundle

INCLUDEPATH += ../core

SOURCES += \
    main.cc \
    TextViewer.cc \
    ../core/Vecteur3D.cc \
    ../core/Particule.cc \
    ../core/Enceinte.cc \
    ../core/Systeme.cc

HEADERS += \
    TextViewer.h \
    ../core/Vecteur3D.h \
    ../core/Particule.h \
    ../core/Enceinte.h \
    ../core/Systeme.h \
    ../core/Dessinable.h \
    ../core/SupportADessin.h \
    ../core/GenerateurAleatoire.h
