#include <QApplication>
#include "glwidget.h"
#include "Particule.h"
#include "Systeme.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    // 333 neon, 333 argon and 333 helium atoms plus 1 tracer, in a 100 x 100 x 100 box
    // (the box size can be passed as 3 more arguments)
    GLWidget w(333);
    w.show();
    return a.exec();
}
