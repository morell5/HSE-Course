#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // Ptr -> String
    int* x = new int(100);

    // connector
    std::filesystem::path path_to_connector("connector.txt");
    std::fstream connector(path_to_connector, std::ios::out);
    connector << x;
    connector.close();
    std::cout << "addr:" << (x) << std::endl;
    std::cout << "*addr:" << (*x) << std::endl;
    
    while (true) {};
    return 0;
}