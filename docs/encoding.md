# Two-bit encoding

The DNA alphabet has only four letters, so each base fits in two bits
(A = 00, C = 01, G = 10, T = 11). This packs four bases into a single byte, a
fourfold reduction compared with one character per base, and it lets a k-mer of
length up to 32 be stored in one 64-bit integer.

## In the tool

At the menu, `-encode` two-bit encodes a chosen sequence and reports the packed
size, then checks that decoding gives the original back:

```text
Enter the index of the sequence: 1
Original length : 60 bases (60 bytes as text)
Two-bit encoded : 15 bytes (four bases per byte)
Round trip      : exact, the encoding is lossless for this sequence.
```

Only A, C, G and T can be represented on two bits. If a sequence contains other
characters (N, IUPAC ambiguity codes, gaps), the round trip is reported as not
exact, since those bases cannot be encoded.

## Why it matters here

The same encoding turns each k-mer into an integer key. That key is what the
[k-mer index](design.md) stores, and comparing integers instead of strings is
what makes the index fast. The reverse complement of an encoded k-mer is also a
cheap bit operation, which the mapper uses to test the reverse strand.
