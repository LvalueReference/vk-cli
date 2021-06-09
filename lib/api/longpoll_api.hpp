#ifndef LONGPOLL_API
#define LONGPOLL_API

#include "lib/network/network.hpp"
#include "lib/api/vk_api.hpp"

namespace vk{
    struct longpoll_api{
    private:
        vk::network _curl;
        vk::vk_api _api;

        std::string _server, _key, _ts;
    public:
        void listen(std::string& res);
    };
}

#endif //LONGPOLL_API