#ifndef VIV_PARSER_H
#define VIV_PARSER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "strategy.h"
namespace s21 {

struct OBJFile {
  int num_vertexes;
  int num_facets;
  std::vector<double> vertexes;
  std::vector<int> facets;
};

class Parser {
 private:
  int status_ = 0;
  OBJFile obj_file_;
  std::ifstream input_file_;

 public:
  Parser() : obj_file_({0, 0, {}, {}}) {}
  bool Processing(std::string file_path);
  bool OpenFile(std::string file_path);
  void ReadingFacetsAndVertexes(std::string file_path);
  void clearData();
  std::string FindFileName(std::string file_path);
  OBJFile get_obj() const;
  int get_status() const;
  void set_obj(const std::vector<double> &new_vertexes);
};

}  // namespace s21
#endif  // VIV_PARSER_H
