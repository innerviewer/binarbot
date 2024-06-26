//
// Created by innerviewer on 2024-06-24.
//

#ifndef BINARBOT_CANDLE_DATABASE_H
#define BINARBOT_CANDLE_DATABASE_H

#include <Binarbot/Types/Candle.h>
#include <units.h>

namespace Binarbot {
    SR_ENUM_NS_CLASS_T(chleni, uint8_t, huy, pizda);


    class CandleDatabase {
        static constexpr uint16_t VERSION = 1001;

    public:
        CandleDatabase(SR_UTILS_NS::StringAtom pair, units::time::minute_t interval)
            : m_pair(pair), m_interval(interval)
        { }

    public:
        static bool Load(const SR_UTILS_NS::Path& path);
        SR_NODISCARD bool Save(const SR_UTILS_NS::Path& path);

        SR_NODISCARD bool FetchAll();

        void Sort() {}

        void Append(const std::vector<Candle>& candles);
        void Append(const Candle& candle);

    private:
        bool m_isSorted = true;
        SR_UTILS_NS::StringAtom m_pair;
        units::time::minute_t m_interval;

        SR_UTILS_NS::Path m_databasePath;
        std::vector<Candle> m_candles;
    };
}

#endif //BINARBOT_CANDLE_DATABASE_H
