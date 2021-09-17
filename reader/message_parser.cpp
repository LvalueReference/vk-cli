#include "message_parser.hpp"
#include "fmt/format.h"

void reader::message_parser::operator=(simdjson::dom::element json){
    _json = json;
}

bool reader::message_parser::has_reply() const{
    return _json["object"]["message"]["reply_message"].is_object();
}

bool reader::message_parser::has_fwd() const{
    return _json["object"]["message"]["fwd_messages"].get_array().size() != 0;
}

bool reader::message_parser::has_fwd(simdjson::dom::element json) const{
    return json["fwd_messages"].is_array();
}

bool reader::message_parser::has_attachments() const{
    return _json["object"]["message"]["attachments"].get_array().size() != 0;
}

bool reader::message_parser::has_attachments(simdjson::dom::element json) const{
    return json["attachments"].get_array().size() != 0;
}


simdjson::dom::element reader::message_parser::get_reply() const{
    return _json["object"]["message"]["reply_message"];
}

simdjson::dom::array reader::message_parser::get_fwd() const{
    return _json["object"]["message"]["fwd_messages"].get_array();
}

simdjson::dom::array reader::message_parser::get_attachments() const{
    return _json["object"]["message"]["attachments"].get_array();
}

simdjson::dom::array reader::message_parser::get_attachments(simdjson::dom::element json) const{
    return json["attachments"].get_array();
}

std::string reader::message_parser::get_reply_text() const{
    return std::string(get_reply()["text"]);
}

std::string reader::message_parser::get_reply_from() const{
    std::int64_t from_id = get_reply()["from_id"];

    return (from_id > 0 ? _api.user_get(from_id) : _api.group_get(from_id));
}

std::string reader::message_parser::get_attachment_type() const{
    return std::string(get_attachments().at(0)["type"]);
}

std::string reader::message_parser::get_attachment_type(simdjson::dom::element json) const{
    return std::string(json["type"]);
}

std::string reader::message_parser::get_reply_attachments_types() const{
    if (!has_attachments(get_reply())) return "";

    std::string result;

    for (const auto& att : get_attachments(get_reply()))
        result.insert(0, fmt::format("[{}] ", get_attachment_type(att)));

    return result;
}

std::string reader::message_parser::get_fwd_attachments_types(simdjson::dom::element fwd) const{
    if (!has_attachments(fwd)) return "";

    std::string result;

    for (const auto& att : get_attachments(fwd))
        result.insert(0, fmt::format("[{}] ", get_attachment_type(att)));

    return result;
}

std::string reader::message_parser::get_fwd_text(simdjson::dom::element fwd) const{
    return std::string(fwd["text"]);
}

std::string reader::message_parser::get_fwd_from(simdjson::dom::element fwd) const{
    std::int64_t from_id = fwd["from_id"];

    return (from_id > 0 ? _api.user_get(from_id) : _api.group_get(from_id));
}