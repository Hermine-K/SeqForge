#include<iostream>

//Procedure
void new_project_fasta(){
 std::cout<<"Hello Hermine. let's analyse a new fasta file "<<std::endl; // like print (affichage)
 }

//function , enter name fasta
std::string enter_name_fasta(){
    std::cout <<"Please give the name of the fasta file with extention "<<std::endl;
    std::string name_fasta; //create a variable to put the name fasta file 
    std::cin>>name_fasta; //asks the user to enter the name of the file and "">>"" shows where to enter the string (name). 
    return name_fasta; 

}

//Function that check if the file is a fasta file(extention .fasta, .fas, .fastq)
std::string extention_fasta(std::string name_fasta){
    if (!(name_fasta.ends_with(".fasta") or name_fasta.ends_with(".fas") or name_fasta.ends_with(".fastq")));{
        std::cerr<<"Error this is not a fasta; please enter a fasta file.";
    }
}


int main() {
   new_project_fasta();
   //enter_name_fasta(); just executes the function without saving it
   //std::cout<<enter_name_fasta(); //with std you display the result instead of just putting the file in the name_fasta variable
   std::string fasta_name = enter_name_fasta(); //here I'm creating a variable that puts the result of the function  
   //std::cout<<fasta_name;
   extention_fasta(fasta_name);
   return 0;// always put it at the end
}
