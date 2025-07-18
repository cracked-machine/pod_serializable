#include <fstream>
#include <ostream>
#include <PodRecord.hpp>

int main()
{
    // serialize the POD-type object to binary file
    {
        std::ofstream is{"pod.bin", is.binary};
        if( not is.is_open() ) { return 1; }
        
        PodRecord podRecord{true, {}, "helloworld"};

        is << podRecord;
        is.flush();
    }

    // deserialize the POD-type object from binary file
    {
        std::ifstream os{"pod.bin", os.binary};
        if( not os.is_open() ) { return 1; }
        
        PodRecord podRecord2{0, {}, "overwriteme"};
        os >> podRecord2;
        std::cout << podRecord2.get_flag_one() << "\n";
        std::cout << podRecord2.get_field_one() << "\n";
    }
    
    return 0;
}