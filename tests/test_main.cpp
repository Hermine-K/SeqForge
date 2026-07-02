// Minimal, dependency-free unit tests for SeqForge.
// Each check prints PASS/FAIL; the program returns non-zero if any check fails.

#include "TwoBitEncoder.hpp"
#include "KmerIndex.hpp"
#include "Mapper.hpp"
#include "FastaReader.hpp"
#include "FastqReader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

static int failures = 0;

static void check(bool condition, const std::string &name) {
    std::cout << (condition ? "PASS  " : "FAIL  ") << name << std::endl;
    if (!condition) failures++;
}

int main() {
    // --- TwoBitEncoder: k-mer round trip ---
    {
        std::string kmer = "ACGTACGTTG";
        std::uint64_t code;
        bool ok = TwoBitEncoder::encode_kmer(kmer, code);
        check(ok, "encode_kmer accepts a valid k-mer");
        check(TwoBitEncoder::decode_kmer(code, static_cast<int>(kmer.size())) == kmer,
              "decode(encode(kmer)) == kmer");
    }
    // --- TwoBitEncoder: invalid base rejected ---
    {
        std::uint64_t code;
        check(!TwoBitEncoder::encode_kmer("ACGTN", code), "encode_kmer rejects a k-mer with N");
    }
    // --- TwoBitEncoder: reverse complement (encoded) ---
    {
        std::string kmer = "AACCGGTT";
        std::uint64_t code, rc;
        TwoBitEncoder::encode_kmer(kmer, code);
        rc = TwoBitEncoder::reverse_complement(code, static_cast<int>(kmer.size()));
        check(TwoBitEncoder::decode_kmer(rc, static_cast<int>(kmer.size())) == "AACCGGTT",
              "reverse complement of AACCGGTT is AACCGGTT (palindrome)");
        std::string kmer2 = "AAAACGGG";
        TwoBitEncoder::encode_kmer(kmer2, code);
        rc = TwoBitEncoder::reverse_complement(code, static_cast<int>(kmer2.size()));
        check(TwoBitEncoder::decode_kmer(rc, static_cast<int>(kmer2.size())) == "CCCGTTTT",
              "reverse complement of AAAACGGG is CCCGTTTT");
    }
    // --- TwoBitEncoder: pack / unpack round trip ---
    {
        std::string seq = "ACGTACGTACGTA";
        auto packed = TwoBitEncoder::pack(seq);
        check(packed.size() == (seq.size() + 3) / 4, "pack uses four bases per byte");
        check(TwoBitEncoder::unpack(packed, seq.size()) == seq, "unpack(pack(seq)) == seq");
    }
    // --- KmerIndex: presence, support, positions, strand ---
    {
        std::string ref = "AAAACCCCGGGGTTTTACGT";
        KmerIndex idx(ref, 4);
        check(idx.contains("AAAA"), "index contains AAAA");
        check(idx.forward_hits("AAAA").size() == 1 && idx.forward_hits("AAAA")[0] == 0,
              "AAAA occurs once at position 0 on the forward strand");
        // TTTT is the reverse complement of AAAA, so querying AAAA must also find a minus-strand hit.
        auto hits = idx.positions("AAAA");
        bool has_minus = false;
        for (auto &h : hits) if (h.strand == '-') has_minus = true;
        check(has_minus, "querying AAAA also reports a reverse-strand hit (TTTT present)");
        check(!idx.contains("AAAT"), "AAAT is absent from the reference");
    }
    // --- Mapper: exact forward, substitution, reverse strand ---
    {
        std::string ref = "ACGTTGCAACCGGATTCAGCTAGCATCGATCGTTAGCACGTACTG";
        int k = 6;
        Mapper mapper(ref, k);

        std::string sub = ref.substr(10, 15);        // a unique region of the reference.
        Mapper::Result r1 = mapper.map_read(sub);
        check(r1.mapped && r1.strand == '+' && r1.position == 10 && r1.mismatches == 0,
              "exact read maps to the forward strand at the right position");

        std::string mut = sub;                       // introduce one substitution in the middle.
        mut[7] = (mut[7] == 'A') ? 'C' : 'A';
        Mapper::Result r2 = mapper.map_read(mut);
        check(r2.mapped && r2.strand == '+' && r2.position == 10 && r2.mismatches == 1,
              "read with one substitution maps to the right place with one mismatch");
        check(r2.seeds_matched < r2.seeds_total,
              "a substitution lowers the number of matching seeds");

        std::string rc = TwoBitEncoder::reverse_complement(sub);
        Mapper::Result r3 = mapper.map_read(rc);
        check(r3.mapped && r3.strand == '-' && r3.position == 10 && r3.mismatches == 0,
              "reverse-complement read maps to the reverse strand at the right position");
    }

    // --- FastqReader: multi-line record ---
    {
        const char *path = "tmp_test_multiline.fq";
        { std::ofstream o(path); o << "@r1\nACGTACGT\nACGTACGT\n+\nIIIIIIII\nIIIIIIII\n@r2\nGGGGCCCC\n+\nIIIIIIII\n"; }
        FastqReader fq; fq.read(path);
        check(fq.sequences.size() == 2, "multi-line FASTQ yields two records");
        check(fq.sequences[0] == "ACGTACGTACGTACGT", "multi-line FASTQ sequence is concatenated");
        check(fq.quality[0].size() == fq.sequences[0].size(), "multi-line FASTQ quality matches the sequence length");
        std::remove(path);
    }
    // --- FastaReader: multi-line record ---
    {
        const char *path = "tmp_test_multiline.fa";
        { std::ofstream o(path); o << ">s1\nACGT\nACGT\n>s2\nTTTT\n"; }
        FastaReader fa; fa.read(path);
        check(fa.sequences.size() == 2, "multi-line FASTA yields two sequences");
        check(fa.sequences[0] == "ACGTACGT", "multi-line FASTA sequence is concatenated");
        std::remove(path);
    }

    std::cout << "\n" << (failures == 0 ? "All tests passed." : std::to_string(failures) + " test(s) failed.") << std::endl;
    return failures == 0 ? 0 : 1;
}
