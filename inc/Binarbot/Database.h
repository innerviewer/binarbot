//
// Created by innerviewer on 2024-06-24.
//

#ifndef BINARBOT_DATABASE_H
#define BINARBOT_DATABASE_H

#include <Binarbot/Types/Candle.h>

namespace Binarbot {
    class CandleDatabase {
    public:
        void Append(const std::vector<Candle>& candles);
        void Append(const Candle& candle);

    private:
        bool m_isSorted = true;
        SR_UTILS_NS::Path m_databasePath;
        std::vector<Candle> m_candles;
    };
}

#endif //BINARBOT_DATABASE_H
