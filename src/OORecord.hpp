#include <OOBase.hpp>
#include <array>

/**
 * @brief   
 * | name  ||  flag  | reserved | field 1 | reserved | field 2 |
 * -----------------------------------------------------------
 * | bytes ||    1   |    10    |   10    |    10    |   10    |
 */
class OORecord : public OOBase {
public:
  OORecord() = default;
  OORecord(std::array<char, 1> flag, std::array<char, 10> reserved_one,
           std::array<char, 10> field_one, std::array<char, 10> reserved_two,
           std::array<char, 10> field_two)
      : m_flag(flag), m_reserved_one(reserved_one), m_field_one(field_one),
        m_reserved_two(reserved_two), m_field_two(field_two) {}

  /**
   * @brief Serialize this object into the given stream
   *
   * @param out The stream to serialize to
   * @return std::ostream&
   */
  void serialize(std::ostream &out) {
    // writes must mirror member declaration order
    out.write(m_flag.data(), m_flag.size());
    out.write(m_reserved_one.data(), m_reserved_one.size());
    out.write(m_field_one.data(), m_field_one.size());
    out.write(m_reserved_one.data(), m_reserved_two.size());
    out.write(m_field_two.data(), m_field_two.size());
    out.flush();
  }

  /**
   * @brief Deserialise the given stream into this object
   *
   * @param in The stream to deserialize from
   * @return std::istream&
   */
  void deserialize(std::istream &in) {
    // reads must mirror member declaration order
    in.read(m_flag.data(), m_flag.size());
    in.read(m_reserved_one.data(), m_reserved_one.size());
    in.read(m_field_one.data(), m_field_one.size());
    in.read(m_reserved_two.data(), m_reserved_two.size());
    in.read(m_field_two.data(), m_field_two.size());
  }

  /**
   * @brief Serialize the object reference into the given stream
   *
   * @param out The stream to serialize to
   * @param obj The object to serialize from
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &out, const OORecord &obj) {
    // writes must mirror member declaration order
    out.write(obj.m_flag.data(), obj.m_flag.size());
    out.write(obj.m_reserved_one.data(), obj.m_reserved_one.size());
    out.write(obj.m_field_one.data(), obj.m_field_one.size());
    out.write(obj.m_reserved_one.data(), obj.m_reserved_two.size());
    out.write(obj.m_field_two.data(), obj.m_field_two.size());
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
  friend std::istream &operator>>(std::istream &in, OORecord &obj) {
    // reads must mirror member declaration order
    in.read(obj.m_flag.data(), obj.m_flag.size());
    in.read(obj.m_reserved_one.data(), obj.m_reserved_one.size());
    in.read(obj.m_field_one.data(), obj.m_field_one.size());
    in.read(obj.m_reserved_two.data(), obj.m_reserved_two.size());
    in.read(obj.m_field_two.data(), obj.m_field_two.size());
    return in;
  }



private:
  std::array<char, 1> m_flag{};
  std::array<char, 10> m_reserved_one{};
  std::array<char, 10> m_field_one{};
  std::array<char, 10> m_reserved_two{};
  std::array<char, 10> m_field_two{};
};