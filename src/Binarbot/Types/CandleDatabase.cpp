//
// Created by innerviewer on 2024-06-24.
//

#include <Binarbot/Types/CandleDatabase.h>

namespace Binarbot {
    bool CandleDatabase::Load() {
        SR_LOG("CandleDatabase::Load() : loading database.");

        if (!m_candles.empty()) {
            SR_ERROR("CandleDatabase::Load() : database is not empty!");
            return false;
        }

        SR_HTYPES_NS::Marshal marshal = SR_HTYPES_NS::Marshal::Load(m_databasePath);
        if (!marshal.Valid()) {
            return false;
        }

        auto&& version = marshal.Read<uint16_t>();
        if (version != VERSION) {
            SR_ERROR("CandleDatabase::Load() : invalid version! Version: '{}'.", version);
            return false;
        }

        m_pair = SR_UTILS_NS::StringAtom(marshal.Read<std::string>());
        m_interval = static_cast<CandleInterval>(marshal.Read<uint8_t>());
        auto&& candleCount = marshal.Read<uint32_t>();

        for (uint32_t i = 0; i < candleCount; ++i) {
            auto&& candle = Candle::Load(&marshal);
            if (!candle.IsValid()) {
                SR_ERROR("CandleDatabase::Load() : candle is invalid!");
                return false;
            }

            m_candles[candle.GetOpenTime()] = candle;
        }

        return true;
    }

    bool CandleDatabase::Save() {
        SR_LOG("CandleDatabase::Save() : saving database.");

        if (m_candles.empty()) {
		    SR_ERROR("CandleDatabase::Save() : database is empty!");
            return false;
        }

        if (!m_databasePath.Create()) {
            SR_ERROR("CandleDatabase::Save() : failed to create destination directory.");
            return false;
        }

        SR_HTYPES_NS::Marshal marshal;
        marshal.Write<uint16_t>(VERSION);
        marshal.Write<std::string>(m_pair.ToString());
        marshal.Write<uint8_t>(m_interval);
        marshal.Write<uint32_t>(m_candles.size());

        for (auto&& [openTime, candle] : m_candles) {
            if (!candle.Save(&marshal)) {
                return false;
            }
        }

        return marshal.Save(m_databasePath);
    }

    bool CandleDatabase::Exists() {
        return m_databasePath.Exists();
    }

    void CandleDatabase::FetchAll() {
        SR_LOG("CandleDatabase::FetchAll() : fetching all candle data for pair '{}' and interval '{}'.", m_pair.ToString(), CandleIntervalValue.at(m_interval));
        auto&& serverTime = BinanceManager::Instance().GetServerTime();

        if (m_candles.empty()) {
            Append(BinanceManager::Instance().GetCandleData(m_pair, m_interval, 1000, 0));
        }

        auto&& candle = m_candles.rbegin()->second;

        while (candle.GetCloseTime() < serverTime) {
            Append(BinanceManager::Instance().GetCandleData(m_pair, m_interval, 1000, candle.GetCloseTime()));
            candle = m_candles.rbegin()->second;
        }
    }

    void CandleDatabase::Append(const std::vector<Candle>& candles) {
        for (auto&& candle : candles) {
            Append(candle);
        }
    }

    void CandleDatabase::Append(const Candle& candle) {
        if (!candle.IsValid()) {
            SR_ERROR("CandleDatabase::Append() : candle is invalid!");
            return;
        }

        if (!m_candles.contains(candle.GetOpenTime())) {
            m_candles[candle.GetOpenTime()] = candle;
        }
        else {
            SR_ERROR("CandleDatabase::Append() : candle is already in the database!");
        }
    }
}
