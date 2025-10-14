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
- **Clough-Douthett patterns**: Rhythmic patterns based on the Clough-Douthett Algorithm.
- **Deep rhythms**: Patterns with multiplicity and distributed onsets.
- **Tihai**: North Indian rhythmic patterns with repetition and offset.

### Scale Class
- **Scale**: Encapsulates musical scales, supporting construction from positions or intervals, and transformations such as transposition, mode, inversion, and mirroring.


## TODO
- **Distances between vectors and rows of matrices**
- **Complexity vectors**
- **Extraction of vectors by their distance, cost function minimization**
- **Voicing, degree, modal interchange, modulation automation**
- **Rhythmic grid**
- **Chord class abstraction**


## Getting Started

1. Clone the repository and include the `src/` directory in your C++ project.
2. See the `examples/` directory for usage demonstrations and test cases.
3. Each header is self-contained and can be included as needed.

## License

MIT License. See [LICENSE](LICENSE) for details.

## Bibliography:

1. Albini, G. (2021). *Perché le note sono sette: Una storia dei fondamenti della musica tra matematica e percezione*. Fuori dal coro. Milano: Algama.

2. Arbonés, J., & Milrud, P. (2011). *L'armonia è questione di numeri: musica e matematica*. Milano: RBA Italia.

3. Arom, S. (2004). *African polyphony and polyrhythm: Musical structure and methodology*. Cambridge: Cambridge University Press.

4. Assayag, G., Feictinger, H. G., & Rodrigues, J. F. (2002). *Mathematics and music: a Diderot mathematical forum*. Berlin: Springer.

5. Benson, D. J. (2007). *Music: a mathematical offering* (3rd print., 2008). Cambridge: Cambridge University Press.

6. Boebinger, D., Norman-Haignere, S. V., McDermott, J. H., & Kanwisher, N. (2021). Music-selective neural populations arise without musical training. *Journal of Neurophysiology*, 125(6), 2237–2263.

7. Brent, J., & Barkley, S. (2011). *Modalogy: scales, modes, chords: the primordial building blocks of Music*. Milwaukee: Hal Leonard Corporation.

8. Burnham, B. R., Long, E., & Zeide, J. (2021). Pitch direction on the perception of major and minor modes. *Attention, Perception & Psychophysics*, 83(1), 399–414.

9. Caimmi, R., Franzon, A., & Tognon, S. (2017). *Intervalli musicali nella scala temperata a 12 note: interpretazione geometrica*. Canterano (RM): Aracne.

10. Callender, C. (2004). Continuous transformations. *Music Theory Online*, 10(3), 3.

11. Callender, C. (2007). Continuous harmonic spaces. *Journal of Music Theory*, 51(2), 277–332.

12. Callender, C., Quinn, I., & Tymoczko, D. (2008). Generalized voice-leading spaces. *Science*, 320(5874), 346–348.

13. Camiz, P., & Giansanti, A. (2019). *Fantalezioni di musimatefisica: un approccio musicale alle scienze esatte*. Milano: Tab.

14. Cohn, R. (1991). Properties and generability of transpositionally invariant sets. *Journal of Music Theory*, 35(1/2), 1–32.

15. Cohn, R. (1997). Neo-riemannian operations, parsimonious trichords, and their "tonnetz" representations. *Journal of Music Theory*, 41(1), 1–66.

16. Cohn, R. (1998). Introduction to neo-riemannian theory: a survey and a historical perspective. *Journal of Music Theory*, 42(2), 167–180.

17. Demaine, E. D., Gomez-Martin, F., Meijer, H., Rappaport, D., Taslakian, P., Toussaint, G. T., Winograd, T., & Wood, D. R. The distance geometry of deep rhythms and scales. [Manuscript or working paper].

18. Douthett, J., & Steinbach, P. (1998). Parsimonious graphs: A study in parsimony, contextual transformations, and modes of limited transposition. *Journal of Music Theory*, 42(2), 241–263.

19. Douthett, J., Hyde, M. M., & Smith, C. J. (2008). *Music Theory and Mathematics: Chords, Collections, and Transformations* (NED-New edition). Woodbridge: Boydell & Brewer.

20. Emmer, M. (2012). *Imagine Math: between culture and mathematics*. Milano: Springer.

21. Emmer, M. (2013). *Imagine Math 2: between culture and mathematics*. Milano: Springer.

22. Emmer, M., Abate, M., & Villarreal, M. (2015). *Imagine Math 4: between culture and mathematics*. Milano: Springer.

23. Fauvel, J., Flood, R., & Wilson, R. J. (2003). *Music and mathematics: from Pythagoras to fractals*. Oxford: Oxford University Press.

24. Forte, A. (1973). *The structure of atonal music*. New Haven: Yale University Press.

25. Garland, T. H., & Kahn, C. V. (1995). *Math and music: harmonious connections*. Palo Alto, CA: Dale Seymour.

26. Hall, R. W., & Tymoczko, D. (2007, July). Poverty and polyphony: A connection between economics and music. In *Bridges Donostia: Mathematics, Music, Art, Architecture, Culture* (pp. 259–268).

27. Harkleroad, L. (2006). *The math behind the music*. New York: Cambridge University Press.

28. Hasty, C. (1997). *Meter As Rhythm*. New York: Oxford University Press.

29. Hoffman, J. (2008). On pitch-class set cartography: Relations between voice-leading spaces and Fourier spaces. *Journal of Music Theory*, 52(2), 219–249.

30. Huron, D. (1989). Voice Denumerability in Polyphonic Music of Homogeneous Timbres. *Music Perception: An Interdisciplinary Journal*, 6(4), 361–382.

31. Huron, D. (2006). *Sweet Anticipation: Music and the Psychology of Expectation*. Cambridge, MA: The MIT Press.

32. Illiano, R., & Locanto, M. (2019). *Twentieth-century music and mathematics*. Turnhout: Brepols.

33. Jacoby, N., Tishby, N., & Tymoczko, D. (2015). An Information Theoretic Approach to Chord Categorization and Functional Harmony. *Journal of New Music Research*, 44(3), 219–244.

34. Jedrzejewski, F. (2006). *Mathematical theory of music*. Sampzon: Delatour France; Paris: Ircam-Centre Pompidou.

35. Johnson, T. A. (2008). *Foundations of diatonic theory: a mathematically based approach to music fundamentals*. Lanham, MD: Scarecrow Press.

36. Keith, M. (1991). *From Polychords to Polya: Adventures in Musical Combinatorics*. Princeton: Vinculum Press.

37. Kircher, A. (1650). *Musurgia universalis sive Ars magna consoni et dissoni*. Roma.

38. Kung, D. (2013). *How music and mathematics relate: course guidebook*. Chantilly, VA: Great Courses.

39. Levy, E. (1985). *A Theory of Harmony*. Albany: State University of New York Press.

40. Lewin, D. (1959). Re: Intervallic relations between two collections of notes. *Journal of Music Theory*, 3(2), 298–301.

41. Lewin, D. (2001). Special cases of the interval function between pitch-class sets X and Y. *Journal of Music Theory*, 45(1), 1–29.

42. Lewin, D. (2011). *Generalized musical intervals and transformations*. Oxford: Oxford University Press.

43. Loy, G. (2011). *Musimathics: the mathematical foundations of music*. Cambridge, MA; London: MIT Press.

44. Maor, E. (2018). *La musica dai numeri: musica e matematica, da Pitagora a Schoenberg*. Torino: Codice.

45. Mazzola, G. (1985). *Gruppen und Kategorien in der Musik: Entwurf einer mathematischen Musiktheorie*. Berlin: Heldermann.

46. Mazzola, G., Mannone, M., & Pang, Y. (2016). *Cool math for hot music: a first introduction to mathematics for music theorists*. Cham: Springer.

47. Mazzola, G. (2017). *The topos of music* (2nd ed.). Cham: Springer.

48. Micallef Grimaud, A., & Eerola, T. (2022). Emotional expression through musical cues: A comparison of production and perception approaches. *PLoS One*, 17(12), e0278593.

49. Odifreddi, P. (2005). *Penna, pennello e bacchetta: le tre invidie del matematico*. Roma; Bari: Laterza.

50. Palmer, S. E., Schloss, K. B., Xu, Z., & Prado-León, L. R. (2013). Music-color associations are mediated by emotion. *Proceedings of the National Academy of Sciences of the United States of America*, 110(22), 8836–8841.

51. Palmer, S. E., Langlois, T. A., & Schloss, K. B. (2016). Music-to-Color Associations of Single-Line Piano Melodies in Non-synesthetes. *Multisensory Research*, 29(1-3), 157–193.

52. Petrarca, S. (2010). *Matematica per la musica e il suono*. Roma: Aracne.

53. Quinn, I. (2006). General equal-tempered harmony (introduction and part I). *Perspectives of New Music*, 44(2), 114–158.

54. Quinn, I. (2007). General equal-tempered harmony: parts 2 and 3. *Perspectives of New Music*, 45(1), 4–63.

55. Roberts, G. E. (2016). *From music to mathematics: exploring the connections*. Baltimore, MD: Johns Hopkins University Press.

56. Robinson, T. (2006, April). The End of Similarity? Semitonal Offset as Similarity Measure. In *Annual meeting of the Music Theory Society of New York State*, Saratoga Springs, NY.

57. Russell, G. (1971). *The Lydian Chromatic Concept of Tonal Organization for Improvisation: For All Instruments*. New York: Concept Publishing Company.

58. Sivakumar, A., & Tymoczko, D. (2019). Intuitive Musical Homotopy: Algebraic, Geometric, Combinatorial, Topological and Applied Approaches to Understanding Musical Phenomena. [Working paper or manuscript].

59. Spence, C., & Di Stefano, N. (2022). Coloured hearing, colour music, colour organs, and the search for perceptually meaningful correspondences between colour and sound. *i-Perception*, 13(3), 20416695221092802.

60. Straus, J. N. (2003). Uniformity, balance, and smoothness in atonal voice leading. *Music Theory Spectrum*, 25(2), 305–352.

61. Straus, J. N. (2005). Voice leading in set-class space. *Journal of Music Theory*, 49(1), 45–108.

62. Toussaint, G. D. (2020). *The geometry of musical rhythm: what makes a "good" rhythm good?* Boca Raton, FL: CRC Press.

63. Tymoczko, D. (2004). Scale networks and Debussy. *Journal of Music Theory*, 48(2), 219–294.

64. Tymoczko, D. (2006). The geometry of musical chords. *Science*, 313(5783), 72–74.

65. Tymoczko, D. (2008). Scale theory, serial theory and voice leading. *Music Analysis*, 27(1), 1–69.

66. Tymoczko, D. (2008). Set-class similarity, voice leading, and the Fourier transform. *Journal of Music Theory*, 52(2), 251–272.

67. Tymoczko, D. (2009). Three Conceptions of Musical Distance. In *Mathematics and Computation in Music. MCM 2009. Communications in Computer and Information Science* (Vol. 38). Berlin, Heidelberg: Springer.

68. Tymoczko, D. (2011). *A Geometry of Music: Harmony and Counterpoint in the Extended Common Practice*. New York: Oxford University Press.

69. Walker, J., & Don, G. W. (2013). *Mathematics and music: composition, perception, and performance*. Boca Raton, FL: CRC Press.

70. Whiteford, K. L., Schloss, K. B., Helwig, N. E., & Palmer, S. E. (2018). Color, Music, and Emotion: Bach to the Blues. *i-Perception*, 9(6), 2041669518808535.