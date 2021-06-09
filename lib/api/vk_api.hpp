#ifndef VK_API_HPP
#define VK_API_HPP

#include "lib/network/network.hpp"
#include "lib/simdjson/simdjson.h"

namespace vk{
    /// Почему структура, а не класс?
    struct vk_api{
    private:
        vk::network _curl;
        /// Это можно обернуть в структуру
        /// например
        /// struct config_data {
        ///     token,
        ///     admin,
        ///     group,
        ///     api_v
        /// }
        ///
        /// И хранить одно поле структурой вместо 4-х строк
        std::string _token, _admin, _group, _api_v;

        /// Это не нужно как поле класса
        simdjson::dom::parser _parser;
        /// И это тоже
        simdjson::dom::object _json;
    public:
        vk_api();

        std::string method(std::string_view meth) const;
        std::vector<vk::network::param> params(const std::vector<vk::network::param>& prms) const;
        /// Здесь можно не принимать параметры а вернуть структуру
        /// struct lp_data {
        ///     server,
        ///     key,
        ///     ts
        /// }
        ///
        /// И ты пишешь
        /// void get_lp_server() {
        ///     // ...
        ///     return {server, key, ts}
        /// }
        void get_lp_server(std::string& server, std::string& key, std::string& ts);
        std::string user_get(int user_ids);
        std::string group_get(int group_ids);
    };
}

#endif //VK_API_HPP