#ifndef VERIFICATION_FASTA_HPP
#define VERIFICATION_FASTA_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class

/**
 * @brief Subclass for performing checks and parsing specific to FASTA files.
 * Inherits common verification tools from verification_HK.
 */
class verification_FASTA : public verification_HK {
public:
 /**
     * @brief Reads and parses a FASTA file.
     * Extracts headers and sequences, storing them in the inherited vectors.
     * @param name_fasta The path to the FASTA file.
*/
    void read_fasta(std::string name_fasta); 
};
#endif // VERIFICATION_FASTA_HPP
