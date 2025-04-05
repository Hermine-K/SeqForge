#include "verification_FASTA.hpp"
#include "verification_FASTQ.hpp"
#include "userPrompt.hpp"
#include "Analyse_HK.hpp"

int main(int argc, char *argv[]) { // Create an object to handle FASTA file verification (reads headers and sequences)
   verification_HK verif;
   verification_FASTA verif_f; // Create an object to handle FASTQ file verification (reads headers, sequences, and quality lines)
   verification_FASTQ verif_q; // Create an object responsible for analyzing the data, whether it's FASTA or FASTQ
   Analyse_HK an;

   verif.new_project_fasta();
   if (argc <= 1){// If the user did not pass a filename as an argument
      std::string name_file = verif.all_verifications();
      std::cout<<"name check "<<name_file<<std::endl;
      std::string type_of_file = verif.what_is_my_file(name_file);
      std::cout<<"The file is of type:  "<<type_of_file<<std::endl;
      if (type_of_file== "FASTA"){
         std::cout<<"Start parsing fasta file"<<std::endl;
         verif_f.read_fasta(name_file);
         std::cout<<"\n The verification of your FASTA file is complete."<<std::endl;
         an.set_verif(&verif_f); // Send the verification results to the analysis module
         an.analyse(name_file, fileType::FASTA);//use pointeur

      }else if (type_of_file== "FASTQ"){
         std::cout<<"Start parsing fastq file"<<std::endl;
         verif_q.read_fastq(name_file);
         std::cout<<"\nThe verification of your FASTQ file is complete."<<std::endl;
         an.set_verif(&verif_q); // Send the verification results to the analysis module
         an.analyse(name_file, fileType::FASTQ);
      }


   }else if(argc == 2){
      std::string name_file = argv[1]; 
      int error_value = verif.all_verifications_know_file(name_file);
      if (error_value == 0){
         std::cout<<"name verification using  all_verification_know_file  "<<name_file<<std::endl;
         std::string type_of_file = verif.what_is_my_file(name_file);
         std::cout<<"The file is of type "<<type_of_file<<std::endl;
         if (type_of_file== "FASTA"){
            std::cout<<"Start parsing fasta file"<<std::endl;
            verif_f.read_fasta(name_file);
            std::cout<<"\n The verification of your FASTA file is complete."<<std::endl;
            an.set_verif(&verif_f); 
            an.analyse(name_file, fileType::FASTA);
            
         }else if (type_of_file== "FASTQ"){
            std::cout<<"Start parsing fastq file"<<std::endl;
            verif_q.read_fastq(name_file);
            std::cout<<"\n The verification of your FASTQ file is complete."<<std::endl;
            an.set_verif(&verif_q); 
            an.analyse(name_file, fileType::FASTQ);
         }

      }
      

   }
   return 0;// always put it at the end
}

