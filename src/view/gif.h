#ifndef GIF_H
#define GIF_H

#include <qgifimage.h>

#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <QTimer>

#include "glwidget.h"
#include "ui_mainwindow.h"

namespace s21 {
class Gif : public QObject {
  Q_OBJECT
 public:
  explicit Gif(QObject *parent = nullptr);
  void setGLWidget(GLWidget *glWidget);
  void setUI(Ui::MainWindow *ui);
  ~Gif();

 signals:

 public slots:
  void button_pressed(QWidget *parent);
  void make_gif();
  void button_screen_pressed(QWidget *parent);

 private:
  QTimer *timer_;
  QString gif_name_;
  QGifImage *gif_frame_;
  int frames_counter_ = 0;
  GLWidget *glWidget_;
  Ui::MainWindow *ui_;
};
}  // namespace s21

#endif  // GIF_H
