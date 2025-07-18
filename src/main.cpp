#include <fstream>
#include <ostream>
#include <string>
#include <iomanip>
#include <PodRecord.hpp>

int main()
{

    std::ofstream outPodFile{"pod.bin", outPodFile.binary};
    PodRecord podRecord{1, {}, "helloworld"};
    outPodFile << podRecord;

    return 0;
}