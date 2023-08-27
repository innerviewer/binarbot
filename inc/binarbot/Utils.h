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

namespace Binarbot {
    // Callback-функция для записи данных, полученных от сервера, в переменную.
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    template<typename T> uint64_t CalculateHash(const T& value) {
        static std::hash<T> h;
        return h(value);
    }

    template<typename T> uint64_t HashCombine(const T& value, uint64_t hash = 0) {
        return hash ^ CalculateHash<T>(value) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    static uint64_t CombineTwoHashes(uint64_t hash1, uint64_t hash2) {
        return hash2 ^ hash1 + 0x9e3779b9 + (hash2 << 6) + (hash2 >> 2);
    }
}

#define BB_NODISCARD [[nodiscard]]
#define BB_INLINE inline
#define BB_ID_INVALID -1
#define BB_INLINE_STATIC inline static
#define BB_ERROR(msg) std::cerr << msg << std::endl;
#define BB_HASH_STR(x) (Binarbot::CalculateHash<std::string>(x))
#define BB_MACRO_CONCAT_UTIL(a, b) a ## b
#define BB_MACRO_CONCAT(a, b) BB_MACRO_CONCAT_UTIL(a, b)

#endif //BINARBOT_UTILS_H
