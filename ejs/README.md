# eJS -- JavaScript for embedded systems.

eJS is a framework to generate JavaScript VMs that are specialised
for applications.

## Contents

* `ejsvm` -- eJSVM, JavaScript virtual machine (core)
* `vmdl` -- VMDL compiler to generate specialised type-based dispatcher used in eJSVM
* `vmgen` -- VMgen is the previous version of VM generator. VMDL compiler is the current mainstream.
* `ejsc` -- eJS compiler to compile JavaScript programs into bytecode files executed by eJSVM.
* `ejsi` -- eJS interpreter interface.

## Quick Start

### Check requirements
Following build tools are required.

* C compiler (GCC or Clang)
* JDK 11 or higher
* make
* Ant
* sed
* Python 3

Following tools are optional.

* Coccinelle
* Oniguruma Regexp library
* Node 14.x (npm 6.x)

### Prepare external libraries

Download the following libraries into `ejsc/libs` if they are not
contained in the repository.

* antlr-4.5.3-complete.jar
* javax.json-1.0.4.jar

### Build

1. Create build directory
```
$ mkdir build.debug
$ copy build.debug
```

2. Create `Makefile` from template `ejsvm/Makefile.template`
```
$ cp ../ejsvm/Makefile.template Makefile
```

3. Edit `Makefile`. The `commands` and `paths` section may need to be changed.

4. Build by `make`.
```
$ make -j
```

5. Followings are generated.

If you build eJS not for MBED:
  * `ejsvm` -- VM
  * `ejsc.jar` -- compiler
  * `ejsi` -- Interpreter user interface

If you build eJS for MBED:
  * `ejsvm.bin` -- VM
  * `connect_mbed` -- interface to communicate VM running on MBED

### execute

#### Interpreter mode
Simply execute `ejsi` in the build directory.
```
$ ejsi
```

#### Compile & run (using babel parser)
The following steps demonstrate compilation and execution of a JavaScript
program `a.js`. Paths to `ejsc.js`, `ejsc.jar` and `ejsvm` should be replaced
appropriately.

Caution: You can't move `ejsc.js` from `ejsc/js`.
`ejsc.jar` and `ejsvm` can be moved.

0. preparation (only before using first time)
```
$ cd ejsc/js
$ npm install
```

1. compile to SBC style bytecode
```
$ node ejsc/js/ejsc.js -O -o a.sbc a.js
```

2. execute
```
$ build/ejsvm a.sbc
```

#### Compile & run (deprecated)
This procedure has been deprecated as it uses a broken old js pacer.

1. compile to SBC style bytecode
```
$ java -jar ejsc.jar -O -o a.sbc a.js
```

2. execute
```
$ ./ejsvm a.sbc
```

#### Running on MBED
TODO: Fill this section.

```
$ mount /path/to/MBED
$ cp ejsvm.bin /path/to/MBED/ejsvm.bin
$ sync /path/to/MBED/ejsvm.bin
$ ./connect_mbed /dev/ttyMBED
```

## eJS VM

### Build option

**See comments in `Makefile.template` for the details.**

* General options
  * `USE_OBC=true/false`: Enable OBC support.
  * `USE_SBC=true/false`: Enable SBC support.

* Word size options
  * `BITWIDTH_INSN = 32 / 64`: Use 32 or 64 bit layout of internal and OBC instructions.
  * `BITWIDTH_JSVALUE = 32 / 64`: Use 32 or 64 bit layout of JSValue.
    If you choose 32 bit layout, pointer size should also be 32bit (`-m32` compiler and linker options are required).
  * `BITWIDTH_ALIGN = 32 / 64`: Alignment heap objects in 32 or 64 bit boundary. Handcrafted code does not support this option.

### Usage

```
ejsvm [options] file1 file2 ...
```

Files are executed in the order of parameter. Files with `sbc`
extensions are executed as SBC files if ejsvm supports SBC format.
Other files (and all files for ejsvm without SBC support) are
executed as OBC files.

#### Options

* General options
  * `-s size`: stack size in words. (default: 50K)
  * `--threshold bytes`: gc threshold size in bytes. (default: gc-dependence)
    * Note: This option may does not work in bibop gc.
  * `-m size`: heap size in bytes. (default: 1M)

* Profiling options for eJS users (available when built with `PROFILE` flag)
  * `-profile`: Print profiling information.
  * `--poutput filename`: Change the output file of `-profile` to `filename`. (default: standard output)
  * `--coverage`: Print coverage information of instructions with log flags.
  * `--icount`: Print execution count of each instruction (count only instructions with log flags).
  * `--forcelog`: Profiling as if all instructions have log flags.
  * `--bpoutput filename`: Change the output file of `-profile` about builtin functions to `filename`. (default: standard output)
    * Note: This option only works in vmdl build.
  * `--pcntuniq`: Remove duplicate output of `-profile`.

* Debug options (available when built with `DEBUG` flag)
  * `-l`: Print the result of the evaluation of the last expression.
  * `-f`: Print function table.
  * `-t`: Print execution trace.
  * `-a`: Same as the combination of the above (`-l -f -t`).

* Profiling options for VM developers
  * `-u`: Print execution times and summary of GC information.
  * `--hc-prof`: Print hidden class graph information. (available when built with `HC_PROF` flag)
  * `--shape-prof`: Print object shape information. (available when built with `SHAPE_PROF` flag)
  * `--gc-prof`: Print GC information (available when built with `GC_PROF` flag)
  * `--ic-prof`: Print inline cache information. (available when built with `IC_PROF` flag)
  * `--as-prof`: Print allocation site cache information. (available when built with `AS_PROF` flag)
  * `--iccprof filename`: Print object shape information. (available when built with `SHAPE_PROF` flag)

* Other flags
  * `-R`: REPL mode. (not for users)
  * `--buildinfo`: Print some build time information. (available when built with `PRINT_BUILD_INFO` flag)


## eJS Compiler

### Build option

When building the eJS compiler separately, i.e., building with `ant`
in the `ejsc` directory, the following properties for ant are available.
These properties are specified appropriately when building all components
altogether in the build directory.

* `specfile`: Path to the default spec file. (default: ''src/ejsc/default.spec'')
* `vmgen`: Path to `vmgen.jar` or `vmdlc.jar`. (default: ''../ejsvm/vmgen/vmgen.jar'')

### Usage

```
java -jar ejsc.jar [options] source1.js source2.js ...
```

eJSC compiles JavaScript programs `source1.js`, `source2.js`, ...
into a single bytecode file. The produced bytecode file executes
`source1.js`, `source2.js`, ... in this order. If `-log` option is
specified before some source files, the immediate following source file
is compiled so that executions of instructions produced from the source
file are logged.

#### Options

* output 
  * `-o <filename>`: Output to `filename`.  (default: `source1.sbc`)
  * `--out-obc` (prefix is double minus): Output OBC (binary) format instead of SBC.

* optimization
  * `-O`: Recommended set of optimizations.  (same as `--bc-opt const:cce:copy:rie:dce:reg:rie:dce:reg -opt-g3`)
  * `--bc-opt <optimizers>` (prefix is double minus): BC based optimizations. `<optimizers>` is a series of the following optimizers.
    * `const`: Constant propagation and using superinstructions
    * `cce`: Common constant loading elimination
    * `copy`: Copy propagation
    * `rie`: Redundant instruction elimination
    * `dce`: Dead code elimination
    * `reg`: Register (re-)assignment
  * `-opt-g3`: Allocate registers for local variables and arguments if possible.
* misc
  * `--spec <specfile>`: Specify the specfile created as `ejsvm.spec` in the process of building VM.  (default: normal instruction set with no superinstructions)
  * `-fn n`: (For REPL) Assume the function number starts from `n`.
  * `-log source.js`: Compile `source.js` using logging instructions.
* debug
  * `--estree`: print ESTree
  * `--iast`: print iAST
  * `--analyzer`: print result of some AST-based analysis (???)
  * `--show-llcode`: print low-level internal code
  * `--show-opt`: print details of optimizations
