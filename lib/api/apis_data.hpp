#ifndef APIS_DATA_HPP
#define APIS_DATA_HPP

namespace vk{
    struct vk_api_data{
        std::string token;
        std::string admin;
        std::string group;
        std::string api_v;
    };

    struct longpoll_data{
        std::string server;
        std::string key;
        std::string ts;
    };
}

#endif //APIS_DATA_HPP