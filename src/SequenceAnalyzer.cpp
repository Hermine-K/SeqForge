// Analysis functions for FASTA and FASTQ files: headers, sequences, lengths,
// complement, suffix table, quality filtering, and the interactive menu loop.

#include "SequenceAnalyzer.hpp"
#include "Menu.hpp"
#include "FastaReader.hpp"
#include "FastqReader.hpp"
#include "TwoBitEncoder.hpp"
#include "Mapper.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

void SequenceAnalyzer::set_file(SequenceFile* f) {
    file = f;
}

void SequenceAnalyzer::show_menu(FileType t) {
    Menu menu;
    menu.display_options();

    if (t == FileType::Fastq) {
        std::cout << "FASTQ specific options:" << std::endl;
        std::cout << "| -quality_score : display the quality scores of a sequence |" << std::endl;
        std::cout << "| -all_fastq     : display the whole content of the FASTQ file |\n" << std::endl;
    } else {
        std::cout << "FASTA specific options:" << std::endl;
        std::cout << "| -all_fasta     : display the whole content of the FASTA file |\n" << std::endl;
    }
}

void SequenceAnalyzer::count_sequences() {
    std::cout << "Total number of sequences: " << file->sequences.size() << std::endl;
}

void SequenceAnalyzer::sequence_length() {
    std::cout << "Enter the index of the sequence: " << std::endl;
    int index;
    std::cin >> index;
    if (index < 1 or index > static_cast<int>(file->sequences.size())) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }
    std::cout << "Length: " << file->sequences[index - 1].size() << std::endl;
}

void SequenceAnalyzer::show_headers() {
    const std::vector<std::string> &headers = file->headers;
    for (std::size_t i = 0; i < headers.size(); ++i) {
        std::cout << "Header " << i + 1 << " : " << headers[i] << std::endl;
    }
}

void SequenceAnalyzer::show_sequences() {
    const std::vector<std::string> &sequences = file->sequences;
    for (std::size_t i = 0; i < sequences.size(); ++i) {
        std::cout << "Sequence " << i + 1 << " : " << sequences[i] << std::endl;
    }
}

void SequenceAnalyzer::total_length() {
    std::size_t total = 0;
    for (const std::string &s : file->sequences) {
        total += s.size();
    }
    std::cout << "Total length of all sequences: " << total << std::endl;
}

void SequenceAnalyzer::show_stats() {
    const std::vector<std::string> &seqs = file->sequences;
    if (seqs.empty()) {
        std::cerr << "No sequence is loaded." << std::endl;
        return;
    }
    std::size_t n = seqs.size();
    std::size_t total = 0;
    std::size_t min_len = std::numeric_limits<std::size_t>::max();
    std::size_t max_len = 0;
    std::size_t gc = 0;      // G or C bases
    std::size_t acgt = 0;    // A, C, G or T bases (ambiguous bases are ignored for GC)
    std::vector<std::size_t> lengths;
    lengths.reserve(n);

    for (const std::string &s : seqs) {
        lengths.push_back(s.size());
        total += s.size();
        if (s.size() < min_len) min_len = s.size();
        if (s.size() > max_len) max_len = s.size();
        for (char c : s) {
            switch (c) {
                case 'G': case 'g': case 'C': case 'c': gc++; acgt++; break;
                case 'A': case 'a': case 'T': case 't': acgt++; break;
                default: break;
            }
        }
    }

    double mean = static_cast<double>(total) / static_cast<double>(n);
    double gc_pct = (acgt > 0) ? (100.0 * static_cast<double>(gc) / static_cast<double>(acgt)) : 0.0;

    // N50: the length such that half of the total bases lie in sequences at least that long.
    std::sort(lengths.begin(), lengths.end(), std::greater<std::size_t>());
    std::size_t half = total / 2, cumulative = 0, n50 = 0;
    for (std::size_t len : lengths) {
        cumulative += len;
        if (cumulative >= half) { n50 = len; break; }
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Sequences        : " << n << "\n";
    std::cout << "Total length     : " << total << " bases\n";
    std::cout << "Min / mean / max : " << min_len << " / " << mean << " / " << max_len << "\n";
    std::cout << "N50              : " << n50 << "\n";
    std::cout << "GC content       : " << gc_pct << " %  (over A/C/G/T only)" << std::endl;
    std::cout.unsetf(std::ios::fixed);
}

void SequenceAnalyzer::show_complement() {
    std::cout << "Enter the index of the sequence: " << std::endl;
    int index;
    std::cin >> index;
    if (index < 1 or index > static_cast<int>(file->sequences.size())) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }
    std::string sequence = file->sequences[index - 1];
    std::string complement;
    for (char base : sequence) {
        switch (base) {
            case 'A': complement += 'T'; break;
            case 'T': complement += 'A'; break;
            case 'C': complement += 'G'; break;
            case 'G': complement += 'C'; break;
            default:  complement += 'N'; break;
        }
    }
    std::cout << "Complement of sequence " << index << " : " << complement << std::endl;
}

void SequenceAnalyzer::show_all_fasta() {
    const std::vector<std::string> &headers = file->headers;
    const std::vector<std::string> &sequences = file->sequences;
    std::cout << "FASTA file content:\n" << std::endl;
    for (std::size_t i = 0; i < headers.size(); ++i) {
        std::cout << headers[i] << "\n" << sequences[i] << "\n" << std::endl;
    }
}

void SequenceAnalyzer::show_all_fastq() {
    const std::vector<std::string> &headers = file->headers;
    const std::vector<std::string> &sequences = file->sequences;
    const std::vector<std::string> &quality = file->quality;
    std::cout << "FASTQ file content:\n" << std::endl;
    for (std::size_t i = 0; i < headers.size(); ++i) {
        std::cout << headers[i] << "\n" << sequences[i] << "\n+\n" << quality[i] << "\n" << std::endl;
    }
}

void SequenceAnalyzer::filter_by_quality(int encoding, int seq_index, int min_quality) {
    if (seq_index < 1 or seq_index > static_cast<int>(file->sequences.size())) {
        std::cerr << "Invalid sequence index." << std::endl;
        return;
    }
    if (min_quality < 0 or min_quality > 40) {
        std::cerr << "Error: the quality score should be between 0 and 40." << std::endl;
        return;
    }

    std::string quality_line = file->quality[seq_index - 1];
    std::string sequence = file->sequences[seq_index - 1];
    std::string filtered;

    int offset = 33;               // default: Sanger / Illumina 1.8+ (Phred+33)
    if (encoding == 2) offset = 64; // Illumina 1.3+ (Phred+64)

    for (std::size_t i = 0; i < quality_line.size(); ++i) {
        int score = static_cast<int>(quality_line[i]) - offset;
        filtered += (score >= min_quality) ? sequence[i] : '-';
    }
    std::cout << "Filtered sequence:\n" << filtered << std::endl;
}

void SequenceAnalyzer::show_suffix_table() {
    // Suffix array + LCP of a single sequence. Approach based on A. Mancheron's course.
    std::cout << "Enter the index of the sequence: ";
    int index;
    std::cin >> index;
    if (index < 1 or index > static_cast<int>(file->sequences.size())) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }

    std::string s = file->sequences[index - 1] + "$"; // append the terminal symbol
    int n = static_cast<int>(s.length());

    std::vector<int> suffixes(n);
    for (int i = 0; i < n; ++i) suffixes[i] = i;

    auto compare_suffix = [&](int i, int j) {
        while (i < n and j < n) {
            if (s[i] != s[j]) return s[i] < s[j];
            i++; j++;
        }
        return i == n;
    };

    auto lcp_length = [&](int i, int j) {
        int lcp = 0;
        while (i + lcp < n and j + lcp < n and s[i + lcp] == s[j + lcp]) lcp++;
        return lcp;
    };

    std::sort(suffixes.begin(), suffixes.end(), compare_suffix);

    std::cout << "\nSuffix table\n" << std::endl;
    std::cout << " Rank |  SA[i]  |  LCP  | Suffix\n";
    std::cout << "---------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        int sa = suffixes[i];
        int lcp = (i == 0) ? 0 : lcp_length(sa, suffixes[i - 1]);
        std::cout << "  " << i << "   |   " << sa << "    |  " << lcp << "   | " << s.substr(sa) << "\n";
    }
}

void SequenceAnalyzer::encode_sequence() {
    std::cout << "Enter the index of the sequence: ";
    int index;
    std::cin >> index;
    if (index < 1 or index > static_cast<int>(file->sequences.size())) {
        std::cerr << "Invalid index." << std::endl;
        return;
    }
    const std::string &seq = file->sequences[index - 1];
    std::vector<std::uint8_t> packed = TwoBitEncoder::pack(seq);
    std::string decoded = TwoBitEncoder::unpack(packed, seq.size());

    std::cout << "Original length : " << seq.size() << " bases (" << seq.size() << " bytes as text)" << std::endl;
    std::cout << "Two-bit encoded : " << packed.size() << " bytes (four bases per byte)" << std::endl;
    if (decoded == seq) {
        std::cout << "Round trip      : exact, the encoding is lossless for this sequence." << std::endl;
    } else {
        std::cout << "Round trip      : not exact, the sequence contains bases other than A/C/G/T "
                     "(only A/C/G/T can be represented on two bits)." << std::endl;
    }
}

void SequenceAnalyzer::map_reads() {
    if (file->sequences.empty()) {
        std::cerr << "No reference sequence is loaded." << std::endl;
        return;
    }
    // The reference is the first sequence of the file loaded at start-up.
    const std::string &reference = file->sequences[0];

    std::cout << "Enter the reads file (a full path, or a name inside ./fasta_files): ";
    std::string input;
    std::cin >> input;
    while (!input.empty() and (input.back() == '\r' or input.back() == ' ' or input.back() == '\t')) {
        input.pop_back(); // remove stray trailing characters from a paste.
    }

    SequenceFile checker;
    std::string reads_path = input;                 // first, try the path exactly as typed.
    if (!checker.file_exists(reads_path) and !input.empty() and input[0] != '/') {
        reads_path = "./fasta_files/" + input;      // for a bare name, look inside ./fasta_files.
    }
    if (checker.check_known_file(reads_path) != 0) {
        return;
    }
    std::string format = checker.detect_format(reads_path);

    std::vector<std::string> reads;
    std::vector<std::string> names;
    if (format == "FASTA") {
        FastaReader reader; reader.read(reads_path);
        reads = reader.sequences; names = reader.headers;
    } else if (format == "FASTQ") {
        FastqReader reader; reader.read(reads_path);
        reads = reader.sequences; names = reader.headers;
    } else {
        std::cerr << "The reads file is neither FASTA nor FASTQ." << std::endl;
        return;
    }

    std::cout << "Enter the k-mer size (for example 11): ";
    int k;
    std::cin >> k;
    if (k <= 0) {
        std::cerr << "The k-mer size must be a positive integer." << std::endl;
        return;
    }

    Mapper mapper(reference, k);
    std::cout << "\nMapping " << reads.size() << " read(s) onto a reference of "
              << reference.size() << " bases (k = " << k << "):\n" << std::endl;

    for (std::size_t i = 0; i < reads.size(); ++i) {
        std::string label = (i < names.size() and !names[i].empty()) ? names[i] : ("read " + std::to_string(i + 1));
        Mapper::Result r = mapper.map_read(reads[i]);
        std::cout << label << "\n";
        if (!r.mapped) {
            std::cout << "  unmapped (" << r.note << ")\n" << std::endl;
            continue;
        }
        std::cout << "  position " << r.position + 1 << " (1-based), strand " << r.strand
                  << ", seeds " << r.seeds_matched << "/" << r.seeds_total;
        if (r.window_checked) std::cout << ", mismatches " << r.mismatches;
        std::cout << "\n  " << r.note << "\n" << std::endl;
    }
}

void SequenceAnalyzer::run(const std::string & /*name*/, FileType t) {
    type = t;
    Menu menu;
    bool running = true;
    std::string option;

    while (running) {
        show_menu(type);
        option = menu.ask_choice();

        if (option == "-help" or option == "-h") {
            show_menu(type);
        } else if (option == "-countseq") {
            count_sequences();
        } else if (option == "-length") {
            sequence_length();
        } else if (option == "-headers") {
            show_headers();
        } else if (option == "-sequence") {
            show_sequences();
        } else if (option == "-total_length") {
            total_length();
        } else if (option == "-stats") {
            show_stats();
        } else if (option == "-complement") {
            show_complement();
        } else if (option == "-all_fasta" and type == FileType::Fasta) {
            show_all_fasta();
        } else if (option == "-all_fastq" and type == FileType::Fastq) {
            show_all_fastq();
        } else if (option == "-quality_score" and type == FileType::Fasta) {
            std::cout << "This option is only available for FASTQ files." << std::endl;
        } else if (option == "-quality_score") {
            std::cout << "Select the encoding you are using:" << std::endl;
            std::cout << "1. Sanger, Phred+33 (ASCII 33-73)" << std::endl;
            std::cout << "2. Illumina 1.3+, Phred+64 (ASCII 64-104)" << std::endl;
            std::cout << "3. Illumina 1.8+, Phred+33 (ASCII 33-74)" << std::endl;
            int encoding; std::cin >> encoding;
            std::cout << "Give the index of the sequence to filter: ";
            int seq_index; std::cin >> seq_index;
            std::cout << "Give the minimum quality score (0-40): ";
            int min_quality; std::cin >> min_quality;
            filter_by_quality(encoding, seq_index, min_quality);
        } else if (option == "-table_suffix") {
            show_suffix_table();
        } else if (option == "-encode") {
            encode_sequence();
        } else if (option == "-mapping") {
            map_reads();
        } else if (option == "-quit") {
            std::cout << "\nThank you for using SeqForge. Goodbye!" << std::endl;
            running = false;
        } else {
            std::cerr << "Error: invalid option." << std::endl;
        }
    }
}
