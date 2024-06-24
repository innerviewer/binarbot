//
// Created by innerviewer on 2024-06-24.
//

#include <Binarbot/Types/Candle.h>
#include <Utils/Types/Marshal.h>

namespace Binarbot {
    void Candle::Initialize(const nlohmann::json& data) {
        if (data.empty()) {
            SR_ERROR("Candle::Initialize() : JSON data is empty!");
            return;
        }


        m_openTime = data[0].get<uint64_t>();
        m_openPrice = stod(data[1].get<std::string>());
        m_highPrice = stod(data[2].get<std::string>());
        m_lowPrice = stod(data[3].get<std::string>());
        m_closePrice = stod(data[4].get<std::string>());
        m_volume = stod(data[5].get<std::string>());
        m_closeTime = data[6].get<uint64_t>();
        m_quoteAssetVolume = stod(data[7].get<std::string>());
        m_numberOfTrades = data[8].get<uint32_t>();
        m_takerBuyBaseAssetVolume = stod(data[9].get<std::string>());
        m_takerBuyQuoteAssetVolume = stod(data[10].get<std::string>());

        if (m_openTime == 0 || m_closeTime == 0) {
            return;
        }

        m_isValid = true;
    }

    Candle Candle::Load(const SpaRcle::Utils::Path& src) {
        Candle candle;
        auto&& marshal = SR_HTYPES_NS::Marshal::Load(src);
        candle.m_openTime = marshal.Read<uint64_t>();
        candle.m_closeTime = marshal.Read<uint64_t>();

        candle.m_openPrice = marshal.Read<double>();
        candle.m_closePrice = marshal.Read<double>();
        candle.m_highPrice = marshal.Read<double>();
        candle.m_lowPrice = marshal.Read<double>();

        candle.m_volume = marshal.Read<double>();
        candle.m_numberOfTrades = marshal.Read<uint32_t>();

        candle.m_quoteAssetVolume = marshal.Read<double>();
        candle.m_takerBuyBaseAssetVolume = marshal.Read<double>();
        candle.m_takerBuyQuoteAssetVolume = marshal.Read<double>();

        if (candle.m_openTime == 0 || candle.m_closeTime == 0) {
            candle.m_isValid = false;
        }

        candle.m_isValid = true;
        return candle;
    }

    bool Candle::Save(const SR_UTILS_NS::Path& dest) const {
        SR_HTYPES_NS::Marshal marshal;
        marshal.Write(m_openTime);
        marshal.Write(m_closeTime);

        marshal.Write(m_openPrice);
        marshal.Write(m_closePrice);
        marshal.Write(m_highPrice);
        marshal.Write(m_lowPrice);

        marshal.Write(m_volume);
        marshal.Write(m_numberOfTrades);

        marshal.Write(m_quoteAssetVolume);
        marshal.Write(m_takerBuyBaseAssetVolume);
        marshal.Write(m_takerBuyQuoteAssetVolume);

        return marshal.Save(dest);
    }

    std::string Candle::ToString() {
        nlohmann::json json;
        json["openTime"] = m_openTime;
        json["openPrice"] = m_openPrice;
        json["highPrice"] = m_highPrice;
        json["lowPrice"] = m_lowPrice;
        json["closePrice"] = m_closePrice;
        json["volume"] = m_volume;
        json["closeTime"] = m_closeTime;
        json["quoteAssetVolume"] = m_quoteAssetVolume;
        json["numberOfTrades"] = m_numberOfTrades;
        json["takerBuyBaseAssetVolume"] = m_takerBuyBaseAssetVolume;
        json["takerBuyQuoteAssetVolume"] = m_takerBuyQuoteAssetVolume;

        return json.dump();
    }
}
