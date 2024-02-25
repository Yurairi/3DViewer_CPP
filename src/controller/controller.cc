#include "controller.h"

s21::Controller* s21::Controller::instance_ = nullptr;

s21::Controller::Controller(Model* mod) : m_(mod) {}

s21::Controller* s21::Controller::getInstance(Model* mod) {
  if (!instance_) {
    instance_ = new Controller(mod);
  }
  return instance_;
}

bool s21::Controller::Processing(std::string file_path) {
  return m_->Processing(file_path);
}

s21::OBJFile s21::Controller::get_obj() { return m_->get_obj(); }

std::string s21::Controller::FindFileName(std::string file_path) {
  return m_->FindFileName(file_path);
}

std::vector<double>::value_type* s21::Controller::GetVerticesData() {
  return m_->GetVerticesData();
}

std::vector<int>::value_type* s21::Controller::GetFacetsData() {
  return m_->GetFacetsData();
}

size_t s21::Controller::GetVerticesSize() { return m_->GetVerticesSize(); }

size_t s21::Controller::GetFacetsSize() { return m_->GetFacetsSize(); }

size_t s21::Controller::GetVerticesNum() { return m_->GetVerticesNum(); }

size_t s21::Controller::GetFacetsNum() { return m_->GetFacetsNum(); }

void s21::Controller::ClearData() { m_->ClearData(); }

bool s21::Controller::use(std::string file_path) { return m_->use(file_path); }

void s21::Controller::ChangeScale(double value) { m_->ChangeScale(value); }

void s21::Controller::ChangeRotateOnX(double value) {
  m_->ChangeRotateOnX(value);
}

void s21::Controller::ChangeRotateOnY(double value) {
  m_->ChangeRotateOnY(value);
}

void s21::Controller::ChangeRotateOnZ(double value) {
  m_->ChangeRotateOnZ(value);
}

void s21::Controller::MoveOnX(double value) { m_->MoveOnX(value); }

void s21::Controller::MoveOnY(double value) { m_->MoveOnY(value); }

void s21::Controller::MoveOnZ(double value) { m_->MoveOnZ(value); }
