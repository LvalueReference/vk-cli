#include "lib/api/vk_api.hpp"
#include <fmt/format.h>

std::string vk::vk_api::method(std::string_view meth) const {
    return fmt::format("https://api.vk.com/method/{}?", std::string(meth.data()));
}

std::vector<vk::_param_type> vk::vk_api::params(std::vector<vk::_param_type> parameters){
    parameters.push_back({"access_token", _conf.token});
    parameters.push_back({"v",            _conf.api_v});

    return parameters;
}

vk::vk_api::vk_api(){
	simdjson::dom::parser parser;
	simdjson::dom::element json = parser.load("../config/my_config.json");

    _conf = vk::vk_api_data{
            std::string(json["TOKEN"]),
            std::string(json["ADMIN"]),
            std::string(json["GROUP"]),
            std::string(json["API_V"])
    };
}

vk::longpoll_data vk::vk_api::get_lp_server() {
	simdjson::dom::parser parser;
    simdjson::dom::element json = parser.parse(vk::request(method("groups.getLongPollServer"),
														   params({{"group_id", _conf.group}})));

    return {
        std::string(json["response"]["server"]),
        std::string(json["response"]["key"]),
        std::string(json["response"]["ts"])
    };
}

std::string vk::vk_api::user_get(int user_ids) {
	simdjson::dom::parser parser;
	simdjson::dom::element json = parser.parse(vk::request(method("users.get"),
														   params({{"user_ids", std::to_string(user_ids)}})));

    return fmt::format("{} {}", std::string(json["response"].at(0)["first_name"]),
                                std::string(json["response"].at(0)["last_name"]));
}

std::string vk::vk_api::group_get(int group_ids) {
	simdjson::dom::parser parser;
	simdjson::dom::element json = parser.parse(vk::request(method("groups.getById"),
														   params({{"group_ids", std::to_string(std::abs(group_ids))}})));

    return std::string(json["response"].at(0)["name"]);
}

std::string vk::vk_api::get_chat_name(int peer_id) {
	simdjson::dom::parser parser;
	simdjson::dom::element json = parser.parse(vk::request(method("messages.getConversationsById"),
														   params({{"peer_ids", std::to_string(peer_id)},
																   {"group_id", _conf.group}})));

    return std::string(json["response"]["items"].get_array().at(0)["chat_settings"]["title"]);
}
