// userPrompt.hpp

#ifndef USER_PROMPT_HPP
#define USER_PROMPT_HPP
#include <iostream>

/**
 * @brief Class to handle user interface options and display menus.
 * Offers different menus and help options depending on the file type (FASTA or FASTQ).
 */

class userPrompt {
public:

/**
     * @brief Displays all common options available for sequence analysis.
*/
    void display_options();

    std::string ask_user_choice(); 

}; // USERPROMPT_HPP

#endif
