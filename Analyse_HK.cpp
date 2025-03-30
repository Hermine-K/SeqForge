#include "Analyse_HK.hpp"

void Analyse_HK::countseq(){
    verification_HK verif; 
    int seqcount = verif.sequences.size(); 
    std::cout<<"On a : "<<seqcount<<"dans le fichier"<<endl;
}

void Analyse_HK::length(){
    verification_HK verif;
    std::cout<<"Veuillez indiquer l'indice de la séquence souhaiter"<<endl;  
    int indice
    std::cin>>indice; 
    int length = verif.sequences[indice-1].size(); 
    std::cout<<"la longueur de la séquence est : "<<length<<endl; 
}

void Analyse_HK::show_headers(){
    verification_HK verif; 
    std::vector<std::string> list_of_headers = verif.heads;
    for(int i=0; i<=list_of_headers.size(); ++i){
        std::cout<<i+1<<list_of_headers[i]<<endl; 
    } 

}

void Analyse_HK::show_sequences(){
    verification_HK verif; 
    std::vector<std::string> list_of_sequence = verif.sequences;
    for(int i=0; i<=list_of_sequence.size(); ++i){
        std::cout<<i+1<<list_of_sequence[i]<<endl; 
    } 
}

void Analyse_HK::total_length(){
    verification_HK verif; 
    std::vector<std::string> list_of_sequence = verif.sequences;
    int total_length = 0; 
    for(int i=0; i<=list_of_sequence.size(); ++i){
        total_length += list_of_sequence[i].size;
    }
    std::cout<<"La longueur total des séquences est de : "<<total_length<<endl; 
}    

//Analyse proprement dit 

void Analyse_HK::analyse(){
    userPrompt user; 
    bool programme = true; 
    std::string options; 
    while(programme){
        user.display_common_options;
        option = user.ask_user_choice;
        
        if(options == "-countseq"){
            countseq(); 

        }else if(options == "-length <index>"){
            length(); 

        }else if(options == "-headers"){
            show_headers(); 
            
        }else if(options == "-sequence <index>"){
            show_sequences(); 
        }else if(options == "-total_length "){
            total_lenght(); 
        }
    }

}