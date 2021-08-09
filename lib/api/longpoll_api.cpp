#include "lib/api/longpoll_api.hpp"

std::string vk::longpoll_api::listen(){
    _conf = _api.get_lp_server();

    return vk::request(_conf.server + '?', {
            {"act",  "a_check"},
            {"key",  _conf.key},
            {"ts",   _conf.ts},
            {"wait", "40"}
    });
}