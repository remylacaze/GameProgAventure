#include "GUIHelper.h"

const std::string gui::menu_title(const std::string title)
{
	std::stringstream ss;

	ss << "= " << title << " ="
		<< "\n"
		<< "\n";

	return ss.str();
}

const std::string gui::menu_divider(const unsigned amount, const char symbol)
{
	std::stringstream ss;

	ss << std::string(amount, symbol)
		<< "\n"
		<< "\n";

	return ss.str();
}

const std::string gui::menu_item(const unsigned index, const std::string text)
{
	std::stringstream ss;

	ss << "- " << "(" << index << ") " << text
		<< "\n";

	return ss.str();
}

const void gui::pausePressKey()
{
	std::string sentence = "----------------------Press any key to continue----------------------";
	std::cout << sentence;
	_getch();
	std::cout << "\r" + std::string(sentence.length(), ' ') << "\r";
}

const void gui::pausePressKeyClear()
{
	std::string sentence = "----------------------Press any key to continue----------------------";
	std::cout << sentence;
	_getch();
	system("CLS");
}
