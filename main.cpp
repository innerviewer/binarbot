//
// Created by innerviewer on 25.08.2023.
//

#include <Binarbot/BinanceManager.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Debug.h>

int main() {
    Binarbot::CurlManager::Ptr pCurlManager = std::make_shared<Binarbot::CurlManager>();
    Binarbot::BinanceManager::Ptr pBinanceManager = std::make_shared<Binarbot::BinanceManager>(pCurlManager);

    auto&& applicationDir = SR_PLATFORM_NS::GetApplicationDirectory();
    SR_UTILS_NS::Debug::Instance().Init(applicationDir.Concat("binarbot.log"), true);

    pCurlManager->Init();
    pCurlManager->DisableCertificate();

    pBinanceManager->GetExchangeInfo();
    //pBinanceManager->GetPricesInfo();

    pCurlManager->DeInit();

    return 0;
}