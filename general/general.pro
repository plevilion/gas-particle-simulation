TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
	particule.cc \
	systeme.cc 
	
HEADERS += \
    particule.h \
    Dessinable.h \
    SupportADessin.h \
    Systeme.h \
