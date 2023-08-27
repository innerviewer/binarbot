//
// Created by innerviewer on 8/26/2023.
//

#include <binarbot/CurlManager.h>

namespace Binarbot {
    void CurlManager::Init() {
        /// Инициализация библиотек.
        curl_global_init(CURL_GLOBAL_DEFAULT);

        /// Создание объекта CURL.
        m_curl = curl_easy_init();

        if (!m_curl) {
            BB_ERROR("CurlManager::Init() : failed to initialize Curl!")
        }

        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Binarbot::WriteCallback);
    }

    void CurlManager::DeInit() {
        /// Освобождение ресурсов CURL.
        curl_easy_cleanup(m_curl);

        /// Освобождение глобальных ресурсов CURL.
        curl_global_cleanup();
    }

    void CurlManager::DisableCertificate() {
        /// Отключение проверки SSL-сертификата.
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    Response CurlManager::PerformUrl(const std::string& url) {
        std::string response_data;

        /// Установка опций CURL.
        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response_data);

        /// Выполнение запроса.
        CURLcode res = curl_easy_perform(m_curl);

        return Binarbot::Response(response_data, res);
    }
}
