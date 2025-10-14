# vectors

## Overview

**vectors** is a C++ library for the vectorial representation and manipulation of musical phenomena. It provides a unified framework for working with musical structures such as scales, chords, rhythms, and transformations using mathematical and algorithmic tools. The library is designed for music theorists, computational musicologists, composers, and developers interested in algorithmic and generative music.

## Features

- Unified vector classes for positions, intervals, and binary patterns
- Meta-operators for selection, transformation, and generation of musical objects
- Distance and similarity measures for musical vectors
- Matrix operations for modal, transpositional, and rototranslational analysis
- Rhythmic pattern generators (Euclidean, Clough-Douthett, deep rhythms, tihai, etc.)
- Support for cyclic and modular arithmetic in musical contexts
- Extensible and modular design for advanced applications

## Library Structure

```
src/
	binaryVector.h        # BinaryVector class for binary rhythm patterns
	chord.h               # Chord generation functions from scales and intervals
	distances.h           # Distance and transformation functions for vectors
	intervalVector.h      # IntervalVector class for intervallic structures
	mathUtil.h            # Mathematical utilities (GCD, LCM, Euclidean division)
	matrix.h              # Matrix operations (modal, transposition, rototranslation)
	positionVector.h      # PositionVector class for pitch/position sets
	rhythmGen.h           # Rhythmic pattern generators
	scale.h               # Scale class for musical scales and transformations
	selection.h           # Selection meta-operators for musical structures
	utility.h             # General utility functions and includes
	Vector.h              # Vectors class: unified representation (positions, intervals, binary)
	vectors.h             # Conversion functions between representations
examples/
	chordTest.cpp         # Chord generation and selection examples
	classtest.cpp         # Class tests for IntervalVector, BinaryVector, PositionVector
	distances.cpp         # Distance and transformation examples
	matrix.cpp            # Matrix operations and modal analysis
	rhythmGen.cpp         # Rhythmic pattern generation examples
	scale2.cpp            # Scale class usage and transformations
	selection.cpp         # Selection meta-operators demonstration
	tihai.cpp             # Tihai rhythmic pattern generation
	vectortest.cpp        # Unified Vectors class demonstration
LICENSE
README.md
```

## Main Components

### Vector Classes
- **PositionVector**: Cyclic positional vectors for pitch sets, supports rotation, inversion, complement, and more.
- **IntervalVector**: Intervallic structures with cyclic access, rotation, inversion, and scalar/vector operations.
- **BinaryVector**: Binary (0/1) vectors for rhythmic patterns, logical operations, and cyclic transformations.
- **Vectors**: Unified class maintaining synchronized position, interval, and binary representations.

### Meta-Operators & Algorithms
- **Selection**: Meta-operators for extracting or generating new vectors from source vectors using position or interval criteria.
- **Chord**: Functions to generate chords from scales and degrees/intervals, supporting transformations and inversions.
- **Matrix**: Modal, transpositional, and rototranslational matrix generation for musical analysis.
- **Distances**: Euclidean, Manhattan, edit, Hamming, and weighted transformation distances for musical vectors.

### Rhythmic Generators
- **Euclidean rhythms**: Evenly distributed pulses in a given number of steps.
- **Clough-Douthett patterns**: Rhythmic patterns based on mathematical models.
- **Deep rhythms**: Patterns with multiplicity and distributed onsets.
- **Tihai**: North Indian rhythmic patterns with repetition and offset.

### Scale Class
- **Scale**: Encapsulates musical scales, supporting construction from positions or intervals, and transformations such as transposition, mode, inversion, and mirroring.

## Applications

- **Algorithmic composition**: Generate and transform scales, chords, and rhythms for generative music systems.
- **Music analysis**: Compute distances, similarities, and transformations between musical objects.
- **Music theory research**: Explore modal, transpositional, and selectional properties of musical sets.
- **Rhythm generation**: Create complex rhythmic patterns for electronic, world, or experimental music.
- **Educational tools**: Demonstrate mathematical and algorithmic concepts in music theory.

## Getting Started


## Documentation (Doxygen)

This project uses [Doxygen](https://www.doxygen.nl/) to generate API documentation from source code comments.

### To generate documentation:

1. Make sure Doxygen is installed (`doxygen --version` should work in your terminal).
2. From the project root, run:
	```sh
	doxygen Doxyfile
	```
3. The generated HTML documentation will be in the `vectors/docs/html` directory. Open `vectors/docs/html/index.html` in your browser.

All public classes, functions, and files are documented using Doxygen-style comments in the source code.

## License

MIT License. See [LICENSE](LICENSE) for details.
