#ifndef VK_API_HPP
#define VK_API_HPP

#include "lib/network/network.hpp"
#include "lib/simdjson/simdjson.h"
#include "apis_data.hpp"

#include <string>
#include <vector>

namespace vk{
	class vk_api {
	private:
		vk::vk_api_data _conf;

		std::string method(std::string_view meth) const;
		std::vector<vk::_param_type> params(std::vector<vk::_param_type> parameters);
	public:
		vk_api();

		vk::longpoll_data get_lp_server();
		std::string user_get(int user_ids);
		std::string group_get(int group_ids);
		std::string get_chat_name(int peer_id);
	};
}

#endif //VK_API_HPP
