#include <iostream>
#include "reader/reader.hpp"

int main(){
    vk::api::longpoll_api lp;
    std::cout << lp.listen() << std::endl;

    return EXIT_SUCCESS;
}
