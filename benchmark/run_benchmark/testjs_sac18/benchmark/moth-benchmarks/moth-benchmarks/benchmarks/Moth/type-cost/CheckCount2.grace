// Copyright (c) 2018 see AUTHORS.md file
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the 'Software'), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

import "../harness" as harness

type A = interface {
  a
}

type B = interface {
  b
}

type C = interface {
  c
}

type D = interface {
  d
}

type E = interface {
  e
}


def a = object {
  method a {counter} 
}

def b = object {
  method b {counter} 
}

def c = object {
  method c {counter} 
}

def d = object {
  method d {counter} 
}

def e = object {
  method e {counter} 
}

class newCheckCount {
  inherit harness.newBenchmark

  var count

  method benchmark {
      count := 0.asInteger

      1.asInteger.to(1000) do { i->
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
        foo(a,b,c,d,e)
      }
      count
  }

  method foo(xa : A, xb : B, xc, xd, xe) {
    count := count + 1
  }

  method verifyResult(result) {
    result == 10000
  }
}

method newInstance { newCheckCount }
