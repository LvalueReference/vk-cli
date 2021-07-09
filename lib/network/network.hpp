#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <string_view>
#include <vector>

namespace vk{
	using _param_type = std::pair<std::string, std::string>;
    std::string request(std::string_view url, const std::vector<_param_type>& parameters);
}

#endif //NETWORK_HPP

