#ifndef ANALYSE_FASTA_HPP
#define ANALYSE_FASTA_HPP

#include <iostream>
#include "Analyse_HK.hpp" // Include parent class

class Analyse_FASTA : public Analyse_HK {
public:
    void display_menu() override {
        userPrompt user;
        user.display_fasta_menu();
    }
};
#endif // ANALYSE_FASTA_HPP