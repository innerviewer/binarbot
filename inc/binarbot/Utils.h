//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_UTILS_H
#define BINARBOT_UTILS_H

#include <iostream>
#include <string>
#include <memory>

#include <openssl/ssl.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#define BB_NODISCARD [[nodiscard]]
#define BB_ERROR(msg) std::cerr << msg << std::endl;

namespace Binarbot {
    // Callback-функция для записи данных, полученных от сервера, в переменную.
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
}

#endif //BINARBOT_UTILS_H
