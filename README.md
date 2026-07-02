# SeqForge

![CI](https://github.com/Hermine-K/SeqForge/actions/workflows/ci.yml/badge.svg)
![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/license-MIT-green)

A small, dependency-free C++ toolkit to read, validate and analyze FASTA and
FASTQ files, encode nucleotide sequences on two bits, index a reference with a
k-mer index, and map short reads onto that reference by seed-and-extend.

## Features

Reading and validation:

- Robust FASTA and FASTQ parsing that never blocks on malformed input. Blank
  lines, missing headers, multi-line FASTA and FASTQ records, and Windows line
  endings are all handled.
- Sequence validation against the IUPAC alphabet, with a clear report of every
  invalid character, and structural checks (header before sequence, empty
  sequence, duplicated header, sequence and quality of equal length in FASTQ).

Analysis (interactive menu):

- Count sequences, show headers and sequences, compute lengths, show the
  complement of a sequence, filter a FASTQ read by quality score, and print the
  suffix and LCP table of a sequence.

Encoding, indexing and mapping:

- `TwoBitEncoder` packs A/C/G/T on two bits (four bases per byte, a fourfold
  size reduction) and encodes a k-mer of length up to 32 into a single 64-bit
  integer.
- `KmerIndex` builds a hash table from every encoded k-mer of a reference to its
  positions. It answers, for any word, whether it is present on either strand,
  its support (number of occurrences), its positions and its strand.
- `Mapper` maps a read by voting for the diagonal supported by the most k-mer
  seeds, tests both strands, then counts the mismatches over the aligned window.
  This separates an exact match from a read carrying a substitution or a
  sequencing error, following the strategy of the original project.

## Design note: why a k-mer index

An earlier version indexed a sequence with a suffix table built by a comparison
sort, whose construction was quadratic (about six seconds for ten kilobases and
more than five minutes for a hundred). The k-mer index used here is built in one
linear pass over the reference and every lookup is constant on average, because
each fixed-length k-mer is encoded into an integer and stored in a hash table.
This is the choice that lets the mapping scale, and it is what real mappers rely
on before adding heavier structures such as an FM-index.

## Build and test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/seqforge
```

Or a quick build with g++:

```bash
g++ -std=c++20 -Isrc src/*.cpp -o seqforge
```

## Usage

Run with a file to analyze it (or run without arguments to select a file
interactively from a `fasta_files/` folder next to the program):

```bash
./seqforge path/to/reference.fasta
```

Run `seqforge --help` for a full description without loading a file. At the menu,
useful options are `-stats` (sequence count, lengths, N50 and GC content),
`-encode` (two-bit encode a sequence and show the packed size), `-mapping` (map
the reads of a second file onto the first sequence of the loaded file; it asks
for the reads file, given as a full path or a name inside `fasta_files/`, and the
k-mer size), and `-quit`.

## Project structure

```
SeqForge/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── .github/workflows/ci.yml       # build and test on every push
├── src/
│   ├── main.cpp                   # entry point, file selection and dispatch
│   ├── SequenceFile.{hpp,cpp}     # base class: checks, format detection, validation, storage
│   ├── FastaReader.{hpp,cpp}      # FASTA parsing
│   ├── FastqReader.{hpp,cpp}      # FASTQ parsing
│   ├── SequenceAnalyzer.{hpp,cpp} # analysis options and the interactive loop
│   ├── Menu.{hpp,cpp}             # menu display and input
│   ├── TwoBitEncoder.{hpp,cpp}    # two-bit encoding of sequences and k-mers
│   ├── KmerIndex.{hpp,cpp}        # k-mer hash index of a reference
│   └── Mapper.{hpp,cpp}           # read mapping by seed-and-extend
└── tests/
    └── test_main.cpp              # unit tests (encoder, index, mapper)
```

## Roadmap

- SAM-formatted output for the mapped reads.
- Mapping against a reference made of several sequences.
- Chaining of seeds to handle insertions and deletions, not only substitutions.
- A more compact index (for example an FM-index) for very large genomes.

## License

Released under the MIT License. See [LICENSE](LICENSE).
