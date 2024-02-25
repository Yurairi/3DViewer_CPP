#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  s21::Model m;
  s21::Controller* c = s21::Controller::getInstance(&m);
  s21::MainWindow w(nullptr, c);
  w.show();
  return a.exec();
}
