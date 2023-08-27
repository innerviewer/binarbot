//
// Created by innerviewer on 8/27/2023.
//

#ifndef BINARBOT_SINGLETON_H
#define BINARBOT_SINGLETON_H

#include <binarbot/NonCopyable.h>

namespace Binarbot {
    template<typename T> class Singleton;

    class SingletonManager : public NonCopyable {
    public:
        void** GetSingleton(uint64_t id) noexcept;

    private:
        std::unordered_map<uint64_t, void*> m_singletons;

    };

    SingletonManager* GetSingletonManager() noexcept;

    template<typename T> class Singleton : public NonCopyable {
    protected:
        Singleton() = default;
        ~Singleton() override = default;

    public:
        static bool IsSingletonInitialized() noexcept {
            auto&& pSingleton = GetSingleton();
            return pSingleton && *pSingleton;
        }

        static void DestroySingleton() {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                return;
            }

            if (!(*singleton)->IsSingletonCanBeDestroyed()) {
                BB_ERROR("DestroySingleton() : singleton can't be destroyed!");
                return;
            }

            (*singleton)->OnSingletonDestroy();

            delete *singleton;
            (*singleton) = nullptr;
        }

        /// TODO: это не потокобезопасно, нужно переделать
        static T& Instance() noexcept {
            auto&& singleton = GetSingleton();

            if (!(*singleton)) {
                *singleton = new T();
                (*singleton)->InitSingleton();
            }

            return *static_cast<T*>(*singleton);
        }

        static void LockSingleton() noexcept {
            if (auto&& singleton = GetSingleton()) {
                if (!(*singleton)) {
                    *singleton = new T();
                    (*singleton)->InitSingleton();
                }

                (*singleton)->m_mutex.lock();
            }
        }

        static void UnlockSingleton() noexcept {
            if (auto&& singleton = GetSingleton()) {
                if (!(*singleton)) {
                    BB_ERROR("UnlockSingleton() : singleton isn't initialized!");
                    return;
                }

                (*singleton)->m_mutex.unlock();
            }
        }

        static std::recursive_mutex& GetMutex() noexcept {
            return Instance().m_mutex;
        }

    protected:
        virtual void OnSingletonDestroy() { }
        virtual void InitSingleton() { }
        virtual bool IsSingletonCanBeDestroyed() const { return true; }

    private:
        static Singleton<T>** GetSingleton() noexcept {
            void** p = GetSingletonManager()->GetSingleton(typeid(Singleton<T>).hash_code());
            return reinterpret_cast<Singleton<T>**>(p);
        }

    protected:
        mutable std::recursive_mutex m_mutex;

        };
}

#endif //BINARBOT_SINGLETON_H
