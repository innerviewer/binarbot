//
// Created by innerviewer on 2024-06-24.
//

#include <Binarbot/Types/Candle.h>

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

    Candle Candle::Load(SR_HTYPES_NS::Marshal* pMarshal) {
        Candle candle;

        if (!pMarshal || !pMarshal->Valid()) {
            SR_ERROR("Candle::Load() : invalid marshal!");
            return candle;
        }

        auto&& version = pMarshal->Read<uint16_t>();
        if (version != VERSION) {
            SR_ERROR("Candle::Load() : invalid version! Version: '{}'.", version);
            return candle;
        }

        candle.m_openTime = pMarshal->Read<uint64_t>();
        candle.m_closeTime = pMarshal->Read<uint64_t>();

        candle.m_openPrice = pMarshal->Read<double>();
        candle.m_closePrice = pMarshal->Read<double>();
        candle.m_highPrice = pMarshal->Read<double>();
        candle.m_lowPrice = pMarshal->Read<double>();

        candle.m_volume = pMarshal->Read<double>();
        candle.m_numberOfTrades = pMarshal->Read<uint32_t>();

        candle.m_quoteAssetVolume = pMarshal->Read<double>();
        candle.m_takerBuyBaseAssetVolume = pMarshal->Read<double>();
        candle.m_takerBuyQuoteAssetVolume = pMarshal->Read<double>();

        candle.m_isValid = true;
        return candle;
    }

    bool Candle::Save(SR_HTYPES_NS::Marshal* pMarshal) const {
        if (!pMarshal || !pMarshal->Valid()) {
            SR_ERROR("Candle::Save() : invalid marshal!");
            return false;
        }

        pMarshal->Write(VERSION);

        pMarshal->Write(m_openTime);
        pMarshal->Write(m_closeTime);

        pMarshal->Write(m_openPrice);
        pMarshal->Write(m_closePrice);
        pMarshal->Write(m_highPrice);
        pMarshal->Write(m_lowPrice);

        pMarshal->Write(m_volume);
        pMarshal->Write(m_numberOfTrades);

        pMarshal->Write(m_quoteAssetVolume);
        pMarshal->Write(m_takerBuyBaseAssetVolume);
        pMarshal->Write(m_takerBuyQuoteAssetVolume);

        return true;
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
