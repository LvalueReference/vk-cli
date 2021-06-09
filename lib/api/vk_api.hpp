#ifndef VK_API_HPP
#define VK_API_HPP

#include "lib/network/network.hpp"
#include "lib/simdjson/simdjson.h"
#include "lib/config/config.hpp"

#include <string>
#include <vector>

namespace vk{
    class vk_api{
    private:
        vk::network _curl;

        simdjson::dom::parser _parser;
        simdjson::dom::object _json;

        vk::vk_api_data _conf;
    public:
        vk_api();

        std::string method(std::string_view meth) const;
        std::vector<vk::network::param> params(const std::vector<vk::network::param>& prms) const;

        vk::longpoll_data get_lp_server();
        std::string user_get(int user_ids);
        std::string group_get(int group_ids);
    };
}

#endif //VK_API_HPP
