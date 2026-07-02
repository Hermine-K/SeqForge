#include "FastaReader.hpp"

// Removes a trailing carriage return so Windows files (CRLF) are read cleanly.
static void strip_cr(std::string &line) {
    if (!line.empty() and line.back() == '\r') {
        line.pop_back();
    }
}

void FastaReader::read(const std::string &path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: unable to open the file " << path << std::endl;
        return;
    }

    std::string line;
    std::string seq = "";
    bool have_header = false;
    std::size_t line_no = 0;

    // Reading line by line with getline consumes each line, so the parser can never
    // stay stuck on the same character (this removes the infinite loop of the old version).
    while (std::getline(file, line)) {
        line_no++;
        strip_cr(line);
        if (line.empty()) {
            continue; // a blank line has nothing to store, we skip it.
        }

        char first = line[0];
        if (first == '>' or first == ';') { // header line.
            if (have_header) {
                if (seq.empty()) {
                    std::cerr << "Warning: the header before line " << line_no
                              << " is followed by an empty sequence." << std::endl;
                }
                add_sequence(seq);
                seq = "";
            }
            for (const std::string &h : headers) { // duplicated headers are often a source of errors.
                if (h == line) {
                    std::cerr << "Warning: duplicated header at line " << line_no
                              << " (" << line << ")." << std::endl;
                    break;
                }
            }
            add_header(line);
            have_header = true;
        } else { // sequence line.
            if (!have_header) {
                std::cerr << "Error: sequence found before any header (line " << line_no
                          << "). The file is not a valid FASTA." << std::endl;
                return;
            }
            if (line.size() > 80) {
                std::cerr << "Warning: line " << line_no << " is longer than 80 characters." << std::endl;
            }
            seq += validate_sequence(line);
        }
    }

    if (have_header) {
        if (seq.empty()) {
            std::cerr << "Warning: the last header is followed by an empty sequence." << std::endl;
        }
        add_sequence(seq);
    } else {
        std::cerr << "Error: no header found, the file is not a valid FASTA." << std::endl;
    }
    file.close();
}
