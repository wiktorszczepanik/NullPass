#include "nullpass.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NullPass window;
    window.show();
    return app.exec();
}
