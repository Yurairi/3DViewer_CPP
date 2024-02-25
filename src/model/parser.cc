#include "parser.h"

int s21::Parser::get_status() const { return status_; }
s21::OBJFile s21::Parser::get_obj() const { return obj_file_; }

bool s21::Parser::OpenFile(std::string file_path) {
  input_file_.open(file_path);
  return input_file_.is_open();
}

bool s21::Parser::Processing(std::string file_path) {
  clearData();
  if (OpenFile(file_path)) {
    ReadingFacetsAndVertexes(file_path);
  } else {
    status_ = 1;
  }
  return get_status();
}

void s21::Parser::ReadingFacetsAndVertexes(std::string file_path) {
  std::ifstream input(file_path);
  std::string line;
  int num_vertexes = 0;

  while (std::getline(input, line)) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;
    if (token == "v") {
      double x, y, z;
      if (iss >> x >> y >> z) {
        obj_file_.vertexes.push_back(x);
        obj_file_.vertexes.push_back(y);
        obj_file_.vertexes.push_back(z);
        num_vertexes++;
      }
    } else if (token == "f") {
      std::string index;
      std::vector<int> fac_line;
      while (iss >> index) {
        int idx = std::stoi(index);
        if (idx < 0) {
          idx = num_vertexes + idx + 1;
        }
        fac_line.push_back(idx);
      }
      for (size_t i = 0; i < fac_line.size(); ++i) {
        obj_file_.facets.push_back(fac_line[i] - 1);
        obj_file_.facets.push_back(fac_line[(i + 1) % fac_line.size()] - 1);
      }
      obj_file_.num_facets++;
    }
  }
  obj_file_.num_vertexes = num_vertexes;
}

void s21::Parser::clearData() {
  obj_file_.facets.clear();
  obj_file_.vertexes.clear();
  obj_file_.num_facets = 0;
  obj_file_.num_vertexes = 0;
  status_ = 0;
}

std::string s21::Parser::FindFileName(std::string file_path) {
  std::string start;
  size_t lastSlashPos = file_path.find_last_of('/');
  size_t extPos = file_path.find_last_of('.');
  if (lastSlashPos != std::string::npos && extPos != std::string::npos) {
    start = file_path.substr(lastSlashPos + 1, extPos - lastSlashPos - 1);
  }
  return start;
}

void s21::Parser::set_obj(const std::vector<double> &new_vertexes) {
  obj_file_.vertexes = new_vertexes;
}
