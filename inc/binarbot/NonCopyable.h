//
// Created by innerviewer on 8/27/2023.
//

#ifndef BINARBOT_NONCOPYABLE_H
#define BINARBOT_NONCOPYABLE_H

namespace Binarbot {
    class NonCopyable {
    protected:
        constexpr NonCopyable() = default;
        virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif //BINARBOT_NONCOPYABLE_H
