#include "network.hpp"

#include <sstream>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <fmt/format.h>

static std::string gen_params(const std::vector<vk::_param_type>& params){
    std::string res;

    for (const auto& [key, value] : params)
        res.append(fmt::format("{}={}&", key, value));

    return res;
}

std::string vk::request(std::string_view url, const std::vector<vk::_param_type>& parameters){
    std::stringstream res;
    curlpp::Easy curl;

    curl.setOpt(curlpp::Options::Url(std::string(url.data()) + gen_params(parameters)));
    curl.setOpt(curlpp::Options::WriteStream(&res));
    curl.perform();

    return res.str();
}
