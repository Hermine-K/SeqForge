//#include<iostream
#include "verification_HK.hpp"
#include "verification_FASTA.hpp"


int main(int argc, char *argv[]) {

   verification_HK verif; 
   verification_FASTA verif_f; 
   //verification_FASTQ verif_q; 
   verif.new_project_fasta();
   std::string name_file = verif.all_verifications();
   std::cout<<"verif faite sur le nom "<<name_file<<std::endl;
   std::string type_of_file = verif.what_is_my_file(name_file);
   std::cout<<"le fichier est un "<<type_of_file<<std::endl;
   if (type_of_file== "FASTA"){
       std::cout<<"je rentre dans le if"<<std::endl;
      verif_f.read_fasta(name_file);
   }
  //if (type_of_file== "FASTQ"){

      //veriif_q.lire_file(name_file);
   //}

   
   return 0;// always put it at the end
}

