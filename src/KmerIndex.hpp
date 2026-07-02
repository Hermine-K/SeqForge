#ifndef KMER_INDEX_HPP
#define KMER_INDEX_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

/**
 * @brief A k-mer index of a reference sequence.
 *
 * Every k-mer of the reference is encoded on two bits per base and stored in a
 * hash table that maps the encoded k-mer to the list of positions where it
 * starts. Building is linear in the length of the reference and a lookup is
 * constant on average, which answers the questions of the project directly:
 * is a word present (on either strand), how many times (its support), at which
 * positions and on which strand.
 *
 * This replaces the suffix-table approach whose construction was quadratic.
 */
class KmerIndex {
public:
    /** @brief One occurrence of a queried k-mer: a position and a strand. */
    struct Hit {
        std::size_t position; ///< 0-based start position on the reference.
        char strand;          ///< '+' for the forward strand, '-' for the reverse strand.
    };

    /** @brief Builds the index of every k-mer of the reference. */
    KmerIndex(const std::string &reference, int k);

    /** @brief The k-mer size used by this index. */
    int kmer_size() const { return k; }

    /** @brief The length of the indexed reference. */
    std::size_t reference_length() const { return reference.size(); }

    /** @brief Whether the word (or its reverse complement) is present in the reference. */
    bool contains(const std::string &word) const;

    /** @brief Total number of occurrences of the word on both strands (its support). */
    std::size_t support(const std::string &word) const;

    /** @brief All occurrences of the word, with their position and strand. */
    std::vector<Hit> positions(const std::string &word) const;

    /** @brief Forward-strand start positions of the word (used by the mapper). */
    std::vector<std::size_t> forward_hits(const std::string &word) const;

    /** @brief The k-mer starting at position i of the reference. */
    std::string kmer_at(std::size_t i) const;

private:
    std::string reference;
    int k;
    std::unordered_map<std::uint64_t, std::vector<std::uint32_t>> table; ///< encoded k-mer -> forward positions.
};

#endif // KMER_INDEX_HPP
