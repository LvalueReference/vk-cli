#ifndef LONGPOLL_API
#define LONGPOLL_API

#include "lib/network/network.hpp"
#include "lib/api/vk_api.hpp"

namespace vk{
    /// Если у тебя класс с одной функцией, задумайся, нужен ли тебе класс или функция
    struct longpoll_api{
    private:
        vk::network _curl;
        vk::vk_api _api;

        std::string _server, _key, _ts;
    public:
        /// Зачем принимать строку по ссылке, если можно создать её внутри функции и вернуть?
        void listen(std::string& res);
    };
}

#endif //LONGPOLL_API