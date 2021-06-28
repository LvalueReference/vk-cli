#ifndef READER_HPP
#define READER_HPP

#include "lib/api/longpoll_api.hpp"
#include "simdjson/simdjson.h"
#include "reader_data.hpp"
#include "message.hpp"

#include <time.h>

namespace reader {
    class reader {
    private:
        vk::api::longpoll_api _lp;

        message _data;

        simdjson::dom::parser _parser;
        simdjson::dom::element _json;
    public:
        void run();
    };
}

#endif //READER_HPP
