//
// Created by innerviewer on 8/26/2023.
//

#ifndef BINARBOT_BINANCEMANAGER_H
#define BINARBOT_BINANCEMANAGER_H

#include <binarbot/CurlManager.h>

namespace Binarbot {
    class BinanceManager {
    public:
        using Ptr = std::shared_ptr<Binarbot::BinanceManager>;
        inline static const std::string exchangeInfoUrl = "https://api.binance.com/api/v3/exchangeInfo"; /* NOLINT */

    public:
        explicit BinanceManager(Binarbot::CurlManager::Ptr pCurlManager)
            : m_curlManager(std::move(pCurlManager))
        { }

    public:
        BB_NODISCARD void GetExchangeInfo() const;

    private:
        Binarbot::CurlManager::Ptr m_curlManager = nullptr;
    };
}

#endif //BINARBOT_BINANCEMANAGER_H
