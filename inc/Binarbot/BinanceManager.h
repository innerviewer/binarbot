//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_BINANCEMANAGER_H
#define BINARBOT_BINANCEMANAGER_H

#include <Binarbot/CurlManager.h>
#include <Binarbot/Types/Candle.h>

#include <Utils/Common/Enumerations.h>

#include <nlohmann/json.hpp>

namespace Binarbot {
    SR_ENUM_NS_CLASS_T(TradableStatus, uint8_t,
        Tradable,
        NotTradable
    );

    SR_ENUM_NS_CLASS_T(MarketDataEndpoints, uint64_t,
        ServerTime, ExchangeInformation, OrderBook,
        RecentTrades, OldTrades, AggregateTrades,
        KlineData, CurrentAveragePrice, TickerPriceChangeStatistics,
        SymbolPriceTicker, SymbolOrderBookTicker, OpenInterest,
        OpenInterestStatistics
    );

    //static constexpr std::unordered_map
    //static constexpr std::string ApiUrls

    class BinanceManager {
    public:
        using Ptr = std::shared_ptr<Binarbot::BinanceManager>;
        inline static const std::string exchangeInfoUrl = "https://api.binance.com/api/v3/exchangeInfo"; /* NOLINT */
        inline static const std::string pricesInfoUrl = "https://api.binance.com/api/v3/ticker/price"; /* NOLINT */
        inline static const std::string candleDataUrl = "https://api.binance.com/api/v3/klines"; /* NOLINT */

    public:
        explicit BinanceManager(Binarbot::CurlManager::Ptr pCurlManager)
            : m_curlManager(std::move(pCurlManager))
        { }

    public:
        SR_NODISCARD std::vector<Candle> GetCandleData(const std::string& symbol, const std::string& interval, uint16_t limit) const;

    private:
        SR_NODISCARD static std::string ComposeRequest(const std::string& baseUrl, const std::vector<std::string>& params);

    private:
        Binarbot::CurlManager::Ptr m_curlManager = nullptr;
    };
}

#endif //BINARBOT_BINANCEMANAGER_H
