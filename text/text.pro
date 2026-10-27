QMAKE_CXXFLAGS += -std=c++17

CONFIG += console

TARGET = ex_05_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    Textviewer.cc \
    ../general/Vecteur3D.cc \
    ../general/particule.cc \
    ../general/systeme.cc \
    ../general/Enceinte.cc 
    
HEADERS += \
    ../general/Systeme.h \
    Textviewer.h \
    ../general/Dessinable.h \
    ../general/SupportADessin.h \
	../general/Vecteur3D.h \
    ../general/particule.h \
    ../general/Enceinte.h  \
    ../general/GenerateurAleatoire.h
