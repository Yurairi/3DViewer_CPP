#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>

class Strategy {
 public:
  virtual ~Strategy() {}
  virtual bool use(const std::string& file_path) = 0;
};

#endif  // STRATEGY_H
