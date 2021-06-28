#include "lib/api/vk_api.hpp"

std::string vk::api::vk_api::method(std::string_view meth) const {
    return "https://api.vk.com/method/" + std::string(meth.data()) + '?';
}

std::vector<vk::network::param> vk::api::vk_api::params(std::vector<vk::network::param> prms){
    prms.push_back({"access_token", _conf.token});
    prms.push_back({"v",            _conf.api_v});

    return prms;
}

vk::api::vk_api::vk_api() : _json(_parser.load("../config/config.json")){
    _conf = vk::api::vk_api_data{
            std::string(_json["TOKEN"]),
            std::string(_json["ADMIN"]),
            std::string(_json["GROUP"]),
            std::string(_json["API_V"])
    };
}

vk::api::longpoll_data vk::api::vk_api::get_lp_server() {
    _json = _parser.parse(_curl.request(method("groups.getLongPollServer"), params({
        {"group_id", _conf.group}
    })));

    return {
        std::string(_json["response"]["server"]),
        std::string(_json["response"]["key"]),
        std::string(_json["response"]["ts"])
    };
}

std::string vk::api::vk_api::user_get(int user_ids) {
    _json = _parser.parse(_curl.request(method("users.get"), params({
            {"user_ids", std::to_string(user_ids)}
    })));

    return std::string(_json["response"].at(0)["first_name"]) + " " + std::string(_json["response"].at(0)["last_name"]);
}

std::string vk::api::vk_api::group_get(int group_ids) {
    _json = _parser.parse(_curl.request(method("groups.getById"), params({
        {"group_ids", std::to_string(std::abs(group_ids))}
    })));

    return std::string(_json["response"].at(0)["name"]);
}