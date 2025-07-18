#include <ostream>
#include <array>
#include <iostream>
#include <string>
#include <sstream>

class PodRecord
{
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

    friend std::ostream& operator<<(std::ostream& out, const PodRecord& obj) 
    {
        // writes must mirror member declaration order
        out.write(obj.m_flag.data(), obj.m_flag.size());
        out.write(obj.m_reserved_one.data(), obj.m_reserved_one.size());
        out.write(obj.m_field_one.data(), obj.m_field_one.size());
        out.write(obj.m_reserved_one.data(), obj.m_reserved_two.size());
        out.write(obj.m_field_two.data(), obj.m_field_two.size());
        return out;
    }

    friend std::istream& operator>>(std::istream& in, PodRecord& obj)
    {
        // reads must mirror member declaration order
        in.read(obj.m_flag.data(), obj.m_flag.size());
        in.read(obj.m_reserved_one.data(), obj.m_reserved_one.size());
        in.read(obj.m_field_one.data(), obj.m_field_one.size());
        in.read(obj.m_reserved_two.data(), obj.m_reserved_two.size());
        in.read(obj.m_field_two.data(), obj.m_field_two.size());
        return in;
    }

    // Universal member-to-string accessor.
    // pod_member: Pass in POD **object** member to get the string repr.
    // to_ascii: The output format. ascii if true, byte/hex if false.
    template<size_t SIZE>
    std::string get(
        const std::array<char, SIZE>& pod_member, 
        bool to_ascii
    )
    {
        std::stringstream out;
        for( const char &b: pod_member) { 
            if (to_ascii) { out << std::dec << b; }
            else { out << std::hex << unsigned(b); }
        }
        return out.str();
    }
};