#ifndef LONGPOLL_API
#define LONGPOLL_API

#include "lib/network/network.hpp"
#include "lib/api/vk_api.hpp"
#include "apis_data.hpp"

namespace vk{
    namespace api{
        class longpoll_api{
        private:
            vk::api::vk_api _api;
            vk::api::longpoll_data _conf;
        public:
            std::string listen();
        };
    }
}

#endif //LONGPOLL_API