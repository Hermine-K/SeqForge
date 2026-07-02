# How it works

This page explains the choices behind SeqForge and their trade-offs.

## From a suffix table to a k-mer index

An earlier version of the project indexed a sequence with a suffix table built
by a comparison sort. Sorting the suffixes costs O(n log n) comparisons, and
each comparison can scan up to O(n) characters, so the construction is
effectively quadratic. Measured on real data, this was about six seconds for ten
kilobases and more than five minutes for a hundred, which does not scale to a
genome.

SeqForge replaces it with a **k-mer index**. Every k-mer of the reference is
encoded on two bits per base into a 64-bit integer and stored in a hash table
that maps the integer to the list of positions where the k-mer starts:

- Building the index is a single linear pass over the reference, so O(n).
- A lookup is constant on average, plus the number of occurrences returned.

The index answers the questions the project requires directly: is a word present
on either strand, how many times (its support), at which positions and on which
strand. This is the standard first step of real read mappers before they add
heavier structures.

## Seed-and-extend mapping

For a read, the mapper collects the positions of all its k-mers from the index.
Each hit votes for a diagonal, defined as the reference position minus the
k-mer offset inside the read, so that k-mers belonging to the same alignment all
vote for the same diagonal. The best-supported diagonal is the read position.
The read is mapped both directly and as its reverse complement to decide the
strand. A final pass counts the mismatches over the aligned window, which is the
extend step and distinguishes an exact match from a substitution or error.

## Complexity

- Reading a FASTA or FASTQ file is linear in the number of bases, O(n).
- Building the k-mer index of a reference of length n is O(n).
- Mapping a read of length m is O(m) lookups plus the hits examined.

## Honest limitations

- Only the first sequence of the reference file is indexed.
- The mapper handles substitutions well; insertions and deletions are not
  chained yet, so an indel is not diagnosed as precisely as a substitution.
- The index is kept in memory, which is fine for a chromosome but not for a
  whole large genome without a more compact structure.

A production mapper such as BWA uses a Burrows-Wheeler transform and an FM-index
to stay memory-efficient on very large genomes. SeqForge does not aim to compete
with those, but it implements the same core idea in a small, readable form.
