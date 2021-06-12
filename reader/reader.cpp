#include "reader.hpp"
#include <iomanip>

static bool has_reply(const simdjson::dom::element& json){
    return json["object"]["message"]["reply_message"].is_object();
}

static bool has_attachments(const simdjson::dom::element& json){
    return json["object"]["message"]["attachments"].get_array().size() != 0;
}

static std::string get_reply_text(const simdjson::dom::element& json){
    return std::string(json["object"]["message"]["reply_message"]["text"]);
}

static std::string get_attachment_type(const simdjson::dom::element& json){
    return std::string(json["object"]["message"]["attachments"].at(0)["type"]);
}

static std::string get_attachments_count(const simdjson::dom::element& json){
    return std::to_string(json["object"]["message"]["attachments"].get_array().size());
}

std::string vk::reader::reader::message(){
    std::string res = _data.message;

    for (const auto& updates : _json["updates"].get_array()){
        if (has_reply(updates))
            res.insert(0, "{reply: " + get_reply_text(updates) + "} ");

        if (has_attachments(updates))
            res.insert(0, "{" + get_attachment_type(updates) + ": " + get_attachments_count(updates) + "} ");
    }

    return res;
}

std::string vk::reader::reader::from(){
    return (_data.from_id > 0 ? _api.user_get(_data.from_id) : _api.group_get(_data.from_id));
}

std::string vk::reader::reader::time(){
    time_t t;
    ::time(&t);

    tm* tme = localtime(&t);

    return std::to_string(tme->tm_hour) + ':' + std::to_string(tme->tm_min);
}

void vk::reader::reader::run(){
    std::cout << "Started" << std::endl;

    while(true){
        _json = _parser.parse(_lp.listen());

        if (_json["updates"].get_array().size() != 0){
            for (const auto& updates : _json["updates"].get_array()){
                _data.message = updates["object"]["message"]["text"].get_c_str();
                _data.peer_id = updates["object"]["message"]["peer_id"].get_int64();
                _data.from_id = updates["object"]["message"]["from_id"].get_int64();
            }

            std::cout << '(' << time() << ") [" << from() << "] $-> " << message() << std::endl;
        }
    }
}