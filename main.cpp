#include "ui.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo repo("melodii.txt");
    Service service(repo);
    AppGUI w(service);
    w.show();
    return app.exec();
}
