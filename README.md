# expected
Single header, work-in-progress implementation of `std::expected` with functional-style extensions.

Clang + GCC: [![Linux Build Status](https://travis-ci.org/TartanLlama/expected.png?branch=master)](https://travis-ci.org/TartanLlama/expected)
MSVC: [![Windows Build Status](https://ci.appveyor.com/api/projects/status/k5x00xa11y3s5wsg?svg=true)](https://ci.appveyor.com/project/TartanLlama/expected)

Full documentation available at [expected.tartanllama.xyz](https://expected.tartanllama.xyz)

### Compiler support

Tested on:

- Linux CI
  * clang 3.9
  * clang 3.8
  * clang 3.7
  * clang 3.6
  * clang 3.5
  * g++ 5.0
  * g++ 4.9
  * g++ 4.8
- Windows CI
  * MSVC 2015
  * MSVC 2017
- Linux manual
  * g++ 7.2
  * g++ 5.4

### Dependencies

Requires [Standardese](https://github.com/foonathan/standardese) for generating documentation.

Requires [Catch](https://github.com/philsquared/Catch) for testing. This is bundled in the test directory.

----------

[![CC0](http://i.creativecommons.org/p/zero/1.0/88x31.png)]("http://creativecommons.org/publicdomain/zero/1.0/")

To the extent possible under law, [Simon Brand](https://twitter.com/TartanLlama) has waived all copyright and related or neighboring rights to the `optional` library. This work is published from: United Kingdom.
