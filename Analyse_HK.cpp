
// This file contains all the analysis functions used for FASTA and FASTQ files.
// It includes methods to show headers, sequences, lengths, quality filtering, etc.

#include "Analyse_HK.hpp"
#include "userPrompt.hpp"
#include <iostream>
#include <algorithm>

void Analyse_HK::set_verif(verification_HK* v) {
    verif = v;
}


void Analyse_HK::display_menu(fileType type) {
    userPrompt user;
    user.display_options();  // Affiche le menu unique

    if (type == fileType::FASTQ) {
        std::cout<<"\n╭────────────────────────────── Options spécifiques FASTQ ──────────────────╮" << std::endl;
        std::cout << "| -quality_score   : Affiche les scores de qualité pour une séquence        |\n" << std::endl;
        std::cout << "| -all_fastq       : Affiche tout le contenu du fichier FASTQ               |\n" << std::endl;
        std::cout << "╰───────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
    } else if (type == fileType::FASTA) {
        std::cout<<"\n╭────────────────────────────── Options spécifiques FASTA ──────────────────╮" << std::endl;
        std::cout << "| -all_fasta       : Affiche tout le contenu du fichier FASTA               |\n" << std::endl;
        std::cout << "╰───────────────────────────────────────────────────────────────────────────╯\n" << std::endl;
    }
}

void Analyse_HK::countseq(){ // Count and display the number of sequences in the file
    int seqcount = verif->sequences.size(); 
    std::cout<<"Total number of sequences: " <<seqcount<<std::endl;
}

void Analyse_HK::length(){// Show the length of a specific sequence by its index
    std::cout<<"Enter the index of the sequence: "<<std::endl;  
    int indice; 
    std::cin>>indice; 
    int length = verif->sequences[indice-1].size(); 
    std::cout<<"Length: "<<length<<std::endl; 
}

void Analyse_HK::show_headers() { // Show all the sequence headers
    const std::vector<std::string>& headers = verif->heads;
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << "Header " << i + 1 << " : " << headers[i] << std::endl;
    }
}

void Analyse_HK::show_sequences() { // Show all sequence 
    const std::vector<std::string>& sequences = verif->sequences;
    for (size_t i = 0; i < sequences.size(); ++i) {
        std::cout << "Séquence " << i + 1 << " : " << sequences[i] << std::endl;
    }
}


void Analyse_HK::total_length(){ // Calculate and display the total length of all sequences combined
    std::vector<std::string> list_of_sequence = verif->sequences;
    int total_length = 0; 
    for(int i=0; i < list_of_sequence.size(); ++i){
        total_length += list_of_sequence[i].size();
    }
    std::cout<<"Total length of all sequences: "<<total_length<<std::endl; 
}    

void Analyse_HK::show_complement(){// Generate and display the complementary strand of a sequence
    std::cout<<"Enter the index of the sequence: "<<std::endl; 
    int indice;
    std::cin>>indice; 
    std::string sequence = verif->sequences[indice - 1]; 
    std::string complement; 
    for (char base : sequence){
        switch (base){ 

            case 'A': complement += 'T'; break;
            case 'T': complement += 'A'; break;
            case 'C': complement += 'G'; break;
            case 'G': complement += 'C'; break;
            default:  complement += 'N'; break; 
        }
    } 
    std::cout<<"Complementary strand: "<<indice<<" : "<<complement<<std::endl; 
}


void Analyse_HK::show_all_fasta() { 
    std::vector<std::string> headers = verif->heads; 
    std::vector<std::string> sequences = verif->sequences;
    std::cout << " Contenu du fichier FASTA :\n" << std::endl;
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << headers[i] << "\n" << sequences[i] << "\n" << std::endl;
    }
}

void Analyse_HK::show_all_fastq() {
    std::vector<std::string> headers = verif->heads; 
    std::vector<std::string> sequences = verif->sequences;
    std::vector<std::string> quality = verif->quality; 
    std::cout << " Contenu du fichier FASTQ :\n" << std::endl;
    for (size_t i = 0; i < headers.size(); ++i) {
        std::cout << headers[i] << "\n" << sequences[i] << "\n" << "+" << "\n" << quality[i] << "\n" << std::endl;
    }
}

void Analyse_HK::quality_score(int encoding, int seq_index, int min_quality) { //score de qualité suivant la méthode de séquençage
     if (seq_index < 1 || seq_index > verif->sequences.size()) {
        std::cerr << "Invalid sequence index." << std::endl;
        return;
    }

    if (min_quality > 40 || min_quality < 0) {
        std::cerr << "Error: quality score should be between 0 and 40." << std::endl;
        return;
    }

    std::string quality_line = verif->quality[seq_index - 1];
    std::string sequence = verif->sequences[seq_index - 1];
    std::string filtered_sequence = "";

    int offset = 33; // default: Sanger
    if (encoding == 2) offset = 64; // Illumina 1.3+

    for (size_t i = 0; i < quality_line.size(); ++i) {
        int score = static_cast<int>(quality_line[i]) - offset;
        if (score >= min_quality) {
            filtered_sequence += sequence[i];
        } else {
            filtered_sequence += '-';
        }
    }

    std::cout << "Filtered sequence:\n" << filtered_sequence << std::endl;
}    

void Analyse_HK::show_suffix_table() { // Display the suffix table (list of all suffixes of a sequence)
    // Code based on Professor Alban Mancheron's approach
    int index;
    std::cout << "Enter the index of the sequence: ";
    std::cin >> index;

    if (index < 1 or  index > verif->sequences.size()) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    // Retrieve the sequence + add the $ terminal symbol
    std::string s = verif->sequences[index - 1] + "$";
    int n = s.length();

    // Construction of the suffix table (indices 0 to n-1)
    std::vector<int> suffixes(n);
    for (int i = 0; i < n; ++i) {
        suffixes[i] = i;
    }

    // Lexicographic comparison function between two suffixes
    auto compareSuffix = [&](int i, int j) {
        while (i < n && j < n) {
            if (s[i] != s[j])
                return s[i] < s[j];
            i++;
            j++;
        }
        return i == n;
    };

    // Function for calculating the Longest Common Prefix (LCP) between two suffixes
    auto longestCommonPrefix = [&](int i, int j) {
        int lcp = 0;
        while (i + lcp < n && j + lcp < n && s[i + lcp] == s[j + lcp]) {
            lcp++;
        }
        return lcp;
    };

    // Sort suffixes by lexicographical order
    std::sort(suffixes.begin(), suffixes.end(), compareSuffix);

    // Displaying the suffix and LCP table
    std::cout << "\nTable of suffixes\n" <<std::endl;
    std::cout << " Rang |  SA[i]  |  LCP  | Suffixe\n";
    std::cout << "---------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        int sa = suffixes[i];
        int lcp = (i == 0) ? 0 : longestCommonPrefix(sa, suffixes[i - 1]);
        std::cout << "  " << i << "   |   " << sa << "    |  " << lcp << "   | " << s.substr(sa) << "\n";
    }
}







//Analyse  

void Analyse_HK::analyse(const std::string& name_file, fileType t){//display userPrompts options
    type = t;
    userPrompt user; 
    bool programme = true; 
    std::string options;  
    while(programme){
        display_menu(type); 
        options = user.ask_user_choice();
        
        if(options == "-countseq"){
            countseq(); 

        }else if(options == "-length"){
            length(); 

        }else if(options == "-headers"){
            show_headers(); 
            
        }else if(options == "-sequence"){
            show_sequences(); 

        }else if(options == "-total_length"){
            total_length(); 

        }else if (options == "-complement"){
            show_complement(); 
        
        }else if(options == "-all_fasta" && type == fileType::FASTA){
            show_all_fasta();
        
        }else if(options == "-all_fastq" && type == fileType::FASTQ){
            show_all_fastq();

        }else if(options == "-quality_score" && type == fileType::FASTA){
             std::cout << "Cette option n'est disponible que pour les fichiers FASTQ.\n";

        }else if(options == "-quality_score"){

            std::cout<<"Please select the filter that you're using:"<<std::endl;
            std::cout<<"1. Sanger with Phred+33 (ASCII 33-73)"<<std::endl;
            std::cout<<"2. Illumina 1.3+ with Phred+64 (ASCII 64-104)"<<std::endl;
            std::cout<<"3. Illumina 1.8+ with Phred+33 (ASCII 33-74)"<<std::endl;

            int encoding;
            std::cin >> encoding;

            std::cout<<"Give the index of the sequence you want to filter : ";
            int seq_index;
            std::cin >> seq_index;

            std::cout<<"Give the minimal quality score you want (0 - 40) : ";
            int min_quality;
            std::cin >> min_quality;

            quality_score(encoding, seq_index, min_quality);    

        }else if(options == "-table_suffix"){ 
            show_suffix_table(); 
            
        }else if(options == "-mapping"){ 
            std::cout<<"Nous n'avons pas eu le temps de faire le mapping"<<std::endl; 
            
        }else if(options == "-quit"){
            std::cout << "\n Merci d'avoir utilisé notre programme. À bientôt !" << std::endl;
            programme = false;
        } else {
         std::cerr << "Error : option invalide" << std::endl;
        } 
    }

    


}