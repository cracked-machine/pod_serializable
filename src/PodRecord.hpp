#include <array>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class PodRecord {
private:
  //  | name  ||  flag  | reserved | field 1 | reserved | field 2 |
  //  -----------------------------------------------------------
  //  | bytes ||    1   |    10    |   10    |    10    |   10    |
  //
  //
public:
  std::array<char, 1> m_flag{};
  std::array<char, 10> m_reserved_one{};
  std::array<char, 10> m_field_one{};
  std::array<char, 10> m_reserved_two{};
  std::array<char, 10> m_field_two{};

  /**
   * @brief Serialize the object reference into the given stream
   * 
   * @param out The stream to serialize to 
   * @param obj The object to serialize from 
   * @return std::ostream& 
   */
  friend std::ostream &operator<<(std::ostream &out, const PodRecord &obj) {
    // writes must mirror member declaration order
    out.write(obj.m_flag.data(), obj.m_flag.size());
    out.write(obj.m_reserved_one.data(), obj.m_reserved_one.size());
    out.write(obj.m_field_one.data(), obj.m_field_one.size());
    out.write(obj.m_reserved_one.data(), obj.m_reserved_two.size());
    out.write(obj.m_field_two.data(), obj.m_field_two.size());
    return out;
  }

  /**
   * @brief Deserialise the given stream into the object reference
   * 
   * @param in The stream to deserialize from
   * @param obj The object to receive the deserialization
   * @return std::istream& 
   */
  friend std::istream &operator>>(std::istream &in, PodRecord &obj) {
    // reads must mirror member declaration order
    in.read(obj.m_flag.data(), obj.m_flag.size());
    in.read(obj.m_reserved_one.data(), obj.m_reserved_one.size());
    in.read(obj.m_field_one.data(), obj.m_field_one.size());
    in.read(obj.m_reserved_two.data(), obj.m_reserved_two.size());
    in.read(obj.m_field_two.data(), obj.m_field_two.size());
    return in;
  }

  /**
   * @brief Returns member value as formatted string.
   * 
   * @tparam SIZE 
   * @param obj_member The member to get as string
   * @param to_ascii if true format output as ascii text, else hex/bytes
   * @return std::string 
   */
  template <size_t SIZE>
  std::string get(const std::array<char, SIZE> &obj_member, bool to_ascii) {
    std::stringstream out;
    for (const char &b : obj_member) {
      if (to_ascii) {
        out << std::dec << b;
      } else {
        out << std::hex << unsigned(b);
      }
    }
    return out.str();
  }
};