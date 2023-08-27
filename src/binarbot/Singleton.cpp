//
// Created by innerviewer on 8/27/2023.
//

#include <binarbot/Singleton.h>

namespace Binarbot {
    SingletonManager* GetSingletonManager() noexcept {
        static SingletonManager* singletonManager = nullptr;

        if (!singletonManager) {
            singletonManager = new SingletonManager();
        }

        return singletonManager;
    }

    void** SingletonManager::GetSingleton(uint64_t id) noexcept {
        if (auto&& pIt = m_singletons.find(id); pIt != m_singletons.end()) {
            return &pIt->second;
        }

        auto&& pIt = m_singletons.insert(std::make_pair(id, nullptr));
        return &pIt.first->second;
    }
}