#ifndef FASTQ_READER_HPP
#define FASTQ_READER_HPP

#include "SequenceFile.hpp"

/**
 * @brief Reads and validates FASTQ files. Inherits the common tools from SequenceFile.
 */
class FastqReader : public SequenceFile {
public:
    /** @brief Reads a FASTQ file and stores its headers, sequences and quality lines. */
    void read(const std::string &path);
};

#endif // FASTQ_READER_HPP
