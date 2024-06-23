//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_CURLMANAGER_H
#define BINARBOT_CURLMANAGER_H

#include <Utils/stdInclude.h>
#include <curl/curl.h>

namespace Binarbot {
    using Pairs = std::vector<std::string>;
    using Response = std::pair<std::string, CURLcode>;

    struct TradeInfo {
        Pairs pairs;
    };

    class CurlManager {
    public:
        using Ptr = std::shared_ptr<Binarbot::CurlManager>;

    public:
        void Init();
        void DeInit();

    public:
        SR_NODISCARD CURL* GetHandle() const { return m_curl; }

        SR_NODISCARD Response PerformUrl(const std::string& url);

    public:
        void DisableCertificate();

    private:
        CURL* m_curl = nullptr;

        std::string m_url;

        TradeInfo m_tradeInfo;
    };
}

#endif //BINARBOT_CURLMANAGER_H
