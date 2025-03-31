#ifndef VERIFICATION_FASTQ_HPP
#define VERIFICATION_FASTQ_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class

/**
 * @brief Subclass for performing checks and parsing specific to FASTQ files.
 * Inherits common verification tools from verification_HK.
 */

class verification_FASTQ : public verification_HK {
public:

/**
     * @brief Reads and parses a FASTQ file.
     * Extracts headers, sequences, and quality scores, storing them in the inherited vectors.
     * @param name_fastq The path to the FASTQ file.
*/
    void read_fastq(std::string name_fastq); 
};
#endif // VERIFICATION_FASTQ_HPP
