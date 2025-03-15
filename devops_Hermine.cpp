//#include<iostream
#include "verification_HK.hpp"
#include "verification_FASTA.hpp"


int main(int argc, char *argv[]) {

   verification_HK verif; 
   verification_FASTA verif_f; 
   //verification_FASTQ verif_q; 
   verif.new_project_fasta();
   if (argc <= 1){
      std::string name_file = verif.all_verifications();
      std::cout<<"verification faite sur le nom "<<name_file<<std::endl;
      std::string type_of_file = verif.what_is_my_file(name_file);
      std::cout<<"le fichier est un "<<type_of_file<<std::endl;
      if (type_of_file== "FASTA"){
         std::cout<<"Start parsing fasta file"<<std::endl;
         verif_f.read_fasta(name_file);
      }
      //if (type_of_file== "FASTQ"){

      //veriif_q.lire_file(name_file);
      //}


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
      }
      //if (type_of_file== "FASTQ"){

      //veriif_q.lire_file(name_file);
      //}

      }
      

   }
   
   
   return 0;// always put it at the end
}

