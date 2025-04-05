//subclass for checks specific to fasta files. 

#include "verification_FASTA.hpp"


void verification_FASTA::read_fasta(std::string name_fasta){
    std::ifstream file(name_fasta); // ifstream is used to open a file and store its content.
    if(file){//True if the file is open. 
        bool new_seq = true; 
        std::string seq = "";

        while(file){ //As long as the file is open.
            int car = file.peek(); //int because even if it's a character, we store the ascii code. If, for example, we want to check that we have letters, we have direct code. visible characters start with 32, so if we are on a visible character (!; A; b; etc) we are in ascii code.
            if (car != -1){ //check that we're not at the end of the doc with the ascii number.
                if (new_seq) { //check if you are in a seq
                    if (car > 32){ //checks whether the ascii number is greater than 32. > 32 punctuation character
                        if (car == ';' or car == '>'){ //vérifie si c'est l'entête.
                            new_seq = false; 
                            std:: string H; //stocke l'entête. 
                            getline(file, H); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                            set_heads(H); //ajouter l'entête à la liste head(vecteur)
                        } 

                    }
                }else{
                    if (car == ';' or car == '>'){ 
                        set_sequences(seq); // pour vérifier que ce n'est pas une entête donc pourvoir faire le else 
                        new_seq = true;
                        seq = "";
                        

                    
                    }else{
                        std:: string S;  //stocke la ligne de sequence.
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



