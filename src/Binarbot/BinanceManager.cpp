//
// Created by innerviewer on 8/26/2023.
//

#include <Binarbot/BinanceManager.h>
#include <Binarbot/Types/Candle.h>
#include <nlohmann/json.hpp>

namespace Binarbot {
    /*void BinanceManager::GetExchangeInfo() const {
        Binarbot::Response response = m_curlManager->PerformUrl(exchangeInfoUrl);

        if (response.second != CURLE_OK) {
            SR_ERROR("BinanceManager::GetExchangeInfo() : cURL request failed! Error: "
                     + std::string(curl_easy_strerror(response.second)));
            return;
        }

        nlohmann::json response_json = nlohmann::json::parse(response.first, nullptr, false);
        if (!response_json.is_object()) {
            SR_ERROR("BinanceManager::GetExchangeInfo() : Failed to parse JSON response!");
            return;
        }

        for (const auto& symbol : response_json["symbols"]) {
            if (symbol["status"].get<std::string>() == "TRADING") {
                std::cout << symbol["symbol"].get<std::string>() << " IS TRADABLE "<<  std::endl;
            }
            else {
                std::cout << symbol["symbol"].get<std::string>() << " IS NOT TRADABLE "<<  std::endl;
            }
        }
    }*/

    /*void BinanceManager::GetPricesInfo() const {
        Binarbot::Response response = m_curlManager->PerformUrl(pricesInfoUrl);

        if (response.second != CURLE_OK) {
            SR_ERROR("BinanceManager::GetPricesInfo() : cURL request failed! Error: "
                     + std::string(curl_easy_strerror(response.second)));
            return;
        }

        nlohmann::json response_json = nlohmann::json::parse(response.first, nullptr, false);
        if (!response_json.is_object()) {
            SR_ERROR("BinanceManager::GetPricesInfo() : Failed to parse JSON response!");
            return;
        }

        for (const auto& entry : response_json) {
            std::string symbol = entry["symbol"];
            std::string priceStr = entry["price"];
            double price = std::stod(priceStr); /// Convert string to double.
            std::cout << symbol << ": " << price << std::endl;
        }
    }*/

    std::vector<Candle> BinanceManager::GetCandleData(const std::string& symbol, const std::string& interval, uint16_t limit) const {
        std::vector<std::string> params = { "symbol=" + symbol,"interval=" + interval,"limit=" + std::to_string(limit) };
        std::string candleDataUrl = m_apiUrls.at(MarketDataEndpoints::KlineData);

        auto&& request = ComposeRequest(candleDataUrl, params);
        auto&& response = m_curlManager->PerformUrl(request);

        auto&& data = nlohmann::json::parse(response, nullptr, false);

        std::vector<Candle> candles;
        candles.reserve(limit);

        for (auto&& candleData : data) {
            Candle candle;
            candle.Initialize(candleData);
            if (candle.IsValid()) {
                candles.emplace_back(candle);
            }
        }
        return candles;
    }

    uint64_t BinanceManager::GetServerTime() const {
        auto&& response = m_curlManager->PerformUrl(m_apiUrls.at(MarketDataEndpoints::ServerTime));

        auto&& data = nlohmann::json::parse(response, nullptr, false);
        return data["serverTime"].get<uint64_t>();
    }

    std::string BinanceManager::ComposeRequest(const std::string& baseUrl, const std::vector<std::string>& params) {
        if (params.empty()) {
            return baseUrl;
        }

        std::string result = baseUrl;
        for (auto&& pIt = params.begin(); pIt != params.end(); ++pIt) {
            if (pIt == params.begin()) {
                result += "?";
            }
            else {
                result += "&";
            }

            result += *pIt;
        }

        return result;
    }
}