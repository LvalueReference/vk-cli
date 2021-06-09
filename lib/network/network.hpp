#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <string_view>
#include <vector>

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

namespace vk{
    class network{
    private:
        curlpp::Easy _curl;
    public:
        struct param{
            std::string key;
            std::string value;
        };

        std::string request(std::string_view url, const std::vector<param>& params);
    };
}

#endif //NETWORK_HPP

