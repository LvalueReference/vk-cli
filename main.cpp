#include <iostream>
#include "reader/reader.hpp"

int main(){
    reader::chat_reader reader;
    reader.run();

    return EXIT_SUCCESS;
}
