#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "simdjson/simdjson.h"
#include "lib/api/vk_api.hpp"
#include "lib/api/apis_data.hpp"
#include "reader/reader_data.hpp"

namespace vk{
    namespace reader{
        class message{
        private:
            simdjson::dom::object _json;
            vk::api::vk_api _api;
            vk::reader::reader_data _data;
        public:
            void init(const simdjson::dom::element& json);

            std::string msg();
            std::string from();
            std::string time();

            bool has_reply();
            bool has_attachments();
            bool has_attachments(const simdjson::dom::element& att);
            bool has_fwd();

            auto get_attachments();
            auto get_attachments(const simdjson::dom::element& att);
            auto get_reply();
            auto get_fwd();
            std::string get_reply_text();
            std::string get_reply_from();
            std::string get_attachment_type();
            std::string get_attachment_type(const simdjson::dom::element& att);
            //std::string get_attachments_count(const simdjson::dom::object& att);
        };
    }
}

#endif //MESSAGE_HPP