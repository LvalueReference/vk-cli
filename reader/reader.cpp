#include "reader.hpp"
#include <fmt/format.h>

[[noreturn]] void reader::chat_reader::run(){
    std::cout << "[ STARTED ]" << std::endl;

    while (true){
        _json = _parser.parse(_lp.listen());

        if (_json["updates"].get_array().size() != 0){
            for (const auto& updates : _json["updates"].get_array()){
                _msg = updates;

                std::cout << fmt::format("┌[\033[32m{}\033[0m] ({}) [{}]\n└[message]> \033[33m{}\033[0m",
                                         _msg.from(),
                                         _msg.current_time(),
                                         _msg.chat_name(),
                                         _msg.message_text()) << std::endl;
            }
        }
    }
}