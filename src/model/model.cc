#include "model.h"

bool s21::Model::Processing(const std::string& file_name) {
  bool status = parser_.Processing(file_name);
  if (!status) ObjData_ = parser_.get_obj();
  return status;
}

std::vector<double>::value_type* s21::Model::GetVerticesData() {
  return ObjData_.vertexes.data();
}

std::vector<int>::value_type* s21::Model::GetFacetsData() {
  return ObjData_.facets.data();
}

size_t s21::Model::GetVerticesSize() { return ObjData_.vertexes.size(); }

size_t s21::Model::GetFacetsSize() { return ObjData_.facets.size(); }

size_t s21::Model::GetVerticesNum() { return ObjData_.num_vertexes; }

size_t s21::Model::GetFacetsNum() { return ObjData_.num_facets; }

void s21::Model::ClearData() {
  ObjData_.vertexes.clear();
  ObjData_.facets.clear();
  ObjData_.num_facets = 0;
  ObjData_.num_vertexes = 0;
}

s21::OBJFile s21::Model::get_obj() { return parser_.get_obj(); }

s21::OBJFile s21::Model::get_obj_model() const { return ObjData_; }

std::string s21::Model::FindFileName(std::string file_path) {
  return parser_.FindFileName(file_path);
}

void s21::Model::ChangeScale(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.ChangeScale(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::ChangeRotateOnX(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.ChangeRotateOnX(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::ChangeRotateOnY(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.ChangeRotateOnY(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::ChangeRotateOnZ(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.ChangeRotateOnZ(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::MoveOnX(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.MoveOnX(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::MoveOnY(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.MoveOnY(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::MoveOnZ(double value) {
  affine_.set_vertices(ObjData_.vertexes);
  affine_.MoveOnZ(value);
  ObjData_.vertexes = affine_.get_vertices();
}

void s21::Model::set_obj_parser(const std::vector<double>& new_vertexes) {
  parser_.set_obj(new_vertexes);
}
