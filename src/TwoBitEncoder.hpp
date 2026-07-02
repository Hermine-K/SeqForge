#ifndef TWO_BIT_ENCODER_HPP
#define TWO_BIT_ENCODER_HPP

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Two-bit binary encoding of nucleotide sequences.
 *
 * The DNA alphabet has only four letters, so each base fits in two bits
 * (A=00, C=01, G=10, T=11). This packs four bases per byte (a fourfold size
 * reduction) and lets a k-mer of length up to 32 be stored in a single
 * 64-bit integer, which is what makes the k-mer index fast.
 *
 * Only A, C, G and T are supported. Any other character (N, IUPAC ambiguity
 * codes, gaps) makes a k-mer invalid and is not encoded.
 */
class TwoBitEncoder {
public:
    /** @brief Two-bit code of a base, or -1 if the character is not A/C/G/T. */
    static int base_to_code(char base);

    /** @brief Base corresponding to a two-bit code (0..3). */
    static char code_to_base(int code);

    /**
     * @brief Encodes a k-mer (length up to 32) into a 64-bit integer.
     * @param kmer The k-mer string.
     * @param code Output: the encoded value (first base in the high bits).
     * @return true if the k-mer contains only A/C/G/T and fits in 64 bits.
     */
    static bool encode_kmer(const std::string &kmer, std::uint64_t &code);

    /** @brief Decodes a k-mer of length k from its 64-bit code. */
    static std::string decode_kmer(std::uint64_t code, int k);

    /** @brief Reverse complement of an encoded k-mer of length k. */
    static std::uint64_t reverse_complement(std::uint64_t code, int k);

    /** @brief Reverse complement of a sequence string (non-A/C/G/T becomes 'N'). */
    static std::string reverse_complement(const std::string &seq);

    /**
     * @brief Packs a sequence into bytes, four bases per byte.
     * Characters other than A/C/G/T are stored as A; validate sequences first.
     */
    static std::vector<std::uint8_t> pack(const std::string &seq);

    /** @brief Unpacks a byte vector back into a sequence of the given length. */
    static std::string unpack(const std::vector<std::uint8_t> &packed, std::size_t length);
};

#endif // TWO_BIT_ENCODER_HPP
