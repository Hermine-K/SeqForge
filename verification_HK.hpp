

#ifndef VERIFICATION_HK_HPP
#define VERIFICATION_HK_HPP

#include<iostream>

#include<fstream>


class verification_HK{
    public: //public veut dire fonctions ou procédures qui peuvent être utiliser dans le main  
        void new_project_fasta();
        std::string enter_name_fasta();
        bool extention_fasta(std::string name_fasta); 
        std::string all_verifications(); 
        bool fasta_empty (std:: string name_file); 
       
} ; 

#endif 
