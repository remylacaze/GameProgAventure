#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>

namespace gui
{
	const std::string menu_title(const std::string title);
	const std::string menu_divider(const unsigned amount = 30, const char symbol = '-');
	const std::string menu_item(const unsigned index, const std::string text);
	const void pausePressKey();
	const void pausePressKeyClear();
}
