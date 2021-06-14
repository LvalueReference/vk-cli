#include "message.hpp"

void vk::reader::message::init(const simdjson::dom::element& json){
        _json = json;

        _data.message = _json["object"]["message"]["text"].get_c_str();
        _data.from_id = _json["object"]["message"]["from_id"].get_int64();
        _data.peer_id = _json["object"]["message"]["peer_id"].get_int64();
}

bool vk::reader::message::has_reply() {
    return _json["object"]["message"]["reply_message"].is_object();
}

bool vk::reader::message::has_attachments() {
    return _json["object"]["message"]["attachments"].get_array().size() != 0;
}

bool vk::reader::message::has_fwd() {
    return _json["object"]["message"]["fwd_messages"].get_array().size() != 0;
}

std::string vk::reader::message::get_attachment_type(const simdjson::dom::object& att) {
    return std::string(att["type"]);
}

std::string vk::reader::message::get_attachments_count(const simdjson::dom::object& att) {
    return std::to_string(att.size());
}

std::string vk::reader::message::get_reply_text() {
    return std::string(_json["object"]["message"]["reply_message"]["text"]);
}

std::string vk::reader::message::msg() {
    std::string res = _data.message;

    if (has_reply())
        res.insert(0, "{reply: " + get_reply_text() + "} ");

    if (has_attachments()) {
        for (const auto& att : _json["object"]["message"]["attachments"].get_array()) {
            res.insert(0, "{" + get_attachment_type(att) + ": " + get_attachments_count(att) + "} ");
        }
    }

    return res;
}

std::string vk::reader::message::from() {
    return (_data.from_id > 0 ? _api.user_get(_data.from_id) : _api.group_get(_data.from_id));
}

std::string vk::reader::message::time() {
    time_t t;
    ::time(&t);

    tm* tme = localtime(&t);

    return std::to_string(tme->tm_hour) + ':' + std::to_string(tme->tm_min);
}