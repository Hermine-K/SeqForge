# Usage

## Launching

```bash
seqforge <file>     analyze a file directly (the path can be relative or absolute)
seqforge            pick a file interactively from the ./fasta_files folder
seqforge --help     show the help and the list of options
```

The format, FASTA or FASTQ, is detected automatically from the extension and
the first character, and printed. An invalid file is rejected with the reason
and the line involved.

## The interactive menu

Once a valid file is loaded, an interactive menu is shown. Options are grouped:

**File**

- `-countseq` : count the number of sequences.
- `-headers` : display the headers.
- `-stats` : a summary with the sequence count, the total length, the minimum,
  mean and maximum length, the N50 and the GC content.

**Sequence**

- `-sequence` : display the stored sequences.
- `-length` : length of a sequence, given its index.
- `-total_length` : total length of all sequences.
- `-complement` : complement of a sequence, given its index.
- `-table_suffix` : suffix and LCP table of a sequence.

**FASTQ only**

- `-quality_score` : filter a read by its quality scores (choose the encoding,
  the sequence index and the minimum score).

**Encoding and mapping**

- `-encode` : two-bit encode a sequence and show the packed size. See
  [Two-bit encoding](encoding.md).
- `-mapping` : map the reads of a second file onto the loaded reference. See
  [Read mapping](mapping.md).

`-help` shows the menu again and `-quit` exits.

!!! note "The fasta_files folder"
    In interactive mode, the file must sit in a `fasta_files/` folder next to the
    program. When you pass a path on the command line, or a full path to the reads
    file during mapping, that folder is not needed.
