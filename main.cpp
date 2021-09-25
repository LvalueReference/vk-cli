#include <iostream>
#include <fstream>

#include "fmt/format.h"
#include "simdjson.h"
#include "lib/api/longpoll_api.hpp"
#include "reader/message.hpp"
#include "reader/color.hpp"

using reader::color;

std::string colorize_message_template(){
    std::string_view msg_template = "┌[{}{{}}{}] ({{}}) [{{}}]\n└[message]-> {}{{}}{}";

    return fmt::format(msg_template, fg(color::BOLD_GREEN), fg(color::CLEAR), fg(color::BOLD_YELLOW), fg(color::CLEAR));
}

template <class T>
std::string make_message(const T& from, const T& time, const T& chat_name, const T& text){
    return fmt::format(colorize_message_template(), from, time, chat_name, text);
}

template <class T>
std::string make_log_message(const T& from, const T& time, const T& chat_name, const T& text){
    std::string_view msg_template = "┌[{}] ({}) [{}]\n└[message]-> {}";

    return fmt::format(msg_template, from, time, chat_name, text);
}

int main(){
#ifdef _WIN32
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    vk::longpoll_api longpoll;
    reader::message message;

    simdjson::dom::element json;
    simdjson::dom::parser parser;

    std::ofstream logs("../logs.txt", std::ios::out | std::ios::app);

    std::cout << fmt::format("==========[ {}STARTED{} ]==========", fg(color::BOLD_GREEN), fg(color::CLEAR))
              << std::endl;

    while (true){
        json = parser.parse(longpoll.listen());

        if (json["updates"].get_array().size() != 0){
            for (const auto& updates: json["updates"].get_array()){
                message = updates;

                std::cout << make_message(message.from(), message.current_time(), message.chat_name(),
                                          message.message_text()) << std::endl;

                try{
                    logs << make_log_message(message.from(), message.current_time(), message.chat_name(),
                                             message.message_text()) << std::endl;
                } catch(std::ofstream::failure& exc){
                    std::cerr << "Ошибка записи в лог-файл: " << exc.what() << std::endl;
                }
            }
        }
    }
}