#include "message.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <fmt/format.h>

simdjson::dom::element reader::message::operator=(const simdjson::dom::element &json) {
    _rdata = reader::reader_data{
        std::string(json["object"]["message"]["text"]),
        json["object"]["message"]["peer_id"],
        json["object"]["message"]["from_id"]
    };

    _mp = json;
    _json = json;
}

std::string reader::message::message_text(){
    std::string res = _rdata.message;

    if (_mp.has_reply())
        res.insert(0, fmt::format("[reply to {}: {}{}] ", _mp.get_reply_from(),
                                                          _mp.get_reply_attachments_types(),
                                                          _mp.get_reply_text()));

    if (_mp.has_attachments()){
        for (const auto& att : _mp.get_attachments()){
            res.append(fmt::format(" [{}]", _mp.get_attachment_type(att)));
        }
    }

    if (_mp.has_fwd()){
        res.append(" {fwd message}:\n");

        for (const auto& fwd : _mp.get_fwd()){
            res.append(fmt::format("\t\t\t\033[0m┌[\033[1;32m{}\033[0m]\n\t\t\t└[message]> \033[1;36m{}{}\033[0m\n",
                                   _mp.get_fwd_from(fwd),
                                   _mp.get_fwd_attachments_types(fwd),
                                   _mp.get_fwd_text(fwd)));
        }
    }

    return res;
}

std::string reader::message::from() {
    return (_rdata.from_id > 0 ? _api.user_get(_rdata.from_id) : _api.group_get(_rdata.from_id));
}

std::string reader::message::current_time() {
	std::ostringstream out;

	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() - std::chrono::hours(24));
    out << std::put_time(std::localtime(&now), "%T");
	
    return out.str();
}

std::string reader::message::chat_name() {
    return _api.get_chat_name(_rdata.peer_id);
}