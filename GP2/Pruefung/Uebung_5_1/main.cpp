#include <iostream>
#include <vector>
#include <string>
int main( )
{
    std::string s = "Hello";
    std::cout << s.at(0) << "\n";
    s[0];
    s.length();
    std::cout << s.find("el") << "\n"; // Returns 1
    s.replace(s.find("el"), s.length(), "le");
    std::cout << s << "\n";
    // Vector--------
    std::vector<float> pos1(3); // Länge anfangs auf 3 setzen
    std::vector<float> pos{1.0, 2.0, 4.0};

    for(const auto& e : pos1) {
        std::cout << e <<"\n";
    }
    for(const auto& e : pos) {
        std::cout << e <<"\n";
    }
    pos.size();
    return 0;
}