# Moth-benchmarks modified for ejs

source: `git@github.com:gracelang/moth-benchmarks.git`

## Dirs

  *  `moth-benchmarks`:  same as upstream
  * `benchmarks`: modified benchmarks for eJS.  Makefile is available.

## Makefile

### Options

  * `EJSC`: path to ejsc.jar
  
### targets  

  * `all`: creates all sbc files.
  * `alljs`: creates a single .js file to be executed with eJS for each benchmark.
  * `nodejs`:creates a single .js file to be executed with Node.js for each benchmark.
    *  `node --no-opt $1` to execute with no-JIT node.JS

## Benchmarks

  * DeltaBlue
    * heapsize: 100MB
  * Richards
    * heapsize: 1MB
  * Havlak
    * heapsize: 100MB
  * CD
    * heapsize 10MB
  * Bounce
     * heapsize 1MB
  * List
    * heapsize: 1MB
   * Mandelbrot
    * heapsize:1MB
  * Mandelbrot
    * heapsize: 1MB
  * Permute
    * heapsize: 1MB
  * Permute
    * heapsize: 1MB
  * Queens:
    * heapsize: 1MB
  * Sieve
    * heapsize: 1MB
  * Storage
    * heapsize: 10MB
  * Towers:
    * heapsize: 1MB

## Note

Json cannot be executed due to the limitation of codeloader that cannot load
a 'string' instruction with a long string constant.

