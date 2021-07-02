#include "message.hpp"
#include <ostream>

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

    if (_mp.has_fwd()){
        res.append(" {fwd message}:\n");

        for (const auto& fwd : _mp.get_fwd()){
            res.append("\t\t\t\033[0m┌[\033[32m" + _mp.get_fwd_from(fwd) + "\033[0m]\n"
                              "\t\t\t└[message]> \033[36m" + _mp.get_fwd_attachments_types(fwd) +
                                                             _mp.get_fwd_text(fwd) + "\033[0m\n");
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