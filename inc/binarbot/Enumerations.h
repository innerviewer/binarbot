//
// Created by innerviewer on 8/27/2023.
//

#ifndef BINARBOT_ENUMERATIONS_H
#define BINARBOT_ENUMERATIONS_H

#include <binarbot/EnumReflector.h>

/// -----------------------------------------[Базовые с настройкой типа]------------------------------------------------

/// Declare an enumeration inside a class
#define BB_ENUM_T(enumName, type, ...)                                                                                  \
      SR_ENUM_DETAIL_MAKE(enum, class, enumName, type, __VA_ARGS__ )                                                    \

/// Declare an enumeration inside a class
#define BB_ENUM_CLASS_T(enumName, type, ...)                                                                            \
      BB_ENUM_DETAIL_MAKE(enum class, class, enumName, type, __VA_ARGS__ )                                              \

/// Declare an enumeration inside a namespace
#define BB_ENUM_NS_T(enumName, type, ...)                                                                               \
      BB_ENUM_DETAIL_MAKE(enum, namespace, enumName, type, __VA_ARGS__ )                                                \

/// Declare an enumeration inside a namespace
#define BB_ENUM_NS_CLASS_T(enumName, type, ...)                                                                         \
      BB_ENUM_DETAIL_MAKE(enum class, namespace, enumName, type, __VA_ARGS__ )                                          \
      typedef type BB_MACRO_CONCAT(enumName, Flag);                                                                     \

/// Declare an enumeration inside a namespace
#define BB_ENUM_NS_STRUCT_T(enumName, type, ...)                                                                        \
      struct enumName {                                                                                                 \
            BB_ENUM_DETAIL_MAKE(enum, class, BB_MACRO_CONCAT(enumName, T), type, __VA_ARGS__ )                          \
      };                                                                                                                \
      typedef type BB_MACRO_CONCAT(enumName, Flag);                                                                     \

#endif //BINARBOT_ENUMERATIONS_H
