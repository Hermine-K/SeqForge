#ifndef VERIFICATION_FASTA_HPP
#define VERIFICATION_FASTA_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class
#include <vector>

class verification_FASTA : public verification_HK {
public:
    bool validate_headers(const std::string &line);
    std::string validate_sequence(const std::string &line);  // Vérifie les séquences
    std::vector<std::string> heads; 
    std::vector<std::string> sequences;
    void read_fasta(std::string name_fasta); 
    void set_heads(std::string H); 
    void set_sequences(std::string S); 
};
#endif
