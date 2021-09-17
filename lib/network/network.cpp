#include "network.hpp"
#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"

#include <sstream>
#include <numeric>

static std::string gen_parameters(vk::params_t&& parameters){
    return std::accumulate(parameters.begin(), parameters.end(), std::string(), [](std::string& out, const auto& pair) {
        if (out.empty()) { out.reserve(1024); }
        out += pair.first;
        out += "=";
        out += pair.second;
        out += "&";
        return out;
    });
}

std::string vk::request(std::string_view url, vk::params_t&& parameter_pack){
    std::stringstream result;
    curlpp::Easy curl;

    curl.setOpt(curlpp::Options::Url(std::string(url.data(), url.size()) + gen_parameters(std::move(parameter_pack))));
    curl.setOpt(curlpp::Options::WriteStream(&result));
    curl.perform();

    return result.str();
}
