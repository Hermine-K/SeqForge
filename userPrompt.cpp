
#include <iostream>
#include "userPrompt.hpp"


// Display the available options that the user can choose from
void userPrompt::display_options() {
    std::cout<<"\n╭────────────────────────────── COMMON OPTIONS ─────────────────────────────╮" << std::endl;
    std::cout << "│ -countseq           : Count the number of sequences                       │" << std::endl;
    std::cout << "│ -headers            : Display the headers of sequences (with indexes)     │" << std::endl;
    std::cout << "│ -sequence           : Show sequence at position <index>                   │" << std::endl;
    std::cout << "│ -length             : Show length of sequence at position <index>         │" << std::endl;
    std::cout << "│ -total_length       : Show total length of all sequences                  │" << std::endl;
    std::cout << "| -complement         : Display complementary sequence at position <index>  |" << std::endl;
    std::cout << "│ -quality_score      : Display quality scores                              │" << std::endl; 
    std::cout << "| -table_suffix       : Display suffix + LCP table of sequence <index>      |" << std::endl;
    std::cout << "│ -mapping            : Perform mapping of reads (same length required)     │" << std::endl;
    std::cout << "│ -quit               : Exit the program                                    │" << std::endl;
    std::cout << "╰───────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
}

// Ask the user to enter an option, and return their choice as a string
std::string userPrompt::ask_user_choice(){
    std::string choice;
    std::cout << "\n Enter your option: ";
    std::cin>>choice; 
    //std::cout << "\n You chose: " << choice << std::endl;
    return choice; 
    
}






