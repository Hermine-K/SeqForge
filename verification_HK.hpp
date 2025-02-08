

#ifndef VERIFICATION_HK_HPP
#define VERIFICATION_HK_HPP

#include<iostream>
#include<fstream>
#include<filesystem>


class verification_HK{
    public: //public veut dire fonctions ou procédures qui peuvent être utiliser dans le main  
        void new_project_fasta();
        void fasta_repertory();  
        std::string enter_name_fasta();
        bool exists_fasta(const std::string &file_path);
        bool extention_fasta(std::string name_fasta); 
        std::string all_verifications(); 
        bool fasta_empty (const std::string &name_file); 
        std::string what_is_my_file(std::string name_fasta); 
       
} ; 

#endif 
