#include "Mapper.hpp"
#include "TwoBitEncoder.hpp"
#include <map>

Mapper::Mapper(const std::string &ref, int k_) : reference(ref), k(k_), index(ref, k_) {}

void Mapper::best_forward_diagonal(const std::string &query, long &best_diag, std::size_t &best_votes) const {
    best_diag = 0;
    best_votes = 0;
    if (query.size() < static_cast<std::size_t>(k)) return;

    // Each k-mer hit votes for the diagonal d = reference_position - read_offset.
    std::map<long, std::size_t> votes;
    for (std::size_t j = 0; j + static_cast<std::size_t>(k) <= query.size(); ++j) {
        std::vector<std::size_t> hits = index.forward_hits(query.substr(j, k));
        for (std::size_t p : hits) {
            long d = static_cast<long>(p) - static_cast<long>(j);
            std::size_t v = ++votes[d];
            if (v > best_votes) {
                best_votes = v;
                best_diag = d;
            }
        }
    }
}

std::size_t Mapper::count_mismatches(const std::string &query, long diag) const {
    std::size_t mm = 0;
    for (std::size_t j = 0; j < query.size(); ++j) {
        long ref_pos = diag + static_cast<long>(j);
        if (ref_pos < 0 or ref_pos >= static_cast<long>(reference.size())) {
            mm++; // a base falling outside the reference counts as a mismatch.
            continue;
        }
        if (reference[static_cast<std::size_t>(ref_pos)] != query[j]) mm++;
    }
    return mm;
}

Mapper::Result Mapper::map_read(const std::string &read) const {
    Result r;
    r.seeds_total = (read.size() >= static_cast<std::size_t>(k)) ? read.size() - k + 1 : 0;

    if (read.size() < static_cast<std::size_t>(k)) {
        r.note = "read shorter than k, cannot be mapped";
        return r;
    }

    // Forward strand.
    long fdiag; std::size_t fvotes;
    best_forward_diagonal(read, fdiag, fvotes);

    // Reverse strand: map the reverse complement of the read on the forward index.
    std::string rc = TwoBitEncoder::reverse_complement(read);
    long rdiag; std::size_t rvotes;
    best_forward_diagonal(rc, rdiag, rvotes);

    if (fvotes == 0 and rvotes == 0) {
        r.note = "no k-mer of the read was found in the reference";
        return r;
    }

    // Keep the strand with the most supporting seeds.
    std::string aligned_query;
    long diag;
    if (fvotes >= rvotes) {
        r.strand = '+'; r.seeds_matched = fvotes; diag = fdiag; aligned_query = read;
    } else {
        r.strand = '-'; r.seeds_matched = rvotes; diag = rdiag; aligned_query = rc;
    }

    r.mapped = true;
    r.position = (diag < 0) ? 0 : static_cast<std::size_t>(diag);

    // Extend step: count mismatches over the aligned window if it fits in the reference.
    if (diag >= 0 and diag + static_cast<long>(aligned_query.size()) <= static_cast<long>(reference.size())) {
        r.mismatches = count_mismatches(aligned_query, diag);
        r.window_checked = true;
        if (r.mismatches == 0) {
            r.note = "exact match (all k-mers aligned)";
        } else {
            r.note = "aligned with " + std::to_string(r.mismatches) +
                     " mismatch(es): likely substitution or sequencing error";
        }
    } else {
        r.note = "aligned near the reference border, window not fully checked";
    }
    return r;
}
