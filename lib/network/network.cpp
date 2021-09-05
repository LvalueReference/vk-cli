#include "network.hpp"
#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"

#include <sstream>
#include <fmt/format.h>

static std::string gen_params(const vk::param_type& params){
    std::string result;

    for (const auto& [key, value] : params)
        result.append(fmt::format("{}={}&", key, value));

    return result;
}

std::string vk::request(std::string_view url, const vk::param_type& parameters){
    std::stringstream result;
    curlpp::Easy curl;

    curl.setOpt(curlpp::Options::Url(std::string(url.data(), url.size()) + gen_params(parameters)));
    curl.setOpt(curlpp::Options::WriteStream(&result));
    curl.perform();

    return result.str();
}
