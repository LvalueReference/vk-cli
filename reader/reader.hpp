#ifndef READER_HPP
#define READER_HPP

#include <iostream>

#include "simdjson.h"
#include "lib/api/longpoll_api.hpp"
#include "message.hpp"

namespace reader{
    class chat_reader{
    private:
        vk::longpoll_api _longpoll;
        reader::message _message;

        simdjson::dom::element _json;
        simdjson::dom::parser _parser;
    public:
        void run();
    };
}

#endif //READER_HPP