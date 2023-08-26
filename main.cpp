//
// Created by innerviewer on 25.08.2023.
//

#include <binarbot/BinanceManager.h>

int main() {
    Binarbot::CurlManager::Ptr pCurlManager = std::make_shared<Binarbot::CurlManager>();
    Binarbot::BinanceManager::Ptr pBinanceManager = std::make_shared<Binarbot::BinanceManager>(pCurlManager);

    pCurlManager->Init();
    pCurlManager->DisableCertificate();

    pBinanceManager->GetExchangeInfo();

    pCurlManager->DeInit();

    return 0;
}