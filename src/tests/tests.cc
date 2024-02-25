#include <gtest/gtest.h>

#include "../model/model.h"

TEST(ModelTest, ProcessingValidFile) {
  s21::Model model;
  bool result = model.Processing("tests/obj/skull.obj");
  EXPECT_FALSE(result);

  EXPECT_EQ(model.get_obj().num_facets, 9537);
  EXPECT_EQ(model.get_obj().num_vertexes, 6122);
}

TEST(ModelTest, ProcessingValidFile2) {
  s21::Model model;
  bool result = model.Processing("tests/obj/one_million.obj");
  EXPECT_TRUE(!result);

  EXPECT_EQ(model.get_obj().num_facets, 1669317);
  EXPECT_EQ(model.get_obj().num_vertexes, 1000000);
}

TEST(ModelTest, ProcessingInvalidFile2) {
  s21::Model model;
  bool result = model.Processing("tests/obj/City.obj");
  EXPECT_TRUE(result);
}

TEST(ModelTest, ProcessingEmptyFile) {
  s21::Model model;
  bool result = model.Processing("tests/obj/emp.obj");
  EXPECT_FALSE(result);
  EXPECT_EQ(model.get_obj().num_facets, 0);
  EXPECT_EQ(model.get_obj().num_vertexes, 0);
}

TEST(ModelTest, ProcessingEmptyFile2) {
  s21::Model model;
  bool result = model.Processing("tests/obj/Empty.obj");
  EXPECT_FALSE(result);
  EXPECT_EQ(model.get_obj().num_facets, 1);
  EXPECT_EQ(model.get_obj().num_vertexes, 1);
}

TEST(ModelTest, AffineScale) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.ChangeScale(3);
  EXPECT_FALSE(result);
  EXPECT_EQ(model.get_obj().num_facets, 10);
  EXPECT_EQ(model.get_obj().num_vertexes, 8);
  std::vector<double> scalecube = {0, 0, 0, 0, 0, 6, 0, 6, 0, 0, 6, 6,
                                   6, 0, 0, 6, 0, 6, 6, 6, 0, 6, 6, 6};
  EXPECT_EQ(model.get_obj_model().vertexes, scalecube);
}

TEST(ModelTest, AffineChangeRotateX) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.ChangeRotateOnX(30);
  EXPECT_FALSE(result);
  std::vector<double> rxcube = {
      0, 0, 0, 0, -1, 1.73205, 0, 1.73205, 1, 0, 0.732051, 2.73205,
      2, 0, 0, 2, -1, 1.73205, 2, 1.73205, 1, 2, 0.732051, 2.73205};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], rxcube[i], 1e-5);
  }
}

TEST(ModelTest, AffineChangeRotateY) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.ChangeRotateOnY(50);
  EXPECT_FALSE(result);
  std::vector<double> rycube = {0,       0, 0,        1.53209, 0, 1.28558,
                                0,       2, 0,        1.53209, 2, 1.28558,
                                1.28558, 0, -1.53209, 2.81766, 0, -0.246514,
                                1.28558, 2, -1.53209, 2.81766, 2, -0.246514};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], rycube[i], 1e-5);
  }
}

TEST(ModelTest, AffineChangeRotateZ) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.ChangeRotateOnZ(50);
  EXPECT_FALSE(result);
  std::vector<double> rzcube = {0,         0,       0, 0,         0,       2,
                                -1.53209,  1.28558, 0, -1.53209,  1.28558, 2,
                                1.28558,   1.53209, 0, 1.28558,   1.53209, 2,
                                -0.246514, 2.81766, 0, -0.246514, 2.81766, 2};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], rzcube[i], 1e-5);
  }
}

TEST(ModelTest, AffineMoveX) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.MoveOnX(50);
  EXPECT_FALSE(result);
  std::vector<double> mxcube = {50, 0, 0, 50, 0, 2, 50, 2, 0, 50, 2, 2,
                                52, 0, 0, 52, 0, 2, 52, 2, 0, 52, 2, 2};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], mxcube[i], 1e-5);
  }
}

TEST(ModelTest, AffineMoveY) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.MoveOnY(80);
  EXPECT_FALSE(result);
  std::vector<double> mycube = {0, 80, 0, 0, 80, 2, 0, 82, 0, 0, 82, 2,
                                2, 80, 0, 2, 80, 2, 2, 82, 0, 2, 82, 2};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], mycube[i], 1e-5);
  }
}

TEST(ModelTest, AffineMoveZ) {
  s21::Model model;
  bool result = model.Processing("tests/obj/cube.obj");
  model.MoveOnZ(1550);
  EXPECT_FALSE(result);
  std::vector<double> mzcube = {0, 0, 1550, 0, 0, 1552, 0, 2, 1550, 0, 2, 1552,
                                2, 0, 1550, 2, 0, 1552, 2, 2, 1550, 2, 2, 1552};
  for (size_t i = 0; i < model.get_obj_model().vertexes.size(); ++i) {
    ASSERT_NEAR(model.get_obj_model().vertexes[i], mzcube[i], 1e-5);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}