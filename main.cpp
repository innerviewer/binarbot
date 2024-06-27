//
// Created by innerviewer on 25.08.2023.
//

#include <Binarbot/BinanceManager.h>

#include <Utils/Platform/Platform.h>
#include <Utils/Debug.h>

#include <Binarbot/Types/Candle.h>
#include <Binarbot/Types/CandleDatabase.h>

int main() {
    auto&& applicationDir = SR_PLATFORM_NS::GetApplicationDirectory();
    SR_UTILS_NS::Debug::Instance().Init(applicationDir.Concat("binarbot.log"), true);

    auto&& curlManager = Binarbot::CurlManager::Instance();

    curlManager.Init();
    curlManager.DisableCertificate();

    //auto&& binanceManager = Binarbot::BinanceManager::Instance();
    auto&& databaseDir = applicationDir.Concat("data");

    Binarbot::CandleDatabase database(SR_UTILS_NS::StringAtom("BTCUSDT"), Binarbot::CandleInterval::ONE_DAY, databaseDir);
    if (database.Exists()) {
        database.Load();
    }
    else {
        database.FetchAll();
        if (!database.Save()) {
            SR_ERROR("Failed to save candle database!");
            return 2;
        }
    }

    curlManager.DeInit();
    return 0;
}