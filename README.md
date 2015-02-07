Ethernet Timing Harness (ETH)
=============================

Ethernet Timing Harness (ETH) is a very basic harness for timing the processing of Ethernet frames.  The harness will providing timing numbers for processing on one or two Ethernet interfaces.

## Compiling

Since the harness is so simple, there is no Makefile. To compile,

    g++ -std=c++11 -pthread -lpcap timing_harness.cpp -o timing_harness

## Extending

To extend the harness and make it time something useful, place processing code into the *callback1()* and *callback2()* functions.

## Copyright

> Copyright (c) 2015 Thomas S. Phillips.
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.
