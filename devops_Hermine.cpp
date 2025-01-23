//#include<iostream
#include "verification_HK.hpp"


int main() {

   verification_HK verif; 
   verif.new_project_fasta();
   //enter_name_fasta(); just executes the function without saving it
   //std::cout<<enter_name_fasta(); //with std you display the result instead of just putting the file in the name_fasta variable
   //std::string fasta_name = verif.enter_name_fasta(); //here I'm creating a variable that puts the result of the function  
   //std::cout<<fasta_name;
   //verif.extention_fasta(fasta_name);
   verif.all_verifications();
   return 0;// always put it at the end
}
