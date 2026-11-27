#pragma once
#include <string>
#include <string_view>

namespace Config {
	inline constexpr std::string_view engineVersion = "0.0.1-dev" ;
	inline constexpr std::string_view engineName = "Core Engine 2026";

	inline constexpr unsigned short versionMajor = 0;
	inline constexpr unsigned short versionMinor = 0;
	inline constexpr unsigned short versionPatch = 1;

	inline constexpr unsigned short width = 1680;
	inline constexpr unsigned short height = 920;

	inline constexpr std::string_view buildDate = __DATE__;
	inline constexpr const char* BuildDate = __TIME__;
}