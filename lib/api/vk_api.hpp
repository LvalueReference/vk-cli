#ifndef VK_API_HPP
#define VK_API_HPP

#include "lib/network/network.hpp"
#include "lib/simdjson/simdjson.h"
#include "apis_data.hpp"

#include <string>
#include <vector>

namespace vk{
    class vk_api{
    private:
        vk::vk_api_data _conf;

        std::string method(std::string_view meth) const;
        vk::param_type params(vk::param_type parameters) const;
    public:
        vk_api();

        vk::longpoll_data get_lp_server() const;
        std::string user_get(std::int32_t user_ids) const;
        std::string group_get(std::int32_t group_ids) const;
        std::string get_chat_name(std::int32_t peer_id) const;
    };
}

#endif //VK_API_HPP
