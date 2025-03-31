//subclass for checks specific to fastq files. 

#include "verification_FASTQ.hpp"


void verification_FASTQ::read_fastq(std::string name_fastq){
    std::ifstream file(name_fastq); // ifstream is used to open a file and store its content.
    if(file){//True if the file is open. 
        bool new_seq = true; 
        bool new_quality = false; 
        std::string seq = "";
        std::string quality = ""; 

        while(file){ //Tant que le fichier est ouvert. 
            int car = file.peek(); //int car même si c'est un caratère, on stocke le code ascii. Si Par exemple on veut vérifier qu'on a des lettres on a sont code directe. les caratères visibles débute par 32 donc si on est sur un caratère visible (!; A; b; etc) on est donc dans le code asci
            if (car != -1){ //vérifie qu'on est pas à la fin du doc avec le numéro ascii. 
                if (new_seq) { //vérifie si on est dans une seq
                    if (car > 32){ //verifie si le numéro ascii est supérieur à 32. > 32 caratère de ponctuation
                        if (car == '@'){ //vérifie si c'est l'entête.
                            new_seq = false; 
                            std:: string H; //stocke l'entête. 
                            getline(file, H); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                            //std::cout<<"on récupère l'entête "<<H<<std::endl; 
                            set_heads(H); //ajouter l'entête à la liste head(vecteur)
                            //std::cout<<"finish adding line to the header"<< std::endl;   
                        } 
                    }
                }else{
                    if (car == '@'){ 
                        set_quality(quality); // pour vérifier que ce n'est pas une entête donc pourvoir faire le else 
                        //std::cout<<"finish adding the sequence "<<seq<<std::endl;
                        quality = "";
                        new_quality = false;   
                        new_seq = true;

                    }else{
                        if(car == '+'){
                           set_sequences(seq);
                           seq = ""; 
                           std:: string o; //permet de sauter une ligne, comme ça dès qu'on sort du if on va a la ligne suivante.
                           getline(file, o);
                           new_quality = true; 
                        }  
                        if(new_quality){
                            std:: string Q; //stocke la ligne de qualité. 
                            getline(file, Q); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                            quality+=Q; //fait le filtre et les warning
                        //std::cout<<"add sequence "<<S<<std::endl;  
                        }else{
                            std:: string S; //stocke la ligne de sequence. 
                            getline(file, S); //lit toute la ligne et même le dernier caratère et va à la ligne puis reste à la nouvelle ligne.
                            seq+=validate_sequence(S); //fait le filtre et les warning
                           //std::cout<<"add sequence "<<S<<std::endl;  
                        } 
                    }
                } 

            }
        }
    set_quality(quality);
    file.close();
    //std::cout<<"finish adding the sequence"<<seq<<std::endl;  

    }
}



