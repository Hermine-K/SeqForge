#include "TwoBitEncoder.hpp"

int TwoBitEncoder::base_to_code(char base) {
    switch (base) {
        case 'A': case 'a': return 0;
        case 'C': case 'c': return 1;
        case 'G': case 'g': return 2;
        case 'T': case 't': return 3;
        default:  return -1;
    }
}

char TwoBitEncoder::code_to_base(int code) {
    switch (code & 3) {
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'G';
        default: return 'T';
    }
}

bool TwoBitEncoder::encode_kmer(const std::string &kmer, std::uint64_t &code) {
    if (kmer.size() > 32) return false; // 32 bases fill the 64 bits exactly.
    std::uint64_t value = 0;
    for (char c : kmer) {
        int b = base_to_code(c);
        if (b < 0) return false;        // a non-A/C/G/T base makes the k-mer invalid.
        value = (value << 2) | static_cast<std::uint64_t>(b);
    }
    code = value;
    return true;
}

std::string TwoBitEncoder::decode_kmer(std::uint64_t code, int k) {
    std::string s(static_cast<std::size_t>(k), 'A');
    for (int i = 0; i < k; ++i) {
        int shift = 2 * (k - 1 - i);    // the first base sits in the high bits.
        s[i] = code_to_base(static_cast<int>((code >> shift) & 3ULL));
    }
    return s;
}

std::uint64_t TwoBitEncoder::reverse_complement(std::uint64_t code, int k) {
    std::uint64_t rc = 0;
    for (int i = 0; i < k; ++i) {
        std::uint64_t base = code & 3ULL;          // read the last base first
        std::uint64_t comp = base ^ 3ULL;          // A<->T and C<->G are a XOR with 0b11
        rc = (rc << 2) | comp;                      // place it at the front of the result
        code >>= 2;
    }
    return rc;
}

std::string TwoBitEncoder::reverse_complement(const std::string &seq) {
    std::string rc;
    rc.reserve(seq.size());
    for (std::size_t i = seq.size(); i-- > 0; ) {
        char c = seq[i];
        switch (c) {
            case 'A': case 'a': rc.push_back('T'); break;
            case 'T': case 't': rc.push_back('A'); break;
            case 'C': case 'c': rc.push_back('G'); break;
            case 'G': case 'g': rc.push_back('C'); break;
            default:            rc.push_back('N'); break;
        }
    }
    return rc;
}

std::vector<std::uint8_t> TwoBitEncoder::pack(const std::string &seq) {
    std::vector<std::uint8_t> packed((seq.size() + 3) / 4, 0);
    for (std::size_t i = 0; i < seq.size(); ++i) {
        int b = base_to_code(seq[i]);
        if (b < 0) b = 0;                          // unknown base stored as A (validate first).
        int shift = 2 * (3 - static_cast<int>(i % 4));
        packed[i / 4] |= static_cast<std::uint8_t>(b << shift);
    }
    return packed;
}

std::string TwoBitEncoder::unpack(const std::vector<std::uint8_t> &packed, std::size_t length) {
    std::string seq(length, 'A');
    for (std::size_t i = 0; i < length; ++i) {
        int shift = 2 * (3 - static_cast<int>(i % 4));
        int b = (packed[i / 4] >> shift) & 3;
        seq[i] = code_to_base(b);
    }
    return seq;
}
