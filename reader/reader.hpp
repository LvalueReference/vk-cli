#ifndef READER_HPP
#define READER_HPP

#include "lib/api/vk_api.hpp"
#include "lib/api/longpoll_api.hpp"
#include "lib/network/network.hpp"
#include "simdjson/simdjson.h"

namespace vk{
    struct reader{
    private:
        vk::vk_api _api;
        vk::longpoll_api _lp;
        vk::network _curl;

        simdjson::dom::parser _parser;
        simdjson::dom::object _json;

        std::string _response, _message;
        int _peer_id, _from_id;

        void init();
        std::string message();
        std::string from();
    public:
        void run();
    };
}

#endif //READER_HPP