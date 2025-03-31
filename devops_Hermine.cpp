//#include<iostream
#include "verification_HK.hpp"
#include "verification_FASTA.hpp"
#include "verification_FASTQ.hpp"
#include "userPrompt.hpp"
#include "Analyse_HK.hpp"
#include "Analyse_FASTA.hpp"
#include "Analyse_FASTQ.hpp"




int main(int argc, char *argv[]) {

   verification_HK verif; 
   verification_FASTA verif_f; 
   verification_FASTQ verif_q; 
   Analyse_HK* an = nullptr; // On crée un pointeur vers la classe mère Analyse_HK.(car elle contient une fonction virtuel). Au début, ce pointeur ne pointe vers rien (nullptr = pointeur nul).
   verif.new_project_fasta();
   if (argc <= 1){
      std::string name_file = verif.all_verifications();
      std::cout<<"verification faite sur le nom "<<name_file<<std::endl;
      std::string type_of_file = verif.what_is_my_file(name_file);
      std::cout<<"le fichier est un "<<type_of_file<<std::endl;
      if (type_of_file== "FASTA"){
         std::cout<<"Start parsing fasta file"<<std::endl;
         verif_f.read_fasta(name_file);
         an = new Analyse_FASTA(); // Puis on crée dynamiquement un objet de la classe Analyse_FASTA.  (hérite de Analyse_HK) et on l’associe au pointeur 'an'.
         std::cout<<"\n La vérification de votre fichier FASTA est terminée."<<std::endl;
         an->analyse(); // On appelle la méthode 'analyse()' via le pointeur 'an'. Grâce au polymorphisme, cela exécutera la version appropriée de display_menu() sans avoir besoin d'un 'if'. 
         delete an; // On libère la mémoire allouée dynamiquement avec 'new'.  C’est important en C++ pour éviter les fuites mémoire.

      }else if (type_of_file== "FASTQ"){
         std::cout<<"Start parsing fastq file"<<std::endl;
         verif_q.read_fastq(name_file);
         an = new Analyse_FASTQ();
         std::cout<<"\n La vérification de votre fichier FASTQ est terminée."<<std::endl;
         an->analyse();
         delete an;
      }


   }else if(argc == 2){
      std::string name_file = argv[1]; 
      int error_value = verif.all_verifications_know_file(name_file);
      if (error_value == 0){
         std::cout<<"verification faite sur le nom grâce à all_verification_know_file  "<<name_file<<std::endl;
         std::string type_of_file = verif.what_is_my_file(name_file);
         std::cout<<"le fichier est un "<<type_of_file<<std::endl;
         if (type_of_file== "FASTA"){
            std::cout<<"Start parsing fasta file"<<std::endl;
            verif_f.read_fasta(name_file);
            an = new Analyse_FASTA(); 
            std::cout<<"\n La vérification de votre fichier FASTA est terminée."<<std::endl;
            an->analyse();
            delete an;
            
         }else if (type_of_file== "FASTQ"){
            std::cout<<"Start parsing fastq file"<<std::endl;
            verif_q.read_fastq(name_file);
            an = new Analyse_FASTQ();
            std::cout<<"\n La vérification de votre fichier FASTAQ est terminée."<<std::endl;
            an->analyse();
            delete an;
         }

      }
      

   }
   return 0;// always put it at the end
}

