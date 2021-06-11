#ifndef READER_DATA_HPP
#define READER_DATA_HPP

#include <string>

namespace vk{
    struct reader_data{
        std::string message;
        int peer_id;
        int from_id;
    };
}

#endif //READER_DATA_HPP