#ifndef MAPPER_HPP
#define MAPPER_HPP

#include <string>
#include "KmerIndex.hpp"

/**
 * @brief Maps short reads onto a reference by seed-and-extend.
 *
 * The reference is indexed once. For a read, every k-mer is looked up in the
 * index: each hit votes for a diagonal (reference position minus read offset),
 * so the diagonal with the most votes is where the read most likely aligns.
 * The read is also mapped as its reverse complement to test the reverse strand.
 * A final pass over the chosen window counts the mismatches (the extend step),
 * which separates an exact match from a read carrying a substitution or error.
 */
class Mapper {
public:
    struct Result {
        bool mapped = false;         ///< Whether a candidate position was found.
        std::size_t position = 0;    ///< 0-based leftmost position on the reference.
        char strand = '+';           ///< '+' forward, '-' reverse.
        std::size_t seeds_matched = 0; ///< k-mers supporting the chosen diagonal.
        std::size_t seeds_total = 0;   ///< total number of k-mers in the read.
        std::size_t mismatches = 0;    ///< mismatches over the aligned window (if it fits).
        bool window_checked = false;   ///< whether the mismatch count could be computed.
        std::string note;              ///< short human-readable diagnosis.
    };

    /** @brief Builds a mapper over the given reference with the given k-mer size. */
    Mapper(const std::string &reference, int k);

    /** @brief Maps a single read onto the reference. */
    Result map_read(const std::string &read) const;

private:
    std::string reference;
    int k;
    KmerIndex index;

    // Votes the best forward diagonal for a query; returns the diagonal and its vote count.
    void best_forward_diagonal(const std::string &query, long &best_diag, std::size_t &best_votes) const;
    std::size_t count_mismatches(const std::string &query, long diag) const;
};

#endif // MAPPER_HPP
