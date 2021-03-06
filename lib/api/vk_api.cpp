#include "lib/api/vk_api.hpp"
#include "fmt/format.h"

std::string vk::vk_api::method(std::string_view method_name) const{
    return fmt::format("https://api.vk.com/method/{}?", std::string(method_name));
}

vk::params_t&& vk::vk_api::params(vk::params_t&& parameter_pack) const{
    parameter_pack.emplace_back(std::make_pair("access_token", _config.token));
    parameter_pack.emplace_back(std::make_pair("v", _config.api_v));

    return std::move(parameter_pack);
}

vk::vk_api::vk_api(){
    simdjson::dom::parser parser;
    auto json = parser.load("../config/config.json");

    _config = vk::vk_api_data{std::string(json["TOKEN"]),
                              std::string(json["GROUP"]),
                              std::string(json["API_V"])};
}

vk::longpoll_data vk::vk_api::get_lp_server() const{
    simdjson::dom::parser parser;
    auto json = parser.parse(vk::request(method("groups.getLongPollServer"),
                                         params({{"group_id", _config.group}})));

    return {std::string(json["response"]["server"]),
            std::string(json["response"]["key"]),
            std::string(json["response"]["ts"])};
}

std::string vk::vk_api::user_get(std::int32_t user_ids) const{
    simdjson::dom::parser parser;
    auto json = parser.parse(vk::request(method("users.get"),
                                         params({{"user_ids", std::to_string(user_ids)}})));

    return fmt::format("{} {}", std::string(json["response"].at(0)["first_name"]),
                                std::string(json["response"].at(0)["last_name"]));
}

std::string vk::vk_api::group_get(std::int32_t group_ids) const{
    simdjson::dom::parser parser;
    auto json = parser.parse(vk::request(method("groups.getById"),
                                         params({{"group_ids", std::to_string(std::abs(group_ids))}})));

    return std::string(json["response"].at(0)["name"]);
}

std::string vk::vk_api::get_chat_name(std::int32_t peer_id) const{
    simdjson::dom::parser parser;
    auto json = parser.parse(vk::request(method("messages.getConversationsById"),
                                         params({{"peer_ids", std::to_string(peer_id)},
                                                 {"group_id", _config.group}})));

    return std::string(json["response"]["items"].get_array().at(0)["chat_settings"]["title"]);
}
