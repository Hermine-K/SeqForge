// userPrompt.hpp

#ifndef USER_PROMPT_HPP
#define USER_PROMPT_HPP
#include <iostream>


class userPrompt {
public:
    void display_common_options();
    void display_fasta_only_options();
    void display_fastq_only_options();
    void display_fasta_menu();
    void display_fastq_menu();
    std::string ask_user_choice(); 

}; 

#endif
