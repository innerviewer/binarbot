//
// Created by innerviewer on 8/26/2023.
//

#include <Binarbot/CurlManager.h>
#include <Utils/Debug.h>

namespace Binarbot {
    void CurlManager::Init() {
        curl_global_init(CURL_GLOBAL_DEFAULT);

        m_curl = curl_easy_init();

        if (!m_curl) {
            SR_ERROR("CurlManager::Init() : failed to initialize Curl!");
        }
    }

    void CurlManager::DeInit() {
        curl_easy_cleanup(m_curl);
        curl_global_cleanup();
    }

    void CurlManager::DisableCertificate() {
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    size_t CurlManager::WriteCallback(char* pData, size_t size, size_t nmemb, std::string* pWriteData) {
        if (!pWriteData) {
            SR_ERROR("CurlManager::WriteCallback() : pWriteData is nullptr!");
            return -1;
        }

        pWriteData->append(pData, size * nmemb);
        return size * nmemb;
    }

    Response CurlManager::PerformUrl(const std::string& url) {
        std::string responseData;

        curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &responseData);

        CURLcode res = curl_easy_perform(m_curl);

        if (res != CURLE_OK) {
            SR_ERROR("CurlManager::PerformUrl() : cURL request failed! Error: " + std::string(curl_easy_strerror(res)));
            return { };
        }

        return Binarbot::Response(responseData, res);
    }

}
