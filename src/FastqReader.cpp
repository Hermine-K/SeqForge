#include "FastqReader.hpp"

// Removes a trailing carriage return so Windows files (CRLF) are read cleanly.
static void strip_cr(std::string &line) {
    if (!line.empty() and line.back() == '\r') {
        line.pop_back();
    }
}

// Reads one line and strips its carriage return. Returns false at end of file.
static bool read_line(std::ifstream &file, std::string &out) {
    if (std::getline(file, out)) {
        strip_cr(out);
        return true;
    }
    return false;
}

void FastqReader::read(const std::string &path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: unable to open the file " << path << std::endl;
        return;
    }

    std::size_t record = 0;
    std::string header;

    // A FASTQ record is: a '@' header, one or more sequence lines, a '+' separator,
    // then one or more quality lines whose total length matches the sequence.
    // We read the sequence until the '+' line, then read quality until it reaches the
    // sequence length. This handles both single-line and multi-line FASTQ, and quality
    // characters that happen to be '@' or '+' (they are counted, not treated as markers).
    while (read_line(file, header)) {
        if (header.empty()) {
            continue; // tolerate blank lines between records.
        }
        if (header[0] != '@') {
            std::cerr << "Error: record " << record + 1 << " does not start with '@'. "
                      << "The file is not a valid FASTQ." << std::endl;
            return;
        }
        record++;

        // Accumulate the sequence lines until the '+' separator.
        std::string seq, line;
        bool found_separator = false;
        while (read_line(file, line)) {
            if (!line.empty() and line[0] == '+') { found_separator = true; break; }
            seq += line;
        }
        if (!found_separator) {
            std::cerr << "Error: record " << record << " has no '+' separator line." << std::endl;
            return;
        }

        // Accumulate the quality lines until they cover the whole sequence.
        std::string qual, qline;
        while (qual.size() < seq.size() and read_line(file, qline)) {
            qual += qline;
        }
        if (qual.size() != seq.size()) {
            std::cerr << "Warning: record " << record << " has a sequence (" << seq.size()
                      << ") and a quality string (" << qual.size() << ") of different lengths." << std::endl;
        }

        add_header(header);
        add_sequence(validate_sequence(seq));
        add_quality(qual);
    }

    if (record == 0) {
        std::cerr << "Error: no record found, the file is not a valid FASTQ." << std::endl;
    }
}
