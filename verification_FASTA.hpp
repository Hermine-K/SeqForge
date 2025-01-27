#ifndef VERIFICATION_FASTA_HPP
#define VERIFICATION_FASTA_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class

class verification_FASTA : public verification_HK {
public:
    bool validate_headers(const std::string &line)
    bool validate_sequences(const std::string &line); // Vérifie les séquences
    bool validate_fasta_format(const std::string &file_path); // Vérifie tout le fichier
};

#endif
