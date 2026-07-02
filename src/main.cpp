#include "FastaReader.hpp"
#include "FastqReader.hpp"
#include "Menu.hpp"
#include "SequenceAnalyzer.hpp"

int main(int argc, char* argv[]) {
    Menu menu;
    menu.print_banner();

    // Help flag: describe the tool and show the options without needing a file.
    if (argc >= 2) {
        std::string arg = argv[1];
        if (arg == "--help" or arg == "-h" or arg == "help") {
            std::cout <<
                "What it does\n"
                "  SeqForge reads a FASTA or FASTQ file, validates it, and lets you explore\n"
                "  it from an interactive menu. It can also two-bit encode sequences and map\n"
                "  reads onto a reference by seed-and-extend.\n\n"
                "How to launch\n"
                "  seqforge <file>     analyze a file directly (the path can be relative)\n"
                "  seqforge            pick a file interactively from the ./fasta_files folder\n"
                "  seqforge --help     show this help\n\n"
                "  Examples:\n"
                "    ./build/seqforge fasta_files/reads.fastq\n"
                "    ./build/seqforge data/genome.fasta\n\n"
                "  The format (FASTA or FASTQ) is detected automatically and printed. An\n"
                "  invalid file is reported with the reason and the line involved.\n\n"
                "Menu options once a file is loaded:" << std::endl;
            menu.display_options();
            std::cout <<
                "  For -mapping, put the reads file in ./fasta_files, then give its name\n"
                "  and a k-mer size (for example 11).\n" << std::endl;
            return 0;
        }
    }

    SequenceFile checker;   // used only for the file checks and format detection
    FastaReader fasta;
    FastqReader fastq;
    SequenceAnalyzer analyzer;

    // Two modes: no argument runs the interactive file selection,
    // one argument uses the given file name directly.
    std::string name;
    if (argc <= 1) {
        name = checker.run_all_checks();
    } else {
        name = argv[1];
        if (checker.check_known_file(name) != 0) {
            return 1;
        }
    }

    std::string format = checker.detect_format(name);
    std::cout << "The file is of type: " << format << std::endl;

    if (format == "FASTA") {
        std::cout << "Parsing the FASTA file..." << std::endl;
        fasta.read(name);
        if (fasta.sequences.empty()) {
            std::cerr << "No sequence could be read from the file." << std::endl;
            return 1;
        }
        std::cout << "\nThe FASTA file has been read (" << fasta.sequences.size() << " sequence(s))." << std::endl;
        analyzer.set_file(&fasta);
        analyzer.run(name, FileType::Fasta);
    } else if (format == "FASTQ") {
        std::cout << "Parsing the FASTQ file..." << std::endl;
        fastq.read(name);
        if (fastq.sequences.empty()) {
            std::cerr << "No read could be parsed from the file." << std::endl;
            return 1;
        }
        std::cout << "\nThe FASTQ file has been read (" << fastq.sequences.size() << " read(s))." << std::endl;
        analyzer.set_file(&fastq);
        analyzer.run(name, FileType::Fastq);
    } else {
        std::cerr << "Unrecognized file format. Nothing to analyze." << std::endl;
        return 1;
    }
    return 0;
}
