#include "lib/api/vk_api.hpp"

std::string vk::vk_api::method(std::string_view meth) const {
    return "https://api.vk.com/method/" + std::string(meth.data()) + '?';
}

std::vector<vk::network::param> vk::vk_api::params(const std::vector<vk::network::param>& prms) const {
    std::vector<vk::network::param> res = {
            {"access_token", _token},
            {"v",            _api_v}
    };

    for (const auto& i : prms)
        res.push_back(i);

    return res;
}

vk::vk_api::vk_api() : _json(_parser.load("../lib/config/config.json")){
    _token = _json["TOKEN"].get_c_str();
    _admin = _json["ADMIN"].get_c_str();
    _group = _json["GROUP"].get_c_str();
    _api_v = _json["API_V"].get_c_str();
}

void vk::vk_api::get_lp_server(std::string& server, std::string& key, std::string& ts) {
    std::string req = _curl.request(method("groups.getLongPollServer"), params({
            {"group_id", _group}
    }));

    _json = _parser.parse(req);

    server = _json["response"]["server"];
    key = _json["response"]["key"];
    ts = _json["response"]["ts"];
}

std::string vk::vk_api::user_get(int user_ids){
    std::string req = _curl.request(method("users.get"), params({
            {"user_ids", std::to_string(user_ids)}
    }));

    _json = _parser.parse(req);

    return std::string(_json["response"].at(0)["first_name"]) + " " + std::string(_json["response"].at(0)["last_name"]);
}

std::string vk::vk_api::group_get(int group_ids) {
    std::string req = _curl.request(method("groups.getById"), params({
            {"group_ids", std::to_string(std::abs(group_ids))}
    }));

    _json = _parser.parse(req);

    return std::string(_json["response"].at(0)["name"]);
}