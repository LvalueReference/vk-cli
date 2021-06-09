#include "network.hpp"
#include <sstream>

static std::string gen_params(const std::vector<vk::network::param>& params){
    std::string res;

    for (const auto& [key, value] : params)
        /// Вот чтобы этого не очень красивого кода не было, нужен format
        /// Можно так:
        ///     res += format("{}={}&", key, value);
        res += key + '=' + value + '&';

    return res;
}

std::string vk::network::request(std::string_view url, const std::vector<vk::network::param>& params){
    std::stringstream res;

    _curl.setOpt(curlpp::Options::Url(std::string(url.data()) + gen_params(params)));
    _curl.setOpt(curlpp::Options::WriteStream(&res));
    _curl.perform();

    return res.str();
}