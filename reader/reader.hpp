#ifndef READER_HPP
#define READER_HPP

#include <iostream>

#include "simdjson/simdjson.h"
#include "lib/api/longpoll_api.hpp"
#include "message.hpp"

namespace reader{
    class chat_reader{
    private:
        vk::longpoll_api _lp;
        reader::message _msg;

        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        [[noreturn]] void run();
    };
}

#endif //READER_HPP