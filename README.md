# Interval Domain Abstract Interpreter

[![Build Status](https://travis-ci.com/GoodDeeds/interval-domain-abstract-interpreter.svg?branch=dev)](https://travis-ci.com/GoodDeeds/interval-domain-abstract-interpreter)

IntervalAI : An restricted Abstract Interpreter based on the integer interval domain

## Prerequisites

* CBMC 5.8 (included as a submodule)
* g++ with C++11 support

## Installing

Get the code. The directory containing this file shall be referred to as `$INTERVALAI_ROOT`

```
git clone --recurse-submodules git@github.com:GoodDeeds/IntervalAI.git
```

Build CBMC

```
cd $INTERVALAI_ROOT/IntervalAI/cbmc/src
make
```

Build IntervalAI

```
cd $INTERVALAI_ROOT/IntervalAI
mkdir build
cd build
cmake ..
make
```

## Running the program

```
cd $INTERVALAI_ROOT/IntervalAI/build
./IntervalAI -m <mode> <goto-binary>
```
