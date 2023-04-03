# wzip - Run-Length Encoding Compression Tool

wzip is a simple command-line tool for compressing and decompressing files using run-length encoding (RLE) algorithm. The compressed format consists of a series of 5-byte entries, each containing a 4-byte integer (the run length) followed by a single character.

## Getting Started

To compile and run the wzip, follow the instructions below.

### Prerequisites

- A C compiler (e.g., GCC)
- GNU Make

### Compilation

1. Clone the repository or download the source code:

```bash
git clone https://github.com/no-hao/wzip.git
```
2. Navigate to the project directory:
```
cd wzip
```

3. Compile the code using the Makefile:
```
make
```

this will create the `wzip` executable.


## Usage

To compress a file, use the `wzip` tool with shell redirection to sae the compressed output to a file:
```
./wzip input.txt > output.z
```

For stage 1 of this project, `wzip` can not handle multithreading but implementation to come in stage 2.


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- This project is based on the `initial-utilities` project of the ostep-projects [github](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities) repository. 
