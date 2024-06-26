//
// Created by innerviewer on 2024-06-24.
//

#include <Binarbot/Types/CandleDatabase.h>

namespace Binarbot {
    bool CandleDatabase::Load(const SR_UTILS_NS::Path& path) {
        SR_HTYPES_NS::Marshal marshal;
        if (!marshal.Load(path)) {
            return false;
        }

        auto&& version = marshal.Read<uint16_t>();
        if (version != VERSION) {
            SR_ERROR("CandleDatabase::Load() : invalid version! Version: '{}'.", version);
            return false;
        }

        auto&& pair = SR_UTILS_NS::StringAtom(marshal.Read<std::string>());
        units::time::minute_t interval(marshal.Read<uint16_t>());

        CandleDatabase database(pair, interval);

        database.m_candles.reserve(marshal.Read<uint32_t>());

        for (uint32_t i = 0; i < database.m_candles.capacity(); ++i) {
            auto&& candle = Candle::Load(&marshal);
            if (!candle.IsValid()) {
                SR_ERROR("CandleDatabase::Load() : candle is invalid!");
                return false;
            }

            database.m_candles.emplace_back(candle);
        }

        return true;
    }

    bool CandleDatabase::Save(const SR_UTILS_NS::Path& path) {
		if (m_candles.empty()) {
            return false;
        }

        if (!m_isSorted) {
            Sort();
        }

        SR_HTYPES_NS::Marshal marshal;
        marshal.Write<uint16_t>(VERSION);
        marshal.Write<std::string>(m_pair.ToString());
        marshal.Write<uint32_t>(static_cast<uint32_t>(m_interval.value()));
        marshal.Write<uint32_t>(m_candles.size());

        for (const auto& candle : m_candles) {
            if (!candle.Save(&marshal)) {
                return false;
            }
        }

        return marshal.Save(path);
    }

    bool CandleDatabase::FetchAll() {
        if (!m_candles.empty()) {
            return false; // TODO: implement logic in this case.
        }


    }

    void CandleDatabase::Append(const std::vector<Candle>& candles) {
        m_candles.insert(m_candles.end(), candles.begin(), candles.end());
        m_isSorted = false;
    }

    void CandleDatabase::Append(const Candle& candle) {
        m_candles.emplace_back(candle);
        m_isSorted = false;
    }
}
