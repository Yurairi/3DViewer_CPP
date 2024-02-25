#include "mainwindow.h"

#include "ui_mainwindow.h"

s21::MainWindow::MainWindow(QWidget* parent, Controller* c1)
    : QMainWindow(parent), ui_(new Ui::MainWindow), c_(c1) {
  ui_->setupUi(this);

  LoadAndScaleImages();
  glWidget_ = new GLWidget(this);

  ui_->layoutForOpenGL->addWidget(glWidget_);

  gif_ = new s21::Gif(this);
  gif_->setGLWidget(glWidget_);
  gif_->setUI(ui_);
  settings_ = new QSettings("21school", "3D_Viewer");
  load_settings();
  glWidget_->controller_ = c_;
}

s21::MainWindow::~MainWindow() {
  save_settings();
  delete glWidget_;
  delete gif_;
  delete settings_;
  delete ui_;
}

void s21::MainWindow::SetImageForLabel(QLabel* label,
                                       const QString& imagePath) {
  QPixmap pixmap(imagePath);
  int w = label->width();
  int h = label->height();
  label->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
}

void s21::MainWindow::LoadAndScaleImages() {
  SetImageForLabel(ui_->label_2, ":/img/13.jpg");
  SetImageForLabel(ui_->label_3, ":/img/9.png");
  SetImageForLabel(ui_->label_4, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_6, ":/img/1.png");
  SetImageForLabel(ui_->label_7, ":/img/7.png");
  SetImageForLabel(ui_->label_12, ":/img/8.png");
  SetImageForLabel(ui_->label_16, ":/img/16.webp");
  SetImageForLabel(ui_->label_5, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_11, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_17, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_18, ":/img/21.png");
  SetImageForLabel(ui_->label_24, ":/img/22.png");
  SetImageForLabel(ui_->label_25, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_31, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_32, ":/img/23.png");
  SetImageForLabel(ui_->label_36, ":/img/17.jpeg");
  SetImageForLabel(ui_->label_37, ":/img/24.png");
}

void s21::MainWindow::on_load_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home", tr("Object (*.obj)"));
  ui_->label->setText(fileName);
}

void s21::MainWindow::on_start_pressed() {
  std::string str = ui_->label->text().toStdString();
  glWidget_->clearModel();
  bool status = c_->use(str);
  ui_->start->setDisabled(1);
  ui_->start->setDisabled(0);
  if (!status) {
    ui_->VerticesLabel->setText(QString::number(c_->GetVerticesNum()));
    ui_->EdgesLabel->setText(QString::number(c_->GetFacetsNum()));
    std::string std_filename = ui_->label->text().toStdString();
    ui_->file_name->setText(
        QString::fromStdString(c_->FindFileName(std_filename)));
    glWidget_->file_exist = true;
    glWidget_->update();
  } else {
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Incorrect file");
    ui_->label->setText("");
  }
}

void s21::MainWindow::on_X_valueChanged(double arg1) {
  c_->MoveOnX(arg1 - glWidget_->x_coord);
  glWidget_->x_coord = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_Y_valueChanged(double arg1) {
  c_->MoveOnY(arg1 - glWidget_->y_coord);
  glWidget_->y_coord = arg1;

  glWidget_->update();
}

void s21::MainWindow::on_Z_valueChanged(double arg1) {
  c_->MoveOnZ(arg1 - glWidget_->z_coord);
  glWidget_->z_coord = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_X_2_valueChanged(double arg1) {
  c_->ChangeRotateOnX(arg1 - glWidget_->x_coord_rotate);
  glWidget_->x_coord_rotate = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_Y_2_valueChanged(double arg1) {
  c_->ChangeRotateOnY(arg1 - glWidget_->y_coord_rotate);
  glWidget_->y_coord_rotate = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_Z_2_valueChanged(double arg1) {
  c_->ChangeRotateOnZ(arg1 - glWidget_->z_coord_rotate);
  glWidget_->z_coord_rotate = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_X_3_valueChanged(double arg1) {
  c_->ChangeScale(arg1 / glWidget_->scale_x);
  glWidget_->scale_x = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_projection_type_toggled(bool checked) {
  glWidget_->projection_type = 1;
  glWidget_->update();
}

void s21::MainWindow::on_radioButton_toggled(bool checked) {
  glWidget_->projection_type = 0;
  glWidget_->update();
}

void s21::MainWindow::on_red_valueChanged(double arg1) {
  glWidget_->c_red = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_gren_valueChanged(double arg1) {
  glWidget_->c_green = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_blue_valueChanged(double arg1) {
  glWidget_->c_blue = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_radioButton_2_toggled(bool checked) {
  glWidget_->mode = 0;
}

void s21::MainWindow::on_radioButton_3_toggled(bool checked) {
  glWidget_->mode = 1;
}

void s21::MainWindow::on_radioButton_7_toggled(bool checked) {
  glWidget_->verticle_mode = 2;
}

void s21::MainWindow::on_lineWidth_valueChanged(double arg1) {
  glWidget_->line_width = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_verticle_Size_valueChanged(double arg1) {
  glWidget_->verticle_width = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_red_verticle_valueChanged(double arg1) {
  glWidget_->v_red = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_green_verticle_valueChanged(double arg1) {
  glWidget_->v_green = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_blue_verticle_valueChanged(double arg1) {
  glWidget_->v_blue = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_red_line_valueChanged(double arg1) {
  glWidget_->l_red = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_green_line_valueChanged(double arg1) {
  glWidget_->l_green = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_blue_line_valueChanged(double arg1) {
  glWidget_->l_blue = arg1;
  glWidget_->update();
}

void s21::MainWindow::on_radioButton_5_toggled(bool checked) {
  glWidget_->verticle_mode = 1;
}

void s21::MainWindow::on_radioButton_6_toggled(bool checked) {
  glWidget_->verticle_mode = 0;
}

void s21::MainWindow::on_screenshot_clicked() {
  gif_->button_screen_pressed(this);
}

void s21::MainWindow::on_gif_clicked() { gif_->button_pressed(this); }

void s21::MainWindow::load_settings() {
  QVariant settingsValue = settings_->value("settings");
  if (settingsValue.isValid() && settingsValue.toInt()) {
    int projection_type = settings_->value("perspective", true).toInt();
    if (projection_type) {
      ui_->projection_type->setChecked(true);
    } else {
      ui_->radioButton->setChecked(true);
    }
    int dot = settings_->value("dotted_on", false).toInt();
    if (dot) {
      ui_->radioButton_2->setChecked(true);
    } else {
      ui_->radioButton_3->setChecked(true);
    }
    int ver = settings_->value("verticle_on", false).toInt();
    if (ver) {
      ui_->radioButton_5->setChecked(true);
    } else {
      ui_->radioButton_6->setChecked(true);
    }
    ui_->red_verticle->setValue(
        settings_->value("verticle_red", 0.0).toDouble());
    ui_->green_verticle->setValue(
        settings_->value("verticle_green", 0.0).toDouble());
    ui_->blue_verticle->setValue(
        settings_->value("verticle_blue", 0.0).toDouble());
    ui_->red_line->setValue(settings_->value("line_red", 0.0).toDouble());
    ui_->green_line->setValue(settings_->value("line_green", 0.0).toDouble());
    ui_->blue_line->setValue(settings_->value("line_blue", 0.0).toDouble());
    ui_->red->setValue(settings_->value("red", 0.0).toDouble());
    ui_->gren->setValue(settings_->value("green", 0.0).toDouble());
    ui_->blue->setValue(settings_->value("blue", 0.0).toDouble());
    ui_->verticle_Size->setValue(
        settings_->value("verticle_Size", 0.0).toDouble());
    ui_->lineWidth->setValue(settings_->value("lineWidth", 0.0).toDouble());
  }
}

void s21::MainWindow::save_settings() {
  settings_->setValue("settings", 1);
  settings_->setValue("perspective", ui_->projection_type->isChecked());
  settings_->setValue("ortho", ui_->radioButton->isChecked());
  settings_->setValue("dotted_on", ui_->radioButton_2->isChecked());
  settings_->setValue("dotted_off", ui_->radioButton_3->isChecked());
  settings_->setValue("verticle_on", ui_->radioButton_5->isChecked());
  settings_->setValue("verticle_off", ui_->radioButton_6->isChecked());
  settings_->setValue("verticle_red", ui_->red_verticle->value());
  settings_->setValue("verticle_green", ui_->green_verticle->value());
  settings_->setValue("verticle_blue", ui_->blue_verticle->value());
  settings_->setValue("line_red", ui_->red_line->value());
  settings_->setValue("line_green", ui_->green_line->value());
  settings_->setValue("line_blue", ui_->blue_line->value());
  settings_->setValue("backround_red", ui_->red->value());
  settings_->setValue("backround_green", ui_->gren->value());
  settings_->setValue("backround_blue", ui_->blue->value());
  settings_->setValue("verticle_Size", ui_->verticle_Size->value());
  settings_->setValue("lineWidth", ui_->lineWidth->value());
}

void s21::MainWindow::on_reset_clicked() {
  ui_->projection_type->setChecked(false);
  ui_->radioButton->setChecked(false);
  ui_->radioButton_2->setChecked(false);
  ui_->radioButton_3->setChecked(false);
  ui_->radioButton_5->setChecked(false);
  ui_->radioButton_6->setChecked(false);
  ui_->red_verticle->setValue(0.0);
  ui_->green_verticle->setValue(0.0);
  ui_->blue_verticle->setValue(0.0);
  ui_->red_line->setValue(0.0);
  ui_->green_line->setValue(0.0);
  ui_->blue_line->setValue(0.0);
  ui_->red->setValue(0.0);
  ui_->gren->setValue(0.0);
  ui_->blue->setValue(0.0);
  ui_->verticle_Size->setValue(0.0);
  ui_->lineWidth->setValue(0.0);
}
