#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "simdjson/simdjson.h"
#include "reader_data.hpp"
#include "lib/api/vk_api.hpp"
#include "message_parser.hpp"

namespace reader{
    class message{
    private:
        simdjson::dom::element _json;
        reader::reader_data _rdata;
        vk::api::vk_api _api;
        reader::message_parser _mp;
    public:
        simdjson::dom::element operator= (const simdjson::dom::element& json);

        std::string message_text();
        std::string from();
        std::string chat_name();
        std::string current_time();
    };
}

#endif //MESSAGE_HPP