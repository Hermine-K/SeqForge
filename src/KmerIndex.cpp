#include "KmerIndex.hpp"
#include "TwoBitEncoder.hpp"

KmerIndex::KmerIndex(const std::string &ref, int k_) : reference(ref), k(k_) {
    if (k <= 0 or reference.size() < static_cast<std::size_t>(k)) {
        return; // nothing to index.
    }
    // Slide a window of length k over the reference and index each valid k-mer.
    for (std::size_t i = 0; i + static_cast<std::size_t>(k) <= reference.size(); ++i) {
        std::uint64_t code;
        if (TwoBitEncoder::encode_kmer(reference.substr(i, k), code)) {
            table[code].push_back(static_cast<std::uint32_t>(i));
        }
        // k-mers containing an invalid base (N, ambiguity codes) are simply skipped.
    }
}

std::vector<std::size_t> KmerIndex::forward_hits(const std::string &word) const {
    std::vector<std::size_t> hits;
    std::uint64_t code;
    if (!TwoBitEncoder::encode_kmer(word, code)) return hits;
    auto it = table.find(code);
    if (it != table.end()) {
        for (std::uint32_t p : it->second) hits.push_back(p);
    }
    return hits;
}

std::vector<KmerIndex::Hit> KmerIndex::positions(const std::string &word) const {
    std::vector<Hit> result;
    std::uint64_t code;
    if (!TwoBitEncoder::encode_kmer(word, code)) return result;

    auto it = table.find(code);                       // forward strand occurrences.
    if (it != table.end()) {
        for (std::uint32_t p : it->second) result.push_back({p, '+'});
    }

    std::uint64_t rc = TwoBitEncoder::reverse_complement(code, k);
    if (rc != code) {                                 // reverse strand occurrences.
        auto it2 = table.find(rc);
        if (it2 != table.end()) {
            for (std::uint32_t p : it2->second) result.push_back({p, '-'});
        }
    }
    return result;
}

bool KmerIndex::contains(const std::string &word) const {
    return !positions(word).empty();
}

std::size_t KmerIndex::support(const std::string &word) const {
    return positions(word).size();
}

std::string KmerIndex::kmer_at(std::size_t i) const {
    if (i + static_cast<std::size_t>(k) > reference.size()) return "";
    return reference.substr(i, k);
}
