#include "message.hpp"

simdjson::dom::element reader::message::operator=(const simdjson::dom::element &json) {
    _rdata = reader::reader_data{
        std::string(json["object"]["message"]["text"]),
        json["object"]["message"]["peer_id"],
        json["object"]["message"]["from_id"]
    };

    _mp = json;
    _json = json;
}

std::string reader::message::message_text() {
    std::string res = _rdata.message;

    if (_mp.has_reply())
        res.insert(0, "{reply to " + _mp.get_reply_from() + ": " + _mp.get_reply_attachments_types() + _mp.get_reply_text() + "} ");

    if (_mp.has_attachments()){
        for (const auto& att : _mp.get_attachments()){
            res.insert(0, '{' + _mp.get_attachment_type(att) + "} ");
        }
    }

    return res;
}

std::string reader::message::from() {
    return (_rdata.from_id > 0 ? _api.user_get(_rdata.from_id) : _api.group_get(_rdata.from_id));
}

std::string reader::message::current_time() {
    time_t t;
    ::time(&t);

    tm* tme = localtime(&t);

    return std::to_string(tme->tm_hour) + ':' + std::to_string(tme->tm_min);
}