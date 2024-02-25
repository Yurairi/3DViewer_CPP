#include "affine.h"

void s21::Affine::ChangeScale(double value) {
  if (value != 0) {
    for (double& vertice : vertices_) {
      vertice *= value;
    }
  }
}

void s21::Affine::ChangeRotateOnX(double value) {
  value = value * M_PI / 180;
  for (long unsigned int i = 0; i < vertices_.size(); i += 3) {
    double y = vertices_[i + 1];
    double z = vertices_[i + 2];
    vertices_[i + 1] = y * std::cos(value) - z * std::sin(value);
    vertices_[i + 2] = y * std::sin(value) + z * std::cos(value);
  }
}

void s21::Affine::ChangeRotateOnY(double value) {
  value = value * M_PI / 180;
  for (long unsigned int i = 0; i < vertices_.size(); i += 3) {
    double x = vertices_[i];
    double z = vertices_[i + 2];
    vertices_[i] = x * std::cos(value) + z * std::sin(value);
    vertices_[i + 2] = -x * std::sin(value) + z * std::cos(value);
  }
}

void s21::Affine::ChangeRotateOnZ(double value) {
  value = value * M_PI / 180;
  for (long unsigned int i = 0; i < vertices_.size(); i += 3) {
    double x = vertices_[i];
    double y = vertices_[i + 1];
    vertices_[i] = x * std::cos(value) - y * std::sin(value);
    vertices_[i + 1] = x * std::sin(value) + y * std::cos(value);
  }
}

void s21::Affine::MoveOnX(double value) {
  for (long unsigned int i = 0; i < vertices_.size(); i += 3) {
    vertices_[i] += value;
  }
}
void s21::Affine::MoveOnY(double value) {
  for (long unsigned int i = 1; i < vertices_.size(); i += 3) {
    vertices_[i] += value;
  }
}
void s21::Affine::MoveOnZ(double value) {
  for (long unsigned int i = 2; i < vertices_.size(); i += 3) {
    vertices_[i] += value;
  }
}

void s21::Affine::set_vertices(const std::vector<double>& vertices) {
  vertices_ = vertices;
}
const std::vector<double>& s21::Affine::get_vertices() { return vertices_; }
