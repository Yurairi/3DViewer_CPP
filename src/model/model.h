#ifndef VIEWER_MODEL_H
#define VIEWER_MODEL_H

#include <list>

#include "affine.h"
#include "parser.h"

namespace s21 {
class Model : public Strategy {
 public:
  static Model *getInstance();
  bool Processing(const std::string &file_name);
  s21::OBJFile get_obj();
  s21::OBJFile get_obj_model() const;
  void set_obj_parser(const std::vector<double> &new_vertexes);
  std::string FindFileName(std::string file_path);
  void ChangeScale(double value);
  void ChangeRotateOnX(double value);
  void ChangeRotateOnY(double value);
  void ChangeRotateOnZ(double value);
  void MoveOnX(double value);
  void MoveOnY(double value);
  void MoveOnZ(double value);

  std::vector<double>::value_type *GetVerticesData();
  std::vector<int>::value_type *GetFacetsData();
  size_t GetVerticesSize();
  size_t GetFacetsSize();
  size_t GetVerticesNum();
  size_t GetFacetsNum();
  void ClearData();
  bool use(const std::string &file_path) override {
    return Processing(file_path);
  }

 private:
  Parser parser_;
  Affine affine_;
  OBJFile ObjData_;
};

}  // namespace s21
#endif  // VIEWER_MODEL_H
