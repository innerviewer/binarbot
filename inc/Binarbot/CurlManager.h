//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_CURLMANAGER_H
#define BINARBOT_CURLMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/stdInclude.h>
#include <curl/curl.h>

namespace Binarbot {
    using Pairs = std::vector<std::string>;

    struct TradeInfo {
        Pairs pairs;
    };

    class CurlManager : public SR_UTILS_NS::Singleton<CurlManager> {
        SR_REGISTER_SINGLETON(CurlManager);
    public:
        void Init();
        void DeInit();

    public:
        SR_NODISCARD CURL* GetHandle() const { return m_curl; }

        static size_t WriteCallback(char* pData, size_t size, size_t nmemb, std::string* pWriteData);
        SR_NODISCARD std::string PerformUrl(const std::string& url);

    public:
        void DisableCertificate();

    private:
        CURL* m_curl = nullptr;

        std::string m_url;

        TradeInfo m_tradeInfo;
    };
}

#endif //BINARBOT_CURLMANAGER_H
