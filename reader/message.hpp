#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "simdjson/simdjson.h"
#include "lib/api/vk_api.hpp"
#include "message_parser.hpp"
#include "reader/reader_data.hpp"

namespace reader{
    class message{
    private:
        simdjson::dom::element _json;
        vk::api::vk_api _api;
        vk::reader::reader_data _data;
        reader::message_parser _mp;
    public:
        simdjson::dom::element operator=(const simdjson::dom::element& json);

        std::string msg();
        std::string from();
        std::string time();
    };
}

#endif //MESSAGE_HPP