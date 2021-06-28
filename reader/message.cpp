#include "message.hpp"

simdjson::dom::element reader::message::operator=(const simdjson::dom::element &json) {
    _mp = json;
    return _json = json;
}

std::string reader::message::msg() {
    std::string res = _data.message;

    if (_mp.has_reply()){
        res.insert(0, "{reply to " + _mp.get_reply_from() + ": " + _mp.get_reply_attachments_types() + _mp.get_reply_text() + "} ");
    }

    if (_mp.has_attachments()){
        for (const auto& att : _mp.get_attachments()){
            res.insert(0, '{' + _mp.get_attachment_type(att) + "} ");
        }
    }

    return res;
}

std::string reader::message::from() {
    return (_data.from_id > 0 ? _api.user_get(_data.from_id) : _api.group_get(_data.from_id));
}

std::string reader::message::time() {
    time_t t;
    ::time(&t);

    tm* tme = localtime(&t);

    return std::to_string(tme->tm_hour) + ':' + std::to_string(tme->tm_min);
}