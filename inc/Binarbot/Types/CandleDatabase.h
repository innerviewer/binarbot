//
// Created by innerviewer on 2024-06-24.
//

#ifndef BINARBOT_CANDLE_DATABASE_H
#define BINARBOT_CANDLE_DATABASE_H

#include <Binarbot/Types/Candle.h>
#include <Utils/Types/SortedVector.h>
#include <Binarbot/Types/CandleInterval.h>

namespace Binarbot {
    SR_ENUM_NS_CLASS_T(chleni, uint8_t, huy, pizda);


    class CandleDatabase {
        static constexpr uint16_t VERSION = 1001;

    public:
        CandleDatabase(SR_UTILS_NS::StringAtom pair, CandleInterval interval, const SR_UTILS_NS::Path& path)
            : m_pair(pair), m_interval(interval)
        {
            m_databasePath = path.Concat(pair.ToString() + "_" + CandleIntervalValue.at(interval) + ".cd");
        }

    public:
        bool Load();
        SR_NODISCARD bool Save();

        SR_NODISCARD bool Exists();

        SR_NODISCARD void FetchAll();

        void Append(const std::vector<Candle>& candles);
        void Append(const Candle& candle);

    private:
        SR_UTILS_NS::StringAtom m_pair;
        CandleInterval m_interval;

        SR_UTILS_NS::Path m_databasePath;
        std::map<uint64_t, Candle> m_candles;
    };
}

#endif //BINARBOT_CANDLE_DATABASE_H
