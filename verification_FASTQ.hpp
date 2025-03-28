#ifndef VERIFICATION_FASTQ_HPP
#define VERIFICATION_FASTQ_HPP

#include <iostream>
#include "verification_HK.hpp" // Include parent class


class verification_FASTQ : public verification_HK {
public:
    void read_fastq(std::string name_fastq); 
};
#endif
