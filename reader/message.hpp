#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "simdjson.h"
#include "reader_data.hpp"
#include "lib/api/vk_api.hpp"
#include "message_parser.hpp"

namespace reader{
    class message{
    private:
        simdjson::dom::element _json;
        reader::reader_data _reader_data;
        vk::vk_api _api;
        reader::message_parser _message_parser;
    public:
        void operator=(const simdjson::dom::element &json);

        std::string message_text() const;
        std::string from() const;
        std::string chat_name() const;
        std::string current_time() const;
    };
}

#endif //MESSAGE_HPP