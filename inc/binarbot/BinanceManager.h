//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_BINANCEMANAGER_H
#define BINARBOT_BINANCEMANAGER_H

#include <binarbot/CurlManager.h>
#include <binarbot/Enumerations.h>

namespace Binarbot {
    BB_ENUM_NS_CLASS_T(TradableStatus, uint8_t,
        Tradable,
        NotTradable
    );

    class BinanceManager {
    public:
        using Ptr = std::shared_ptr<Binarbot::BinanceManager>;
        inline static const std::string exchangeInfoUrl = "https://api.binance.com/api/v3/exchangeInfo"; /* NOLINT */
        inline static const std::string pricesInfoUrl = "https://api.binance.com/api/v3/ticker/price"; /* NOLINT */

    public:
        explicit BinanceManager(Binarbot::CurlManager::Ptr pCurlManager)
            : m_curlManager(std::move(pCurlManager))
        { }

    public:
        BB_NODISCARD void GetExchangeInfo() const;
        BB_NODISCARD void GetPricesInfo() const;

    private:
        Binarbot::CurlManager::Ptr m_curlManager = nullptr;
    };
}

#endif //BINARBOT_BINANCEMANAGER_H
