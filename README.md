# IntervalAI

[![Build Status](https://travis-ci.com/GoodDeeds/IntervalAI.svg?branch=dev)](https://travis-ci.com/GoodDeeds/IntervalAI)

An abstract interpreter based on the integer interval domain for simple C programs

## Setup

### Prerequisites

* CBMC 5.8 (included as a submodule)
* g++ with C++11 support

### Building the project

Get the code. The directory containing this file shall be referred to as `$INTERVALAI_ROOT`

```bash
$ git clone --recurse-submodules https://github.com/GoodDeeds/IntervalAI $INTERVALAI_ROOT
```

Build CBMC

```bash
$ cd $INTERVALAI_ROOT/IntervalAI/cbmc/src
$ make
```

Build IntervalAI

```bash
$ cd $INTERVALAI_ROOT/IntervalAI
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Running IntervalAI

Go to `INTERVALAI_ROOT/IntervalAI/build`. Then, use

```bash
$ ./IntervalAI -m <mode> <goto-binary>
```

Information on modes available, and the restrictions on the input, can be found by using
```bash
$ ./IntervalAI -h
```

## License
This code is provided under the [MIT License](LICENSE).


**Note:** The code has a few [known bugs](https://github.com/GoodDeeds/IntervalAI/issues), which are in the process of getting resolved.