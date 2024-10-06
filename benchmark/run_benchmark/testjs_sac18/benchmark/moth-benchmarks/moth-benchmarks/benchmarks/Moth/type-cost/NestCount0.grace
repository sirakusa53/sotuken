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


class newNestCount {
  inherit harness.newBenchmark

  var count

  method benchmark {
    count := 0.asInteger

    1.asInteger.to(1000) do { i->
      foo9(a,b,c,d,e)
    }
    
    count
  }

  method foo9(xa, xb, xc, xd, xe) {
    count := count + 1
    foo8(a,b,c,d,e)
  }

  method foo8(xa, xb, xc, xd, xe) {
    count := count + 1
    foo7(a,b,c,d,e)
  }

  method foo7(xa, xb, xc, xd, xe) {
    count := count + 1
    foo6(a,b,c,d,e)
  }

  method foo6(xa, xb, xc, xd, xe) {
    count := count + 1
    foo5(a,b,c,d,e)
  }

  method foo5(xa, xb, xc, xd, xe) {
    count := count + 1
    foo4(a,b,c,d,e)
  }

  method foo4(xa, xb, xc, xd, xe) {
    count := count + 1
    foo3(a,b,c,d,e)
  }

  method foo3(xa, xb, xc, xd, xe) {
    count := count + 1
    foo2(a,b,c,d,e)
  }

  method foo2(xa, xb, xc, xd, xe) {
    count := count + 1
    foo1(a,b,c,d,e)
  }

  method foo1(xa, xb, xc, xd, xe) {
    count := count + 1
    foo0(a,b,c,d,e)
  }

  method foo0(xa, xb, xc, xd, xe) {
    count := count + 1
  }

  method verifyResult(result) {
    result == 10000
  }
}

method newInstance { newNestCount }
