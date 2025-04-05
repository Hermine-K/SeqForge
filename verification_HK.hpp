

#ifndef VERIFICATION_HK_HPP
#define VERIFICATION_HK_HPP

#include<iostream>
#include<fstream>
#include<filesystem>
#include <vector>

/**
 * @brief Class for handling generic verifications on biological sequence files (FASTA/FASTQ).
 */
class verification_HK{
    public: //public veut dire fonctions ou procédures qui peuvent être utiliser dans le main  
    /**
     * @brief Announces the start of a new FASTA project.
     */
        void new_project_fasta();

    
    /**
     * @brief Ensures the fasta_files directory exists, or creates it.
     */

        void fasta_repertory(); 

      /**
     * @brief Prompts the user to input the name of a FASTA file and returns its full path.
     * @return The complete path to the user-specified FASTA file.
     */

        std::string enter_name_fasta();

     /**
     * @brief Checks if the given file path exists.
     * @param file_path Full path to the file.
     * @return true if file exists, false otherwise.
     */

        bool exists_fasta(const std::string &file_path);

     /**
     * @brief Checks if the file has a valid FASTA or FASTQ extension.
     * @param name_fasta Name of the file.
     * @return true if the extension is valid, false otherwise.
     */

        bool extention_fasta(std::string name_fasta); 
    /**
     * @brief Performs a full verification loop to get a valid FASTA file from the user.
     * @return Validated file path.
     */    
        std::string all_verifications(); 

     /**
     * @brief Checks if a file is empty.
     * @param name_file Name or path of the file.
     * @return true if the file is empty or cannot be opened.
     */

        bool fasta_empty (const std::string &name_file); 

     /**
     * @brief Identifies the type of file based on its extension.
     * @param name_fasta Name of the file.
     * @return A string indicating "FASTA", "FASTQ" or "NONE".
     */

        std::string what_is_my_file(std::string name_fasta); 

     /**
     * @brief Performs file verification when the file name is already known.
     * @param name_file Name or path of the file.
     * @return 0 if all verifications pass, -1 otherwise.
     */

        int all_verifications_know_file(std::string name_file);

        //Fonctions d'héritage pour fasta et fastq
     /**
     * @brief Checks and validates a sequence string according to IUPAC codes.
     * @param line Sequence string to validate.
     * @return Validated sequence with invalid characters replaced by '-'.
     */   
        std::string validate_sequence(const std::string &line);  // Vérifie les séquences
        std::vector<std::string> heads; ///< Vector storing header lines.
        std::vector<std::string> sequences; ///< Vector storing sequences.
        std::vector<std::string> quality; ///< Vector storing quality scores.
    /**
     * @brief Adds a header line to the internal vector.
     * @param H The header string.
    */

        void set_heads(std::string H); 

    /**
     * @brief Adds a sequence to the internal vector.
     * @param seq The sequence string.
    */

        void set_sequences(std::string S); 


    /**
     * @brief Adds a quality score line to the internal vector.
     * @param Q The quality string.
    */

        void set_quality(std::string Q); 
       
}; 

#endif // VERIFICATION_HK_HPP



//Chaque fonction est documentée avec @brief, et les paramètres ou retours sont annotés quand c’est nécessaire (@param, @return).