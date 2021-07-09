#ifndef READER_DATA_HPP
#define READER_DATA_HPP

namespace reader{
    struct reader_data{
        std::string  message;
        std::int64_t peer_id;
        std::int64_t from_id;
    };
}

#endif //READER_DATA_HPP