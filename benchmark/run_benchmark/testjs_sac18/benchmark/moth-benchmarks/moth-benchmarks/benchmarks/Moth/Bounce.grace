// Copyright (c) 2001-2018 see AUTHORS file
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
//
//
// Adapted for Grace by Richard Roberts
//   2018, June
//

import "harness" as harness

type Ball = interface {
  bounce
}

class newBounce -> Benchmark {
  inherit harness.newBenchmark

  method benchmark -> Number {
    def random: Random = harness.newRandom

    def ballCount: Number = 100.asInteger
    var bounces: Number := 0.asInteger
    def balls: List = platform.kernel.Array.new (ballCount) withAll { newBall(random) }

    1.asInteger.to(50.asInteger) do { i: Number ->
      balls.do { ball: Ball ->
        ball.bounce.ifTrue {
          bounces := bounces + 1.asInteger
        }
      }
    }

    bounces
  }

  method verifyResult(result: Number) -> Boolean {
    result == 1331.asInteger
  }
}

class newBall(random: Random) -> Ball {
  var x: Number := random.next % 500.asInteger
  var y: Number := random.next % 500.asInteger
  var xVel: Number := (random.next % 300.asInteger) - 150.asInteger
  var yVel: Number := (random.next % 300.asInteger) - 150.asInteger

  method bounce -> Boolean {
    def xLimit: Number = 500.asInteger
    def yLimit: Number = 500.asInteger
    var bounced: Boolean := false

    x := x + xVel
    y := y + yVel

    (x > xLimit).ifTrue {
      x := xLimit
      xVel := 0.asInteger - xVel.abs
      bounced := true
    }

    (x < 0.asInteger).ifTrue {
      x := 0.asInteger
      xVel := xVel.abs
      bounced := true
    }

    (y > yLimit).ifTrue {
      y := yLimit
      yVel := 0.asInteger - yVel.abs
      bounced := true
    }

    (y < 0.asInteger).ifTrue {
      y := 0.asInteger
      yVel := yVel.abs
      bounced := true
    }

    bounced
  }
}

method newInstance -> Benchmark { newBounce }
