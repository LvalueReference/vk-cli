#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <string_view>
#include <vector>

namespace vk{
    using params_t = std::vector<std::pair<std::string, std::string>>;

    std::string request(std::string_view url, params_t&& parameter_pack);
}

#endif //NETWORK_HPP

