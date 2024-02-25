#include "gif.h"

s21::Gif::Gif(QObject *parent) : QObject{parent} {
  timer_ = new QTimer(0);
  connect(timer_, SIGNAL(timeout()), this, SLOT(make_gif()));
}

void s21::Gif::button_pressed(QWidget *parent) {
  QDateTime current_date = QDateTime::currentDateTime();
  QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
  QString name_pattern = "Screen Cast " + formattedTime + ".gif";
  gif_name_ = QFileDialog::getSaveFileName(parent, tr("Save a gif animation"),
                                           name_pattern, tr("gif (*.gif)"));
  if (gif_name_ != "") {
    ui_->gif->setDisabled(true);
    gif_frame_ = new QGifImage;
    gif_frame_->setDefaultDelay(10);
    timer_->setInterval(100);
    timer_->start();
  }
}

void s21::Gif::make_gif() {
  QImage image = glWidget_->grabFramebuffer();
  QSize image_size(640, 480);
  QImage scaled_image = image.scaled(image_size);
  gif_frame_->addFrame(scaled_image);
  if (frames_counter_ == 50) {
    timer_->stop();
    gif_frame_->save(gif_name_);
    frames_counter_ = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif animation saved successfully");
    delete gif_frame_;
    ui_->gif->setText("");
    ui_->gif->setEnabled(true);
  }
  frames_counter_++;
  if (!ui_->gif->isEnabled()) {
    ui_->gif->setText(QString::number(frames_counter_ / 10) + "s");
  }
}

void s21::Gif::button_screen_pressed(QWidget *parent) {
  QFileDialog dialogConnectImage(parent);
  QDateTime current_date = QDateTime::currentDateTime();
  QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
  QString name_pattern = "Screen Shot " + formattedTime + ".jpeg";
  QString image_name = dialogConnectImage.getSaveFileName(
      parent, tr("Save a screenshot"), name_pattern,
      tr("image (*.jpeg *.bmp)"));
  if (image_name.length() >= 1) {
    QImage img = glWidget_->grabFramebuffer();
    img.save(image_name);
    QMessageBox messageBoxImage;
    messageBoxImage.information(0, "", "Screenshot saved successfully");
  }
}

void s21::Gif::setGLWidget(GLWidget *glWidget) { glWidget_ = glWidget; }

void s21::Gif::setUI(Ui::MainWindow *ui) { ui_ = ui; }

s21::Gif::~Gif() { delete timer_; }
