

#include "verification_HK.hpp" //on inclut ce qu'il y a dans hpp ici  


//Procedure
void verification_HK:: new_project_fasta(){
 std::cout<<"Hello Hermine. let's analyse a new fasta file "<<std::endl; // like print (affichage)
 }

//function , enter name fasta
std::string verification_HK:: enter_name_fasta(){
    std::cout <<"Please give the name of the fasta file with extention "<<std::endl;
    std::string name_fasta; //create a variable to put the name fasta file 
    std::cin>>name_fasta; //asks the user to enter the name of the file and "">>"" shows where to enter the string (name). 
    return name_fasta; 

}

//Function that check if the file is a fasta file(extention .fasta, .fas, .fastq)
bool verification_HK:: extention_fasta(std::string name_fasta){ //
    bool correct_extention = true; //
    if (!(name_fasta.ends_with(".fasta") or name_fasta.ends_with(".fas") or name_fasta.ends_with(".fastq"))){ //
        std::cerr << "Error: This is not a valid FASTA file. Please enter a file with .fasta, .fas, or .fastq extension: " << std::endl; //
        correct_extention = false; //
    }
    return correct_extention; //
}

bool verification_HK:: fasta_empty(std::string name_file){
    std::ifstream file(name_file); //ifstream permet d'ouvrir un fichier et de stocker ce qu'il y a l'intérieur dans une variable 
    return file.peek() == EOF; //peek() est une méthode qui ermet de regarder le caractère suivant dans le fichier sans le consommer.peek() renvoie alors la constante EOF (End of File, fin du fichier
    
}
//demande toute les vérifications 

std::string verification_HK::all_verifications(){
    bool condition_verif; //création d'unvariable booléenne 
    condition_verif = false; //cette variable est false de base
    std::string name_fasta = "vide"; 
    while (!condition_verif){ //Tant cette variable reste fausse (donc la condition reste fausse)
        std::string name_fasta = enter_name_fasta(); //création d'une variable qui stocke le nom du document à partir de la fontion enter_name_fasta
        if (!extention_fasta(name_fasta)){ //
            continue; //permet de reprendre le while(pas arrêté le programme jusqu'à avoir le bon). Il sort du il et reprend la boucle

        }
        if (fasta_empty(name_fasta)){
            std::cerr<<"Error : The file faste is empty"<<std::endl;
            continue;
        }
    

    }
    return name_fasta; 
}

//Function that check if if the fasta is complete