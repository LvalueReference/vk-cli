#include "lib/api/longpoll_api.hpp"

std::string vk::longpoll_api::listen(){
    _config = _api.get_lp_server();

    return vk::request(_config.server + '?', {{"act",  "a_check"},
                                              {"key",  _config.key},
                                              {"ts",   _config.ts},
                                              {"wait", "40"}});
}