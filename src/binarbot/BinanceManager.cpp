//
// Created by innerviewer on 8/26/2023.
//

#include <binarbot/BinanceManager.h>

namespace Binarbot {
    void BinanceManager::GetExchangeInfo() const {
        Binarbot::Response response = m_curlManager->PerformUrl(exchangeInfoUrl);

        if (response.second != CURLE_OK) {
            BB_ERROR("BinanceManager::GetExchangeInfo() : cURL request failed! Error: "
                     + std::string(curl_easy_strerror(response.second)));
            return;
        }

        // Обработка JSON-ответа.
        nlohmann::json response_json = nlohmann::json::parse(response.first);
        for (const auto &symbol : response_json["symbols"]) {
            std::cout << symbol["symbol"].get<std::string>() << std::endl;

        }
    }
}