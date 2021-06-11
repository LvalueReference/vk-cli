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

        simdjson::dom::parser _parser;
        simdjson::dom::element _json;

        std::string _message, _response;
        int _peer_id, _from_id;

        std::string message();
        std::string from();
    public:
        void run();
    };
}

#endif //READER_HPP
