General
-------

A simple performance benchmark for the following use case:

- input data set (size can be set with `-e` in command)is composed of
  some numbers distributed in range 0 - upper bound (settable through
  `-r`)
- output is a vector of unique numbers from the input set, sorted in
  ascending order

The first implementation uses `std::vector`. Firstly, the vector is
populated with the input set. Then a `std::sort()` is called on the
whole vector range, followed by `std::unique()` and
`std::vector::resize()`.

The second implementation uses `std::set` and its properties (sorted,
element uniqueness). The implementation populates the set with the
input data and then reads back the data to a temporary storage.

Dependencies
------------

- compiler with C++11 support
- Boost `program_options` library

Example
-------

Example run::

  maciek@corsair:~/code/sorttest: ./sorttest -e 100000000 -r 100
  starting with values:
    data set size: 100000000
    value upper range: 100
  size before: 100000000
  size after: 101
  TIMER sort/unique/resize 5033947119
  size after: 101
  TIMER set 4303561564
