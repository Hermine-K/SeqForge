# SeqForge

A small, dependency-free C++ toolkit to read, validate and analyze FASTA and
FASTQ files, encode nucleotide sequences on two bits, index a reference with a
k-mer index, and map short reads onto that reference by seed-and-extend.

SeqForge started as a bioinformatics course project and was rebuilt as a clean,
general command-line tool.

## What it can do

- Read and validate FASTA and FASTQ files, including multi-line records, and
  report structural problems clearly (missing header, empty sequence, quality
  and sequence of different lengths, invalid characters).
- Explore a file from an interactive menu: count, headers, lengths, complement,
  a length and GC-content summary, and the suffix and LCP table of a sequence.
- Encode a sequence on two bits (four bases per byte) and check that the
  encoding is lossless.
- Index a reference by its k-mers and map reads onto it, reporting the position,
  the strand, the number of supporting seeds and the mismatches.

## Quickstart

```bash
cmake -S . -B build
cmake --build build
./build/seqforge --help
```

Then analyze a file:

```bash
./build/seqforge path/to/reads.fastq
```

See [Installation](installation.md) to build, [Usage](usage.md) for the menu,
and [Read mapping](mapping.md) for a full worked example.
