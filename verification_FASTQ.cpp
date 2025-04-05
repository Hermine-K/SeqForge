//subclass for checks specific to fastq files. 

#include "verification_FASTQ.hpp"


void verification_FASTQ::read_fastq(std::string name_fastq){
    std::ifstream file(name_fastq); // ifstream is used to open a file and store its content.
    if(file){//True if the file is open. 
        bool new_seq = true; 
        bool new_quality = false; 
        std::string seq = "";
        std::string quality = ""; 

        while(file){ //As long as the file is open.
            int car = file.peek(); //int because even if it's a character, we store the ascii code. If, for example, we want to check that we have letters, we have direct code. visible characters start with 32, so if we are on a visible character (!; A; b; etc) we are in ascii code.
            if (car != -1){ //check that we're not at the end of the doc with the ascii number.
                if (new_seq) { //check if you are in a seq
                    if (car > 32){ //checks whether the ascii number is greater than 32. > 32 punctuation character
                        if (car == '@'){ //check if this is the header.
                            new_seq = false; 
                            std:: string H; //stocke the header.
                            getline(file, H); //reads the whole line, even the last character, and goes to the next line, then stays on the new line.
                            set_heads(H); //add the header to the list head(vector)  
                        } 
                    }
                }else{
                    if (car == '@'){ 
                        set_quality(quality); // to check that it's not a header, so you can do the else
                        quality = "";
                        new_quality = false;   
                        new_seq = true;

                    }else{
                        if(car == '+'){
                           set_sequences(seq);
                           seq = ""; 
                           std:: string o; //allows you to skip a line, so that as soon as you exit the if, you go to the next line.
                           getline(file, o);
                           new_quality = true; 
                        }  
                        if(new_quality){
                            std:: string Q; //stocke the quality line.
                            getline(file, Q); //reads the whole line, even the last character, and goes to the next line, then stays on the new line.
                            quality+=Q; //does the filter and warnings
                  
                        }else{
                            std:: string S; //stocke the sequence line.
                            getline(file, S); //reads the whole line, even the last character, and goes to the next line, then stays on the new line.
                            seq+=validate_sequence(S); //does the filter and warnings
                        } 
                    }
                } 

            }
        }
    set_quality(quality);
    file.close();

    }
}



