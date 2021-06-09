#include "config.hpp"
#include <string>

struct vk::vk_api_data{
    std::string token;
    std::string admin;
    std::string group;
    std::string api_v;
};

struct vk::longpoll_data{
    std::string server;
    std::string key;
    std::string ts;
};