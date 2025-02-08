//subclass for checks specific to fasta files. 

#include "verification_FASTA.hpp"

//Function that checks the header. 
bool verification_FASTA:: validate_headers(const std::string &line){
    return !line.empty() && (line[0]== '>' || line[0]== ';'); //Returns the line variable if it is not empty and begins with either ‘>’ or ‘;’.
}

//Function that checks the sequence.

std::string verification_FASTA::validate_sequence(const std::string &line) {
    const std::string iupac = "ACGTNRYWSKMBDHV-.acgtnrywskmbdhv-."; // List of valid IUPAC characters.
    std::string good_line;
    // Scrolls through each character on the line.
    for (std::size_t i = 0; i < line.size(); i++) {
       // Checks if the character is not in the IUPAC list.
        if (iupac.find(line[i]) == std::string::npos) {
            std::cerr<<"Error: character "<< line[i] << "found at position"<< i + 1<< "in the sequence :"<< line<< std::endl;   
              
        } 
        else { 
            good_line.push_back(line[i]); 

        } 

    }
    return good_line; 
}


void verification_FASTA::read_fasta(std::string name_fasta){
    std::ifstream file(name_fasta); // ifstream is used to open a file and store its content.
    if(file){//True if the file is open. 
        bool new_seq = true; 
        std::string seq = "";

        while(file){ //Tant que le fichier est ouvert. 
            int car = file.peek(); //int car même si c'est un caratère, on stocke le code ascii. Si Par exemple on veut vérifier qu'on a des lettres on a sont code directe. les caratères visibles débute par 32 donc si on est sur un caratère visible (!; A; b; etc) on est donc dans le code asci
            if (car != -1){ //vérifie qu'on est pas à la fin du doc avec le numéro ascii. 
                if (new_seq) { //vérifie si on est dans une seq
                    if (car > 32){ //verifie si le numéro ascii est supérieur à 32.
                        if (car == ';' or car == '>'){ //vérifie si c'est l'entête.
                            new_seq = false; 
                            std:: string H; //stocke l'entête. 
                            getline(file, H); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                            set_heads(H);
                            std::cout<<"We add the header to the list"<< std::endl;   
                        } 

                    }
                }else{
                    if (car == ';' or car == '>'){ 
                        set_sequences(seq);
                    
                }else{
                    std:: string S; //stocke la ligne de sequence. 
                    getline(file, S); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                    seq+=validate_sequence(S); //fait le filtre et les warning

                }
                } 

            }
        }
    set_sequences(seq);
    file.close();
    }
}



void verification_FASTA::set_heads(std::string H){
    heads.push_back(H);
}

void verification_FASTA::set_sequences(std::string seq){
    sequences.push_back(seq);
}