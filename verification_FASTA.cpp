//subclass for checks specific to fasta files. 

#include "verification_FASTA.hpp"

//Function that checks the header. 
bool verification_HK:: validate_headers(const std::string &line){
    return !line.empty() && (line[0]== '>' || line[0]== ';'); //Returns the line variable if it is not empty and begins with either ‘>’ or ‘;’.
}

//Function that checks the sequence.

bool verification_HK::validate_sequence(const std::string &line) {
    const std::string iupac = "ACGTNRYWSKMBDHV-acgtnrywskmbdhv-"; // List of valid IUPAC characters.

    // Checks whether the line is empty or a header (starts with ‘>’ or ‘;’).
    if (line.empty() || line[0] == '>' || line[0] == ';') {
        return true; //Go on. 

    }

    // Scrolls through each character on the line.
    for (std::size_t i = 0; i < line.size(); i++) {
       // Checks if the character is not in the IUPAC list.
        if (iupac.find(line[i]) == std::string::npos) {
            std::cerr<<"Error: character "<< line[i] << "found at position"<< i + 1<< "in the sequence :"<< line<< endl;   
            return false;       
        }
        

    }
    return true; 


}