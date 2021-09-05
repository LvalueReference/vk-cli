#include "reader.hpp"
#include "fmt/format.h"

void reader::chat_reader::run(){
    std::cout << "==========[ \033[1;32mSTARTED\033[0m ]==========" << std::endl;

    while (true){
        _json = _parser.parse(_longpoll.listen());

        if (_json["updates"].get_array().size() != 0){
            for (const auto& updates: _json["updates"].get_array()){
                _message = updates;

                std::cout << fmt::format("┌[\033[1;32m{}\033[0m] ({}) [{}]\n└[message]-> \033[1;33m{}\033[0m",
                                         _message.from(), _message.current_time(), _message.chat_name(),
                                         _message.message_text()) << std::endl;
            }
        }
    }
}