#pragma once

#include <type_traits>

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#define ENABLE_BITMASK_OPERATORS(EnumType) \
constexpr static inline EnumType operator|(EnumType lhs, EnumType rhs) { \
using T = std::underlying_type_t<EnumType>; \
return static_cast<EnumType>(static_cast<T>(lhs) | static_cast<T>(rhs)); \
} \
constexpr static inline EnumType operator&(EnumType lhs, EnumType rhs) { \
using T = std::underlying_type_t<EnumType>; \
return static_cast<EnumType>(static_cast<T>(lhs) & static_cast<T>(rhs)); \
} \
constexpr static inline EnumType operator^(EnumType lhs, EnumType rhs) { \
using T = std::underlying_type_t<EnumType>; \
return static_cast<EnumType>(static_cast<T>(lhs) ^ static_cast<T>(rhs)); \
} \
constexpr static inline EnumType operator~(EnumType e) { \
using T = std::underlying_type_t<EnumType>; \
return static_cast<EnumType>(~static_cast<T>(e)); \
} \
constexpr static inline EnumType& operator|=(EnumType& lhs, EnumType rhs) { \
lhs = lhs | rhs; \
return lhs; \
} \
constexpr static inline EnumType& operator&=(EnumType& lhs, EnumType rhs) { \
lhs = lhs & rhs; \
return lhs; \
} \
constexpr static inline EnumType& operator^=(EnumType& lhs, EnumType rhs) { \
lhs = lhs ^ rhs; \
return lhs; \
} \
constexpr static inline bool HasFlag(EnumType value, EnumType flag) { \
using T = std::underlying_type_t<EnumType>; \
return (static_cast<T>(value) & static_cast<T>(flag)) == static_cast<T>(flag); \
}
