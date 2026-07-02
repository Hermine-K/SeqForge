#ifndef SEQUENCE_ANALYZER_HPP
#define SEQUENCE_ANALYZER_HPP

#include <string>
#include "SequenceFile.hpp"

/** @brief The format of the file being analyzed. */
enum class FileType { Fasta, Fastq };

/**
 * @brief Runs the interactive analysis of a parsed FASTA or FASTQ file.
 *
 * It holds a pointer to a SequenceFile (a FastaReader or a FastqReader) and offers
 * all the analysis options: counting, lengths, complement, suffix table, quality filtering.
 */
class SequenceAnalyzer {
private:
    SequenceFile* file = nullptr; ///< Pointer to the parsed file (headers, sequences, quality).
    FileType type = FileType::Fasta; ///< Format of the input file.

public:
    /** @brief Sets the pointer to the parsed file. */
    void set_file(SequenceFile* f);

    /** @brief Entry point: displays the menu and handles the user's choices. */
    void run(const std::string &name, FileType t);

    /** @brief Displays the menu, including the options specific to the file type. */
    void show_menu(FileType t);

    void show_headers();
    void show_sequences();
    void sequence_length();
    void count_sequences();
    void total_length();
    /** @brief Prints a summary: sequence count, lengths, N50 and GC content. */
    void show_stats();
    void show_complement();
    void show_suffix_table();
    void show_all_fasta();
    void show_all_fastq();

    /** @brief Two-bit encodes a chosen sequence and reports the packed size and round trip. */
    void encode_sequence();

    /** @brief Maps the reads of a second file onto the first reference sequence, by seed-and-extend. */
    void map_reads();

    /**
     * @brief Filters a sequence by quality score.
     * @param encoding 1 for Phred+33, 2 for Phred+64.
     * @param seq_index 1-based index of the sequence.
     * @param min_quality Minimum accepted quality score.
     */
    void filter_by_quality(int encoding, int seq_index, int min_quality);
};

#endif // SEQUENCE_ANALYZER_HPP
