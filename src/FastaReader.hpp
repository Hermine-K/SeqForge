#ifndef FASTA_READER_HPP
#define FASTA_READER_HPP

#include "SequenceFile.hpp"

/**
 * @brief Reads and validates FASTA files. Inherits the common tools from SequenceFile.
 */
class FastaReader : public SequenceFile {
public:
    /** @brief Reads a FASTA file and stores its headers and sequences. */
    void read(const std::string &path);
};

#endif // FASTA_READER_HPP
