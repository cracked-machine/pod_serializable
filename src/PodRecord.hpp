#include <ostream>
#include <array>
#include <iomanip>
#include <iostream>
#include <string>

class PodRecord
{
private:
    
public:
    std::array<char, 1> m_flag_one{};
    std::array<char, 10> m_padding_one{};
    std::array<char, 11> m_field_one{};

    friend std::ostream& operator<<(std::ostream& out, const PodRecord& obj) 
    {
        out.write(obj.m_flag_one.data(), obj.m_flag_one.size());
        out.write(obj.m_padding_one.data(), obj.m_padding_one.size());
        out.write(obj.m_field_one.data(), obj.m_field_one.size());
        return out;
    }
    friend std::istream& operator>>(std::istream& in, PodRecord& obj)
    {
        in.read(obj.m_flag_one.data(), obj.m_flag_one.size());
        in.read(obj.m_padding_one.data(), obj.m_padding_one.size());
        in.read(obj.m_field_one.data(), obj.m_field_one.size());
        return in;
    }

};