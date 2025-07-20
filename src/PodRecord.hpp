#include <array>
#include <iostream>
#include <ostream>

/**
 * @brief   
 * | name  ||  flag  | reserved | field 1 | reserved | field 2 |
 * -----------------------------------------------------------
 * | bytes ||    1   |    10    |   10    |    10    |   10    |
 */
class PodRecord {
public:
  std::array<char, 1> m_flag{};
  std::array<char, 10> m_reserved_one{};
  std::array<char, 10> m_field_one{};
  std::array<char, 10> m_reserved_two{};
  std::array<char, 10> m_field_two{};

  /**
   * @brief Serialize this object into the given stream
   *
   * @param out The stream to serialize to
   * @return std::ostream&
   */
  void serialize(std::ostream &out) {
    out.write(reinterpret_cast<const char *>(this), sizeof(*this));
    out.flush();
  }

  /**
   * @brief Deserialise the given stream into this object
   *
   * @param in The stream to deserialize from
   * @return std::istream&
   */
  void deserialize(std::istream &in) {
    in.read(reinterpret_cast<char *>(this), sizeof(*this));
  }

  /**
   * @brief Serialize the object reference into the given stream
   *
   * @param out The stream to serialize to
   * @param obj The object to serialize from
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &out, const PodRecord &obj) {
    out.write(reinterpret_cast<const char *>(&obj), sizeof(obj));
    out.flush();
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
    in.read(reinterpret_cast<char *>(&obj), sizeof(obj));
    return in;
  }
};