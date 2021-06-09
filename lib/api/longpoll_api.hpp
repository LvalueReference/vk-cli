#ifndef LONGPOLL_API
#define LONGPOLL_API

#include "lib/network/network.hpp"
#include "lib/api/vk_api.hpp"
#include "lib/config/config.hpp"

namespace vk{
    class longpoll_api{
    private:
        vk::network _curl;
        vk::vk_api _api;

        vk::longpoll_data _conf;
    public:
        std::string listen();
    };
}

#endif //LONGPOLL_API