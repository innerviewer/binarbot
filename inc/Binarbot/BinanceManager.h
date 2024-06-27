//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_BINANCEMANAGER_H
#define BINARBOT_BINANCEMANAGER_H

#include <Binarbot/CurlManager.h>
#include <Binarbot/Types/Candle.h>
#include <Binarbot/Types/CandleInterval.h>

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

    class BinanceManager : public SR_UTILS_NS::Singleton<BinanceManager> {
        SR_REGISTER_SINGLETON(BinanceManager);
        using Super = SR_UTILS_NS::Singleton<BinanceManager>;
    protected:
        BinanceManager();

    public:
        SR_NODISCARD std::vector<Candle> GetCandleData(const std::string& symbol, CandleInterval interval, uint16_t limit) const;
        SR_NODISCARD std::vector<Candle> GetCandleData(const std::string& symbol, CandleInterval interval,
                                                            uint16_t limit, uint64_t startTime, uint64_t endTime) const;
        SR_NODISCARD std::vector<Candle> GetCandleData(const std::string& symbol, CandleInterval interval,
                                                            uint16_t limit, uint64_t startTime) const;

        SR_NODISCARD uint64_t GetServerTime() const;

    private:
        SR_NODISCARD static std::string ComposeRequest(const std::string& baseUrl, const std::vector<std::string>& params);
    };
}

#endif //BINARBOT_BINANCEMANAGER_H
