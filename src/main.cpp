#include <QApplication>
#include "MainWindow.h"

int randomInt(int max, int min) {
	int rando = (min + (qrand() % (int)(max - min + 1)));
	//classic rando
	return rando;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(time(NULL));
    MainWindow *window = new MainWindow;
    window->setFixedSize(750,750);
    window->decorate();
    return app.exec();
}
