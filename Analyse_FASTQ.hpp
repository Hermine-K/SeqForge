#ifndef ANALYSE_FASTQ_HPP
#define ANALYSE_FASTQ_HPP

#include <iostream>
#include "Analyse_HK.hpp" // Include parent class


class Analyse_FASTQ : public Analyse_HK {
public:
    void display_menu() override {
        userPrompt user;
        user.display_fastq_menu();
    }
};
#endif // ANALYSE_FASTQ_HPP