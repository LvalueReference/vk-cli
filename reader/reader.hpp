#ifndef READER_HPP
#define READER_HPP

#include "lib/api/vk_api.hpp"
#include "lib/api/longpoll_api.hpp"
#include "lib/network/network.hpp"
#include "simdjson/simdjson.h"
#include "reader_data.hpp"
#include "message.hpp"

#include <time.h>

namespace vk{
    namespace reader {
        class reader {
        private:
            //vk::api::vk_api _api;
            vk::api::longpoll_api _lp;

            //vk::reader::reader_data _data;
            vk::reader::message _data;

            simdjson::dom::parser _parser;
            simdjson::dom::element _json;
        public:
            void run();
        };
    }
}

#endif //READER_HPP
