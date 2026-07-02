#include "Menu.hpp"
#include <iostream>
#include <string>

// ASCII-art banner (figlet "slant" font).
static const char *BANNER = R"(
   _____            ______
  / ___/___  ____ _/ ____/___  _________ ____
  \__ \/ _ \/ __ `/ /_  / __ \/ ___/ __ `/ _ \
 ___/ /  __/ /_/ / __/ / /_/ / /  / /_/ /  __/
/____/\___/\__, /_/    \____/_/   \__, /\___/
             /_/                 /____/
)";

static const int WIDTH = 74; // inner text width of the menu box

static void box_top() {
    std::string bar;
    for (int i = 0; i < WIDTH + 2; ++i) bar += "\u2500";
    std::cout << "\u256D" << bar << "\u256E\n";
}
static void box_bottom() {
    std::string bar;
    for (int i = 0; i < WIDTH + 2; ++i) bar += "\u2500";
    std::cout << "\u2570" << bar << "\u256F\n";
}
static void box_line(const std::string &s) {
    int pad = WIDTH - static_cast<int>(s.size());
    if (pad < 0) pad = 0;
    std::cout << "\u2502 " << s << std::string(pad, ' ') << " \u2502\n";
}

void Menu::print_banner() {
    std::cout << BANNER << "\n";
    std::cout << "  A C++ toolkit for FASTA/FASTQ: validation, analysis, two-bit encoding,\n";
    std::cout << "  k-mer indexing and read mapping.            version 0.3.2\n" << std::endl;
}

void Menu::display_options() {
    std::cout << "\n";
    box_top();
    box_line("SeqForge menu");
    box_line("");
    box_line("File");
    box_line("  -countseq       count the number of sequences");
    box_line("  -headers        display the headers");
    box_line("  -stats          length and GC content summary");
    box_line("");
    box_line("Sequence");
    box_line("  -sequence       display the stored sequences");
    box_line("  -length         length of a sequence (asks for an index)");
    box_line("  -total_length   total length of all sequences");
    box_line("  -complement     complement of a sequence (asks for an index)");
    box_line("  -table_suffix   suffix and LCP table of a sequence");
    box_line("");
    box_line("FASTQ only");
    box_line("  -quality_score  filter a read by its quality scores");
    box_line("");
    box_line("Encoding and mapping");
    box_line("  -encode         two-bit encode a sequence, show the packed size");
    box_line("  -mapping        map reads from another file onto this reference");
    box_line("");
    box_line("  -help    show this menu again          -quit    exit the program");
    box_bottom();
    std::cout << "\n";
}

std::string Menu::ask_choice() {
    std::string choice;
    std::cout << "Enter your option: ";
    std::cin >> choice;
    return choice;
}
