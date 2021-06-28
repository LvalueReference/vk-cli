#ifndef MESSAGE_PARSER_HPP
#define MESSAGE_PARSER_HPP

#include "simdjson/simdjson.h"
#include "lib/api/vk_api.hpp"

namespace reader{
    class message_parser{
    private:
        vk::api::vk_api _api;
        simdjson::dom::element _json;
    public:
        simdjson::dom::element operator= (const simdjson::dom::element& json);

        bool has_reply();
        bool has_attachments();
        bool has_attachments(const simdjson::dom::element& json);


        simdjson::dom::element get_reply();
        simdjson::dom::array get_attachments();
        simdjson::dom::array get_attachments(const simdjson::dom::element& json);

        std::string get_reply_text();
        std::string get_reply_from();
        std::string get_attachment_type();
        std::string get_attachment_type(const simdjson::dom::element& json);
        std::string get_reply_attachments_types();
    };
}

#endif //MESSAGE_PARSER_HPP