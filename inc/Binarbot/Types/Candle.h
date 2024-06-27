//
// Created by innerviewer on 2024-06-24.
//

#ifndef BINARBOT_CANDLE_H
#define BINARBOT_CANDLE_H

#include <nlohmann/json.hpp>

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Marshal.h>

namespace Binarbot {
    /*SR_ENUM_NS_CLASS_T(CandleInterval, uint16_t,
        ONE_MINUTE,
        THREE_MINUTES,
        FIVE_MINUTES,
        FIFTEEN_MINUTES,
        THIRTY_MINUTES,
        ONE_HOUR,
        TWO_HOURS,
        FOUR_HOURS,
        SIX_HOURS,
        EIGHT_HOURS,
        TWELVE_HOURS,
        ONE_DAY,
        THREE_DAYS,
        ONE_WEEK,
        ONE_MONTH
    );*/

    class Candle {
        static constexpr uint16_t VERSION = 1001;
    public:
        void Initialize(const nlohmann::json& data);

        SR_NODISCARD static Candle Load(SR_HTYPES_NS::Marshal* pMarshal);
        SR_NODISCARD bool Save(SR_HTYPES_NS::Marshal* pMarshal) const;

        SR_NODISCARD std::string ToString();

    public:
        SR_NODISCARD bool IsValid() const { return m_isValid; }

        SR_NODISCARD uint64_t GetOpenTime() const { return m_openTime; }
        SR_NODISCARD uint64_t GetCloseTime() const { return m_closeTime; }

        SR_NODISCARD double GetOpenPrice() const { return m_openPrice; }
        SR_NODISCARD double GetClosePrice() const { return m_closePrice; }
        SR_NODISCARD double GetHighPrice() const { return m_highPrice; }
        SR_NODISCARD double GetLowPrice() const { return m_lowPrice; }

        SR_NODISCARD double GetVolume() const { return m_volume; }
        SR_NODISCARD uint32_t GetNumberOfTrades() const { return m_numberOfTrades; }

        SR_NODISCARD double GetQuoteAssetVolume() const { return m_quoteAssetVolume; }
        SR_NODISCARD double GetTakerBuyBaseAssetVolume() const { return m_takerBuyBaseAssetVolume; }
        SR_NODISCARD double GetTakerBuyQuoteAssetVolume() const { return m_takerBuyQuoteAssetVolume; }

    private:
        bool m_isValid = false;

        uint64_t m_openTime = 0;
        uint64_t m_closeTime = 0;

        double m_openPrice = 0.0f;
        double m_closePrice = 0.0f;
        double m_highPrice = 0.0f;
        double m_lowPrice = 0.0f;

        double m_volume = 0.0f;
        uint32_t m_numberOfTrades = 0;

        double m_quoteAssetVolume = 0.0f;
        double m_takerBuyBaseAssetVolume = 0.0f;
        double m_takerBuyQuoteAssetVolume = 0.0f;
    };
}

namespace std {
    template<> struct less<Binarbot::Candle> {
        bool operator()(const Binarbot::Candle& lhs, const Binarbot::Candle& rhs) const {
            return lhs.GetOpenTime() < rhs.GetOpenTime();
        }
    };
}

#endif //BINARBOT_CANDLE_H
