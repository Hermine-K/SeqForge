#include "SequenceFile.hpp"

// Creates the data directory if it does not exist yet.
void SequenceFile::ensure_directory() {
    const std::string folder = "fasta_files";
    if (!std::filesystem::exists(folder)) {
        std::cerr << "The folder '" << folder << "' does not exist. Creating it now. "
                  << "Please put your file in this folder." << std::endl;
        std::filesystem::create_directory(folder);
    } else {
        std::cout << "The folder '" << folder << "' exists. Please put your file in this folder." << std::endl;
    }
}

std::string SequenceFile::ask_file_name() {
    std::cout << "Please enter the name of the file (it must be inside 'fasta_files'): " << std::endl;
    std::string name;
    std::cin >> name;
    std::string full_path = "./fasta_files/" + name;
    std::cout << "Full path used: " << full_path << std::endl;
    return full_path;
}

bool SequenceFile::file_exists(const std::string &path) {
    return std::filesystem::exists(path);
}

bool SequenceFile::has_valid_extension(const std::string &name) {
    if (name.ends_with(".fasta") or name.ends_with(".fa") or name.ends_with(".fas")
        or name.ends_with(".fastq") or name.ends_with(".fq")) {
        return true;
    }
    std::cerr << "Error: the file extension must be .fasta, .fa, .fas, .fastq or .fq." << std::endl;
    return false;
}

bool SequenceFile::is_empty(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: unable to open the file " << path << std::endl;
        return true;
    }
    return file.peek() == EOF;
}

std::string SequenceFile::detect_format(const std::string &name) {
    std::ifstream input(name);
    if (!input.is_open()) {
        std::cerr << "Error: unable to open the file to identify its format." << std::endl;
        return "NONE";
    }
    // Look at the first non-empty line, so leading blank lines do not fool the detection.
    std::string line;
    char first = 0;
    while (std::getline(input, line)) {
        if (!line.empty() and line.back() == '\r') line.pop_back();
        if (!line.empty()) { first = line[0]; break; }
    }

    if (name.ends_with(".fasta") or name.ends_with(".fa") or name.ends_with(".fas")) {
        if (first == ';' or first == '>') return "FASTA";
        std::cerr << "Error: the file has a FASTA extension but does not start with '>' or ';'." << std::endl;
    }
    if (name.ends_with(".fastq") or name.ends_with(".fq")) {
        if (first == '@') return "FASTQ";
        std::cerr << "Error: the file has a FASTQ extension but does not start with '@'." << std::endl;
    }
    return "NONE";
}

std::string SequenceFile::run_all_checks() {
    ensure_directory();
    std::string name;
    while (true) {
        name = ask_file_name();
        if (!file_exists(name)) {
            std::cerr << "Error: the file does not exist in 'fasta_files'. Please try again." << std::endl;
            continue;
        }
        if (!has_valid_extension(name)) {
            continue;
        }
        if (is_empty(name)) {
            std::cerr << "Error: the file is empty." << std::endl;
            continue;
        }
        break;
    }
    return name;
}

int SequenceFile::check_known_file(const std::string &name) {
    if (!file_exists(name)) {
        std::cerr << "Error: the file does not exist: " << name << std::endl;
        return -1;
    }
    if (!has_valid_extension(name)) {
        return -1;
    }
    if (is_empty(name)) {
        std::cerr << "Error: the file is empty." << std::endl;
        return -1;
    }
    return 0;
}

std::string SequenceFile::validate_sequence(const std::string &line) {
    const std::string iupac = "ACGTNRYWSKMBDHV-.acgtnrywskmbdhv-.";
    std::string cleaned;
    for (std::size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c < 32 or c > 126 or iupac.find(c) == std::string::npos) {
            std::cerr << "Invalid character '" << c << "' (ASCII " << static_cast<int>(c)
                      << ") at position " << i + 1 << " in sequence: " << line
                      << " (replaced by '-')" << std::endl;
            cleaned.push_back('-');
        } else {
            cleaned.push_back(c);
        }
    }
    return cleaned;
}

void SequenceFile::add_header(const std::string &h)   { headers.push_back(h); }
void SequenceFile::add_sequence(const std::string &s) { sequences.push_back(s); }
void SequenceFile::add_quality(const std::string &q)  { quality.push_back(q); }
