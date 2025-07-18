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

    // universal member-to-string accessor
    // supports byte/hex or ascii output format
    template<class MEMBER>
    std::string get(const MEMBER& member, bool to_ascii)
    {
        std::stringstream out;
        for( const char &b: member) { 
            if (to_ascii) { out << std::dec << b; }
            else { out << std::hex << unsigned(b); }
        }
        return out.str();
    }
};