#include <iostream>

class OOBase {
public:
  OOBase() = default;
  virtual ~OOBase(){};
  virtual void serialize(std::ostream &out) = 0;
  virtual void deserialize(std::istream &out) = 0;
};