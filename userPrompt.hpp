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
    void display_common_options();
/**
     * @brief Displays options specific to FASTA files.
*/

    void display_fasta_only_options();

/**
     * @brief Displays options specific to FASTQ files.
 */

    void display_fastq_only_options();

 /**
     * @brief Displays the combined menu for FASTA mode.
*/

    void display_fasta_menu();
 /**
     * @brief Displays the combined menu for FASTQ mode.
*/

    void display_fastq_menu();

/**
 * @brief Prompts the user to enter a choice from the menu.
 * @return The option entered by the user.
 */

    std::string ask_user_choice(); 

}; // USERPROMPT_HPP

#endif
