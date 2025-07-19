#include <PodRecord.hpp>
#include <fstream>
#include <ostream>

int main() {
  // serialize the POD-type object to binary file
  {
    std::ofstream os{"pod.bin", os.binary};
    if (not os.is_open()) {
      return 1;
    }

    PodRecord podRecord{true,
                        {}, // reserved
                        {0xD, 0xE, 0xA, 0xD, 0xB, 0xE, 0xE, 0xF},
                        {}, // reserved
                        "1.1.1.1"};
    os << podRecord;
    os.flush();
  }

  // deserialize the POD-type object from binary file
  {
    std::ifstream is{"pod.bin", is.binary};
    if (not is.is_open()) {
      return 1;
    }

    PodRecord podRecord2;
    is >> podRecord2;

    std::cout << podRecord2.get(podRecord2.m_flag, false) << "\n";
    std::cout << podRecord2.get(podRecord2.m_field_one, false) << "\n";
    std::cout << podRecord2.get(podRecord2.m_field_two, false) << "\n";
  }

  return 0;
}