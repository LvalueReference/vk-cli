#include "lib/api/longpoll_api.hpp"

std::string vk::longpoll_api::listen() {
    _conf = _api.get_lp_server();

    std::string res = _curl.request(_conf.server + '?', {
            {"act",  "a_check"},
            {"key",  _conf.key},
            {"ts",   _conf.ts},
            {"wait", "40"}
    });

    return res;
}