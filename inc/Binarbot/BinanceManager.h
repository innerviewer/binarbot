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

        static const std::map<MarketDataEndpoints, std::string> m_apiUrls = {
        { MarketDataEndpoints::ServerTime, "https://api.binance.com/api/v3/time" },
        { MarketDataEndpoints::ExchangeInformation, "https://api.binance.com/api/v3/exchangeInfo" },
        { MarketDataEndpoints::OrderBook, "https://api.binance.com/api/v3/depth" },
        { MarketDataEndpoints::RecentTrades, "https://api.binance.com/api/v3/trades" },
        { MarketDataEndpoints::OldTrades, "https://api.binance.com/api/v3/historicalTrades" },
        { MarketDataEndpoints::AggregateTrades, "https://api.binance.com/api/v3/aggTrades" },
        { MarketDataEndpoints::KlineData, "https://api.binance.com/api/v3/klines" },
        { MarketDataEndpoints::CurrentAveragePrice, "https://api.binance.com/api/v3/avgPrice" },
        { MarketDataEndpoints::TickerPriceChangeStatistics, "https://api.binance.com/api/v3/ticker/24hr" },
        { MarketDataEndpoints::SymbolPriceTicker, "https://api.binance.com/api/v3/ticker/price" },
        { MarketDataEndpoints::SymbolOrderBookTicker, "https://api.binance.com/api/v3/ticker/bookTicker" },
        { MarketDataEndpoints::OpenInterest, "https://fapi.binance.com/fapi/v1/openInterest" },
        { MarketDataEndpoints::OpenInterestStatistics, "https://fapi.binance.com/fapi/v1/openInterestStat" }
    };

    class BinanceManager {
    public:
        using Ptr = std::shared_ptr<Binarbot::BinanceManager>;

    public:
        explicit BinanceManager(Binarbot::CurlManager::Ptr pCurlManager)
            : m_curlManager(std::move(pCurlManager)) 
			{ }

    public:
        SR_NODISCARD std::vector<Candle> GetCandleData(const std::string& symbol, const std::string& interval, uint16_t limit) const;
        SR_NODISCARD uint64_t GetServerTime() const;

    private:
        SR_NODISCARD static std::string ComposeRequest(const std::string& baseUrl, const std::vector<std::string>& params);

    private:
        Binarbot::CurlManager::Ptr m_curlManager = nullptr;
    };
}

#endif //BINARBOT_BINANCEMANAGER_H
