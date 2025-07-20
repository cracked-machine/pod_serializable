#include <OORecord.hpp>
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
    to_ascii ? out << std::dec << b : out << std::hex << unsigned(b);
  }
  return out.str();
}
} // namespace Format

int test_oorecord() {
  // serialize the POD-type object to binary file
  {
    std::ofstream os{"oorecord.bin", os.binary};
    if (not os.is_open()) {
      return 1;
    }

    OORecord record({1}, {},                                      
                    {0xD, 0xE, 0xA, 0xD, 0xB, 0xE, 0xE, 0xF}, {},
                    {"1.1.1.1"});
    record.serialize(os);
  }

  // deserialize the POD-type object from binary file
  {
    std::ifstream is{"oorecord.bin", is.binary};
    if (not is.is_open()) {
      return 1;
    }

    OORecord record;
    record.deserialize(is);

    // std::cout << Format::as_string(record.m_flag, false) << "\n";
    // std::cout << Format::as_string(record.m_field_one, false) << "\n";
    // std::cout << Format::as_string(record.m_field_two, true) << "\n";
  }

  return 0;
}

int test_podrecord() {
  // serialize the POD-type object to binary file
  {
    std::ofstream os{"podrecord.bin", os.binary};
    if (not os.is_open()) {
      return 1;
    }

    PodRecord record{true,
                        {}, // reserved
                        {0xD, 0xE, 0xA, 0xD, 0xB, 0xE, 0xE, 0xF},
                        {}, // reserved
                        "1.1.1.1"};
    // record.serialize(os);
    os << record;
  }

  // deserialize the POD-type object from binary file
  {
    std::ifstream is{"podrecord.bin", is.binary};
    if (not is.is_open()) {
      return 1;
    }

    PodRecord record;
    // record.deserialize(is);
    is >> record;

    std::cout << Format::as_string(record.m_flag, false) << "\n";
    std::cout << Format::as_string(record.m_field_one, false) << "\n";
    std::cout << Format::as_string(record.m_field_two, true) << "\n";
  }

  return 0;
}

int main() {
  int result;

  if (result == test_podrecord()) {
    return result;
  }
  
  if (result == test_oorecord()) {
    return result;
  }

  return 0;
}