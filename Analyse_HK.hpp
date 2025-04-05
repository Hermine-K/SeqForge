// Analyse.hpp

#ifndef ANALYSE_HPP
#define ANALYSE_HPP

#include <vector>
#include <string>
#include <iostream>
#include "verification_HK.hpp"
#include "userPrompt.hpp"

/**
 * @brief Enum to indicate the type of file being analyzed.
*/

enum class fileType { FASTA, FASTQ };

/**
 * @brief Main analysis class for both FASTA and FASTQ files.
 *
 * This class contains all the functions to analyze biological sequence data.
 * It centralizes the analysis logic regardless of the file format.
*/


class Analyse_HK {

private:
    verification_HK* verif; ///< Pointer to a verification object containing sequences, headers, etc.
    fileType type; ///< Type of the input file (FASTA or FASTQ)


public:
    /**
     * @brief Sets the pointer to the verification object.
     * @param v Pointer to a verification_HK or derived class object.
     */
    void set_verif(verification_HK* v);

    /**
     * @brief Entry point for analysis, allows access to all analysis options.
     * @param name_file Name of the input file.
     * @param t Type of the file (FASTA or FASTQ).
     */
    void analyse(const std::string& name_file, fileType t);

    /**
     * @brief Menu system to display and handle user options.
     * @param type Type of the file (FASTA or FASTQ).
     */
    void display_menu(fileType type);

    /**
     * @brief Displays all headers stored in the file.
     */
    void show_headers();

    /**
     * @brief Displays all sequences stored in the file.
     */
    void show_sequences();

    /**
     * @brief Shows the length of a specific sequence (by index).
     */
    void length();

    /**
     * @brief Displays the total number of sequences.
     */
    void countseq();

    /**
     * @brief Calculates and displays the total length of all sequences combined.
     */
    void total_length();

    /**
     * @brief Displays the complementary strand of a selected sequence.
     */
    void show_complement();

    /**
     * @brief Generates and shows a suffix table for a selected sequence.
     */
    void show_suffix_table();
    
    /**
     * @brief Generates and shows all of fasta.
     */
    void show_all_fasta();

    /**
     * @brief Generates and shows all of fastq.
     */

    void show_all_fastq();

    /**
     * @brief Filters and displays sequence positions by quality score.
     * @param encoding The encoding method selected by the user (Phred+33 or Phred+64).
     * @param seq_index Index of the sequence to evaluate.
     * @param min_quality Minimum acceptable quality score.
     */
    void quality_score(int encoding, int seq_index, int min_quality);
};

#endif // ANALYSE_HK_HPP
