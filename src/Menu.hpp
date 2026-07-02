#ifndef MENU_HPP
#define MENU_HPP

#include <string>

/**
 * @brief Prints the ASCII banner and the interactive menu, and reads the user's choice.
 */
class Menu {
public:
    /** @brief Prints the ASCII-art banner, a one-line description and the version. */
    void print_banner();

    /** @brief Prints the grouped, boxed list of options. */
    void display_options();

    /** @brief Asks the user to type an option and returns it. */
    std::string ask_choice();
};

#endif // MENU_HPP
