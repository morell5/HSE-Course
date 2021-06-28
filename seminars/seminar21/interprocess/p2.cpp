#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    
    std::string name;     

    // connector
    std::filesystem::path path_to_connector("connector.txt");
    std::fstream connector(path_to_connector, std::ios::in);
    connector >> name;

    std::cout << "name:" << name << std::endl;
    // String -> Ptr
    std::stringstream ss_in;
    ss_in << name;
    long long unsigned int i;
    ss_in >> std::hex >> i;
    int* i_ptr = reinterpret_cast<int*>(i);
    
    std::cout << "*i_ptr:" << (*i_ptr) << std::endl;
    return 0;
}