#ifndef MESSAGE_PARSER_HPP
#define MESSAGE_PARSER_HPP

#include "lib/api/vk_api.hpp"
#include "simdjson.h"

namespace reader{
    class message_parser{
    private:
        vk::vk_api _api;
        simdjson::dom::element _json;

    public:
        void operator=(simdjson::dom::element json);

        bool has_reply() const;
        bool has_fwd() const;
        bool has_fwd(simdjson::dom::element json) const;
        bool has_attachments() const;
        bool has_attachments(simdjson::dom::element json) const;

        simdjson::dom::element get_reply() const;
        simdjson::dom::array get_fwd() const;
        simdjson::dom::array get_fwd(simdjson::dom::element json) const;
        simdjson::dom::array get_attachments() const;
        simdjson::dom::array get_attachments(simdjson::dom::element json) const;

        std::string get_reply_text() const;
        std::string get_reply_from() const;
        std::string get_attachment_type() const;
        std::string get_attachment_type(simdjson::dom::element json) const;
        std::string get_reply_attachments_types() const;
        std::string get_fwd_attachments_types(simdjson::dom::element fwd) const;
        std::string get_fwd_text(simdjson::dom::element fwd) const;
        std::string get_fwd_from(simdjson::dom::element fwd) const;
    };
}

#endif //MESSAGE_PARSER_HPP