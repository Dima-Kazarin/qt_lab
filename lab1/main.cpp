#include "widget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QLabel label("Text Label");
    QPushButton button1("Button");
    button1.setStyleSheet("width: 120px; height: 40px");
    QLineEdit textedit;
    QHBoxLayout layout(&w);
    layout.addWidget(&label);
    layout.addWidget(&button1);
    layout.addWidget(&textedit);
    layout.setAlignment(Qt::AlignTop);

    w.setWindowTitle("Title");
    w.resize(320, 240);
    w.show();
    QPushButton *button = new QPushButton("Press me", &w);
    button->move(100, 100);
    button->setStyleSheet("background-color: blue;");
    button->show();
    return a.exec();
}
