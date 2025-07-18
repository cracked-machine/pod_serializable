#include <ostream>
#include <array>
#include <iostream>
#include <string>

class PodRecord
{
private:
    
public:
    // important flag data, pass in true/false
    std::array<char, 1> m_flag{};
    // don't care; pass in {}
    std::array<char, 10> m_padding{};
    // text data, pass in string literal
    std::array<char, 12> m_field{};

    friend std::ostream& operator<<(std::ostream& out, const PodRecord& obj) 
    {
        out.write(obj.m_flag.data(), obj.m_flag.size());
        out.write(obj.m_padding.data(), obj.m_padding.size());
        out.write(obj.m_field.data(), obj.m_field.size());
        return out;
    }
    friend std::istream& operator>>(std::istream& in, PodRecord& obj)
    {
        in.read(obj.m_flag.data(), obj.m_flag.size());
        in.read(obj.m_padding.data(), obj.m_padding.size());
        in.read(obj.m_field.data(), obj.m_field.size());
        return in;
    }

    unsigned get_flag_one()
    {
        return unsigned(m_flag[0]);
    }

    std::string get_field_one()
    {
        return {m_field.begin(), m_field.end()};
    }
};