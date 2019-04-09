#pragma once
#include <type_traits>

namespace fdxx
{
template <typename Enum>
struct EnableBitMaskOperators
{
    static const bool enable = true;
};

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator|(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator|=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator&(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator&=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator^(Enum lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template <typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator^=(Enum& lhs, Enum rhs)
{
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}
} // namespace fdxx

#define ENABLE_BIT_MASK_OPERATORS(x)       \
    template <>                            \
    struct fdxx::EnableBitMaskOperators<x> \
    {                                      \
        static const bool enable = true;   \
    };
