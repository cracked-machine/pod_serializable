#include <PodRecord.hpp>
#include <fstream>
#include <ostream>
#include <sstream>

namespace Format {
/**
 * @brief Returns std::array<char, size_t> as formatted string.
 *
 * @tparam SIZE
 * @param obj_member The member to get as string
 * @param to_ascii if true format output as ascii text, else hex/bytes
 * @return std::string
 */
template <size_t SIZE>
std::string as_string(const std::array<char, SIZE> &obj_member, bool to_ascii) {
  std::stringstream out;
  for (const char &b : obj_member) {
    to_ascii ? 
      out << std::dec << b : 
      out << std::hex << unsigned(b);
  }
  return out.str();
}
} // namespace Format

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
    podRecord.serialize(os);
    
  }

  // deserialize the POD-type object from binary file
  {
    std::ifstream is{"pod.bin", is.binary};
    if (not is.is_open()) {
      return 1;
    }

    PodRecord podRecord2;
    podRecord2.deserialize(is);

    std::cout << Format::as_string(podRecord2.m_flag, false) << "\n";
    std::cout << Format::as_string(podRecord2.m_field_one, false) << "\n";
    std::cout << Format::as_string(podRecord2.m_field_two, true) << "\n";
  }

  return 0;
}