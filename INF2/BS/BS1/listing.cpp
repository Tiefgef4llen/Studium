#include <iostream>
#include <thread>
#include <string>

typedef struct stirngStruct {
    std::string name;
    int length;
} string_t;

void setLength(string_t* str) {
    str->length = str->name.length();
}

int main() {
    string_t str = {"Julian", 0};

    std::thread myThread = std::thread(setLength, &str);

    myThread.join();

    std::cout << str.length << std::endl;

    return 0;
}