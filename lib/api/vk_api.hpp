#ifndef VK_API_HPP
#define VK_API_HPP

#include "lib/network/network.hpp"
#include "lib/simdjson/simdjson.h"

namespace vk{
    struct vk_api{
    private:
        vk::network _curl;
        std::string _token, _admin, _group, _api_v;

        simdjson::dom::parser _parser;
        simdjson::dom::object _json;
    public:
        vk_api();

        std::string method(std::string_view meth) const;
        std::vector<vk::network::param> params(const std::vector<vk::network::param>& prms) const;

        void get_lp_server(std::string& server, std::string& key, std::string& ts);
        std::string user_get(int user_ids);
        std::string group_get(int group_ids);
    };
}

#endif //VK_API_HPP