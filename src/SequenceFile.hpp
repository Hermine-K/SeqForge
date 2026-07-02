#ifndef SEQUENCE_FILE_HPP
#define SEQUENCE_FILE_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

/**
 * @brief Base class for reading and validating biological sequence files (FASTA/FASTQ).
 *
 * It groups the operations shared by the FASTA and FASTQ readers: locating the file,
 * checking its extension and content, validating sequences against the IUPAC alphabet,
 * and storing the parsed records (headers, sequences and, for FASTQ, quality lines).
 */
class SequenceFile {
public:
    /** @brief Makes sure the data directory exists, or creates it. */
    void ensure_directory();

    /** @brief Asks the user for a file name and returns its full path inside the data directory. */
    std::string ask_file_name();

    /** @brief Checks whether the given file path exists. */
    bool file_exists(const std::string &path);

    /** @brief Checks whether the file has a supported extension (.fasta, .fa, .fas, .fastq, .fq). */
    bool has_valid_extension(const std::string &name);

    /** @brief Checks whether a file is empty (or cannot be opened). */
    bool is_empty(const std::string &path);

    /** @brief Detects the format from the extension and the first character. @return "FASTA", "FASTQ" or "NONE". */
    std::string detect_format(const std::string &name);

    /** @brief Interactive loop that returns a valid file path chosen by the user. */
    std::string run_all_checks();

    /** @brief Non-interactive validation when the file name is already known. @return 0 on success, -1 otherwise. */
    int check_known_file(const std::string &name);

    /** @brief Validates a sequence against the IUPAC alphabet, replacing invalid characters with '-'. */
    std::string validate_sequence(const std::string &line);

    std::vector<std::string> headers;   ///< Header lines.
    std::vector<std::string> sequences; ///< Sequences.
    std::vector<std::string> quality;   ///< Quality lines (FASTQ only).

    /** @brief Adds a header to the internal list. */
    void add_header(const std::string &h);
    /** @brief Adds a sequence to the internal list. */
    void add_sequence(const std::string &s);
    /** @brief Adds a quality line to the internal list. */
    void add_quality(const std::string &q);
};

#endif // SEQUENCE_FILE_HPP
