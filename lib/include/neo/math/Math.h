#pragma once

#include <neo/Primitives.h>
#include <stdexcept>
#include <cml/functions/sqrt.hpp>
#include <cml/functions/tan.hpp>
#include <cml/functions/sin.hpp>
#include <cml/functions/cos.hpp>
#include <cml/functions/abs.hpp>
#include <cml/functions/clamp.hpp>
#include <cml/functions/factorial.hpp>

namespace Neo
{
    class Math
    {
    public:
		constexpr static float PI = 3.14159265359f;
		constexpr static float Epsilon = 1e-6f;

		template<typename T>
		constexpr inline static T Radians(T value)
		{
			return value * (PI / 180.0f);
		}

		template<typename T>
		constexpr inline static T HalfRadians(T value)
		{
			return value * ((PI / 180.0f) * 0.5f);
		}

		template<typename T>
		constexpr inline static T Tan(T value)
		{
			return cml::tan(value);
		}

		template<typename T>
		constexpr inline static T Sin(T value)
		{
			return cml::sin(value);
		}

		template<typename T>
		constexpr inline static T Cos(T value)
		{
			return cml::cos(value);
		}

		template<typename T>
		constexpr inline static T Abs(T value)
		{
			return cml::abs(value);
		}

		template<typename T>
		constexpr inline static T Inverse(T value)
		{
			if (value > 0)
			{
				return -value;
			}
			else if (value < 0)
			{
				return Abs(value);
			}
			else
			{
				return value;
			}
		}

		template<typename T>
		constexpr inline static T Sqrt(T value)
		{
			return cml::sqrt(value);
		}

		template<typename T>
		constexpr inline static T Lerp(T from, T to, T amount)
		{
			return from + (to - from) * amount;
		}

		template <typename T>
		constexpr inline static T Atan(T x)
		{
			return cml::atan(x);
		};

		template <typename T>
		constexpr inline static T Factorical(int32 n)
		{
			return cml::factorial(n);
		};

		template <typename T>
		constexpr inline static T Asin(T x)
		{
			return cml::asin(x);
		};

		template <typename T>
		constexpr inline static T Atan2(T x, T y)
		{
			return cml::atan2(x, y);
		};

		template <typename T>
		constexpr inline static T Clamp(T value, T min, T max)
		{
			return cml::clamp(value, min, max);
		};
    };
}
