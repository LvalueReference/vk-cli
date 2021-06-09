#include "reader/reader.hpp"

void vk::reader::init(){
    for (const auto& updates : _json["updates"].get_array()){
        _message = updates["object"]["message"]["text"].get_c_str();
        _peer_id = updates["object"]["message"]["peer_id"].get_int64();
        _from_id = updates["object"]["message"]["from_id"].get_int64();
    }
}

static bool has_reply(const simdjson::dom::element& json){
    return json["object"]["message"]["reply_message"].is_object();
}

std::string vk::reader::message() {
    std::string res = _message;

    for (const auto& updates : _json["updates"].get_array()){
        if (has_reply(updates)){
            res.insert(0, "[reply: " + std::string(updates["object"]["message"]["reply_message"]["text"]) + "] ");
        }
    }

    return res;
}

std::string vk::reader::from() {
    return "[" + (_from_id > 0 ? _api.user_get(_from_id) : _api.group_get(_from_id)) + "] ";
}

void vk::reader::run(){
    std::cout << "Started" << std::endl;

    while(true){
        _lp.listen(_response);
        _json = _parser.parse(_response);

        if (_json["updates"].get_array().size() != 0){
            init();
            std::cout << from() << "$-> " << message() << std::endl;
        } else continue;
    }
}