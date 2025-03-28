#ifndef VERIFICATION_FASTA_HPP
#define VERIFICATION_FASTA_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class


class verification_FASTA : public verification_HK {
public:
    void read_fasta(std::string name_fasta); 
};
#endif
