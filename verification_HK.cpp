

#include "verification_HK.hpp" //include what's in hpp here  

//using namespace std; I prefer not to use it so as not to create a name conflict

//Procedure
void verification_HK:: new_project_fasta(){
 std::cout<<"Hello Hermine. let's analyse a new fasta file "<<std::endl; // like print.
 }


//Procedure to put the file in a good repertory
void verification_HK::fasta_repertory() {
    std::string folder_name = "fasta_files"; //variable with the name of repertory

    if (!std::filesystem::exists(folder_name)) { //make sure the repertory exists 
        std::cerr << "The folder 'fasta_files' doesn't exist. Creating it now. Please put your file in this folder." << std::endl;
        std::filesystem::create_directory(folder_name); //creation of repertory
    } else {
        std::cout << "The folder 'fasta_files' exists. Please put your file in this folder." << std::endl;
    }
}

//function , enter name fasta
std::string verification_HK:: enter_name_fasta(){
    std::cout <<"Please enter the name of the file with (it must be in 'fasta_files'): "<<std::endl;
    std::string name_fasta; //create a variable to put the name fasta file 
    std::cin>>name_fasta; //asks the user to enter the name of the file and "">>"" shows where to enter the string (name). 
    std::string full_path = "./fasta_files/" + name_fasta; // Automatically adds the path to the fasta_files/ folder
    std::cout << "The complete path used :" << full_path << std::endl;
    return full_path; //Returns the variable containing the file/
}

//Function that check if the file exists
bool verification_HK:: exists_fasta(const std::string &file_path){ //The const guarantees that the object will not be modified and the & is used to pass the object by reference.
    return std::filesystem::exists(file_path);//checks if the file exists
        
}

//Function that check if the file is a fasta file(extention .fasta, .fas, .fastq)
bool verification_HK:: extention_fasta(std::string name_fasta){ //parameter a variable containing the name of the file
    bool correct_extention = true; //
    if (!(name_fasta.ends_with(".fasta") or name_fasta.ends_with(".fas") or name_fasta.ends_with(".fastq"))){ //checks if the extension is correct
        std::cerr << "Error: the file extension must be .fasta, .fa or .fastq." << std::endl; 
        correct_extention = false; //if it's not the right extension, the boolean variable is set to false
    }
    return correct_extention; 
}

//Function that check if th file is empty. 
bool verification_HK::fasta_empty(const std::string &name_file) {
    std::ifstream file(name_file); // ifstream is used to open a file and store its content.

    if (!file.is_open()) { // Check if the file has been successfully opened.
        std::cerr << "Error: Unable to open the file " << name_file << std::endl;
        return true; // If the file cannot be opened, consider it empty.
    }

    return file.peek() == EOF; // The peek() method checks the next character without consuming it. If it returns EOF (End Of File), the file is empty.
}

//function that check fasta 
std::string verification_HK:: what_is_my_file(std::string name_fasta){
    if (name_fasta.ends_with(".fasta") or name_fasta.ends_with(".fa")){
        return "FASTA";
    }
    
    if (name_fasta.ends_with(".fastq")){
        return "FASTQ";
    }
return "NONE";
}
//request all checks 
std::string verification_HK::all_verifications(){
    fasta_repertory(); //Checks or creates the ‘fasta_files’ folder.

    bool condition_verif; //creating a Boolean variable.
    condition_verif = false; //this variable is basic false.
    std::string name_fasta = "empty"; //create a variable with ‘empty’ in it.

    while (!condition_verif){ //As long as !condition_verif is true (i.e. condition_verif is false).

        name_fasta = enter_name_fasta(); //This variable stores the name of the document from the enter_name_fasta function.

        if (!exists_fasta(name_fasta)) {
            std::cerr << "Error: The file does not exist in 'fasta_files'. Please try again." << std::endl;
            continue; //Allows you to resume the while (not stopping the program until you have the right one). It exits the if and resumes the loop.
        }

        if (!extention_fasta(name_fasta)){ 
            continue; 

        }
        if (fasta_empty(name_fasta)){
            std::cerr << "Error: The file is empty." << std::endl;
            continue;
        }
        
    
        // If all checks pass.
        //condition_verif = true; 
        break;//Exit the loop.
    }
    
    return name_fasta; 
}

//faire une fonction vérification 2 qui prend en paramètre le nom du fichier et qui n'utilise pas enter_name_fasta

