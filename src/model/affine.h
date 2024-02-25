#ifndef VIEWER_AFFINE_H
#define VIEWER_AFFINE_H

#include <cmath>
#include <vector>
namespace s21 {
class Affine {
 private:
  std::vector<double> vertices_;

 public:
  void ChangeScale(double value);
  void ChangeRotateOnX(double value);
  void ChangeRotateOnY(double value);
  void ChangeRotateOnZ(double value);
  void MoveOnX(double value);
  void MoveOnY(double value);
  void MoveOnZ(double value);
  void set_vertices(const std::vector<double>& vertices);
  const std::vector<double>& get_vertices();
};
}  // namespace s21
#endif  // VIEWER_AFFINE_H
