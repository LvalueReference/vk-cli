#include "reader.hpp"

[[noreturn]] void reader::chat_reader::run() {
    std::cout << "[ STARTED ]" << std::endl;

    while (true){
        _json = _parser.parse(_lp.listen());

        if (_json["updates"].get_array().size() != 0){
            for (const auto& updates : _json["updates"].get_array()){
                _msg = updates;

                std::cout << "┌[\033[32m" + _msg.from() << "\033[0m] (" << _msg.current_time()  << ")\n"
                             "└[message]> \033[35m" << _msg.message_text() << "\033[0m" << std::endl;
            }
        }
    }
}