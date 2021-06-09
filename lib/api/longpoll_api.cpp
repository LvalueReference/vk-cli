#include "lib/api/longpoll_api.hpp"

void vk::longpoll_api::listen(std::string &res) {
    _api.get_lp_server(_server, _key, _ts);

    res = _curl.request(_server + '?', {
            {"act", "a_check"},
            {"key", _key},
            {"ts",  _ts},
            {"wait", "40"}
    });
}