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
        for (const auto& symbol : response_json["symbols"]) {
            if (symbol["status"].get<std::string>() == "TRADING") {
                std::cout << symbol["symbol"].get<std::string>() << " IS TRADABLE "<<  std::endl;
            }
            else {
                std::cout << symbol["symbol"].get<std::string>() << " IS NOT TRADABLE "<<  std::endl;
            }
        }
    }

    void BinanceManager::GetPricesInfo() const {
        Binarbot::Response response = m_curlManager->PerformUrl(pricesInfoUrl);

        if (response.second != CURLE_OK) {
            BB_ERROR("BinanceManager::GetPricesInfo() : cURL request failed! Error: "
                     + std::string(curl_easy_strerror(response.second)));
            return;
        }

        // Обработка JSON-ответа.
        try {
            nlohmann::json response_json = nlohmann::json::parse(response.first);
            for (const auto& entry : response_json) {
                std::string symbol = entry["symbol"];
                std::string priceStr = entry["price"];
                double price = std::stod(priceStr); /// Convert string to double.
                std::cout << symbol << ": " << price << std::endl;
            }
        }
        catch (nlohmann::detail::exception& exp) {
            BB_ERROR("BinanceManager::GetPricesInfo() : " + std::string(exp.what()));
        }
        catch (...) {
            BB_ERROR("BinanceManager::GetPricesInfo() : unknown exception!")
        }

    }
}