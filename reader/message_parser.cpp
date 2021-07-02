#include "message_parser.hpp"

simdjson::dom::element reader::message_parser::operator=(const simdjson::dom::element &json) {
    _json = json;
}


bool reader::message_parser::has_reply() {
    return _json["object"]["message"]["reply_message"].is_object();
}

bool reader::message_parser::has_fwd() {
    return _json["object"]["message"]["fwd_messages"].get_array().size() != 0;
}

bool reader::message_parser::has_fwd(const simdjson::dom::element &json) {
    return json["fwd_messages"].is_array();
}

bool reader::message_parser::has_attachments() {
    return _json["object"]["message"]["attachments"].get_array().size() != 0;
}

bool reader::message_parser::has_attachments(const simdjson::dom::element &json) {
    return json["attachments"].get_array().size() != 0;
}


simdjson::dom::element reader::message_parser::get_reply() {
    return _json["object"]["message"]["reply_message"];
}

simdjson::dom::array reader::message_parser::get_fwd() {
    return _json["object"]["message"]["fwd_messages"].get_array();
}

simdjson::dom::array reader::message_parser::get_attachments() {
    return _json["object"]["message"]["attachments"].get_array();
}

simdjson::dom::array reader::message_parser::get_attachments(const simdjson::dom::element &json) {
    return json["attachments"].get_array();
}

std::string reader::message_parser::get_reply_text() {
    return std::string(get_reply()["text"]);
}

std::string reader::message_parser::get_reply_from() {
    int from_id = get_reply()["from_id"].get_int64();

    return (from_id > 0 ? _api.user_get(from_id) : _api.group_get(from_id));
}

std::string reader::message_parser::get_attachment_type() {
    return std::string(get_attachments().at(0)["type"]);
}

std::string reader::message_parser::get_attachment_type(const simdjson::dom::element& json) {
    return std::string(json["type"]);
}

std::string reader::message_parser::get_reply_attachments_types() {
    if(!has_attachments(get_reply())) return "";

    std::string res;

    for (const auto& att : get_attachments(get_reply()))
        res.insert(0, '{' + get_attachment_type(att) + "} ");

    return res;
}

std::string reader::message_parser::get_fwd_attachments_types(const simdjson::dom::element& fwd) {
    if (!has_attachments(fwd)) return "";

    std::string res;

    for (const auto& att : get_attachments(fwd))
        res.insert(0, '{' + get_attachment_type(att) + "} ");

    return res;
}

std::string reader::message_parser::get_fwd_text(const simdjson::dom::element& fwd) {
    return std::string(fwd["text"]);
}

std::string reader::message_parser::get_fwd_from(const simdjson::dom::element& fwd) {
    int from_id = fwd["from_id"].get_int64();

    return (from_id > 0 ? _api.user_get(from_id) : _api.group_get(from_id));
}