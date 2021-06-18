#include "reader.hpp"
#include <iomanip>

void vk::reader::reader::run(){
    std::cout << "==========[ Starting to read the chat ]==========" << std::endl;

    while(true){
        _json = _parser.parse(_lp.listen());

        if (_json["updates"].get_array().size() != 0){
            for (const auto& updates : _json["updates"].get_array())
                _data.init(updates);

            std::cout << "┌[\033[32m" + _data.from() << "\033[0m] (" << _data.time()  << ")\n"
                         "└[message]> \033[35m" << _data.msg() << "\033[0m" << std::endl;
        }
    }
}