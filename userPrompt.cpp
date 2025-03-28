
#include <iostream>
#include "userPrompt.hpp"



void userPrompt::display_common_options() {
    std::cout << "\n╭────────────────────────────── COMMON OPTIONS ─────────────────────────────╮" << std::endl;
    std::cout << "│ -mapping            : Perform mapping of reads (same length required)     │" << std::endl;
    std::cout << "│ -countseq           : Count the number of sequences                        │" << std::endl;
    std::cout << "│ -headers            : Display the headers of sequences (with indexes)     │" << std::endl;
    std::cout << "│ -sequence <index>   : Show sequence at position <index>                   │" << std::endl;
    std::cout << "│ -length <index>     : Show length of sequence at position <index>         │" << std::endl;
    std::cout << "│ -total_length       : Show total length of all sequences                  │" << std::endl;
    std::cout << "│ -search_naif        : Naive pattern search in sequence <index>           │" << std::endl;
    std::cout << "│ -table_suffix       : Display suffix table of sequence <index>           │" << std::endl;
    std::cout << "│ -table_LCP          : Display LCP table of sequence <index>              │" << std::endl;
    std::cout << "│ -search_suffix_tree : Pattern search using suffix tree in sequence <index>│" << std::endl;
    std::cout << "│ -quit               : Exit the program                                    │" << std::endl;
    std::cout << "╰────────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
}

void userPrompt::display_fasta_only_options() {
    std::cout << "\n╭──────────────────────────── FASTA SPECIFIC OPTIONS ────────────────────────╮" << std::endl;
    std::cout << "│ -all                : Display entire content of the FASTA file             │" << std::endl;
    std::cout << "╰────────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
}

void userPrompt::display_fastq_only_options() {
    std::cout << "\n╭──────────────────────────── FASTQ SPECIFIC OPTIONS ────────────────────────╮" << std::endl;
    std::cout << "│ -quality            : Display quality scores                               │" << std::endl;
    std::cout << "│ -filter_quality     : Filter reads based on quality (not implemented yet)  │" << std::endl;
    std::cout << "╰────────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
}

void userPrompt::display_fasta_menu() {
    std::cout << "\n Please choose an option (FASTA mode):\n" << std::endl;
    display_common_options();
    display_fasta_only_options();
}

void userPrompt::display_fastq_menu() {
    std::cout << "\n Please choose an option (FASTQ mode):\n" << std::endl;
    display_common_options();
    display_fastq_only_options();
}

std::string ask_user_choice() {
    std::string choice;
    std::cout << "\n Enter your option: ";
    std::cin>>choice; 
    std::cout << "\n You chose: " << choice << std::endl;
    return choice; 
    
}


