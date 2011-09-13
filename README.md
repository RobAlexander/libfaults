libfaults
=========

A standalone library for modelling faults on ground-truth values.

Faulty values can be applied in-place, i.e. overwriting the ground truth, or
returned as an extra variable.


Dependencies
------------

* [Boost][1] (tested with 1.42)
* [CMake][2] (tested with 2.8.1)

 [1]: http://www.boost.org/
 [2]: http://www.cmake.org/


Compiling
---------

_This assumes you are using the environment variable `$PSINSTALLPATH` to specify
the root installation directory._

Change into the build directory of libfaults, configure `cmake` then compile:

  $ cd libfaults/build
  $ cmake .. -DCMAKE_INSTALL_PREFIX=$PSINSTALLPATH
  $ make && make test && make install


Usage
-----

All properties for a fault model can be passed as parameters when constructed
and changed using the appropriate Get/Set methods during usage. Two key methods
are provided for getting faulty values:

- **GetFaulty(value)**
  Applies the fault model to the given value and returns the faulty value,
  leaving the original value unmodified.

- **MakeFaulty(value)**
  The same as GetFaulty, but modifies the true value in-place.

Fault models are templated classes supporting all signed/unsigned integers from
8 to 64 bits, along with floats, doubles and long doubles. The faulty values
generated are of the same type as the original values. For example, a random
fault model taking an integer value with always return integer values within a
given range, never a floating point type.


Fault Models
------------

- **Constant**:
  Always replaces the true value with a constant value.

- **Cycle**:
  Iterates through a value list, returning the next value in sequence each time
  GetFaulty/MakeFaulty is called. Wraps around when the last item is reached.

- **Noise**:
  Either offsets or scales the true value by a random amount within a given
  range.

- **Offset**:
  Offsets the true value by a constant amount.

- **Random**:
  Replaces the true value with either a random number within a given range or,
  if given a value list, with a random item from it.

- **Scale**:
  Scales the true value by a constant amount.


Example
-------

To offset a ground truth reading by +5.0:

```c++
OffsetFaultModel<double> fm = new OffsetFaultModel<double>(5.0);
double groundTruth = GetTrueValue();
fm.MakeFaulty(groundTruth);
```

Alternatively, using an extra variable:

```c++
OffsetFaultModel<double> fm = new OffsetFaultModel<double>(5.0);
double groundTruth = GetTrueValue();
double faultyValue = fm.GetFaulty(groundTruth);
```
