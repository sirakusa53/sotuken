# Introduction
This dir is for running all benchmark with 1 command.

# Run all benchmark

## set the benchmark dir
A
|- ejs
|- benchmark - run_benchmark - testcases
   	       		       	   |- 3d-cube.sbc
			           |- math-partial-sums.sbc
				   ...
## Run all benchmark for each dispatcb method
Steps 2,4,5 is the same in all cases.
The result is written in threaded-result or switch-result or opt-result.

### threaded code
1. $ cd /home/(username)/A/ejs/build-threaded
2. $ cp ../ejsvm/Makefile.template .
3. In Makefile, set var as follows.
   VMRUN_MEANS = threaded
   #CPPFLAGS += -DMEASURE_INSN_TIME
4. $ make
5. $ cd /home/(username)/A/benchmark/run_benchmark
6. $ bash ave10.sh threaded

### switch-case
1. $ cd /home/(username)/A/ejs/build-switch
2. $ cp ../ejsvm/Makefile.template .
3. In Makefile, set var as follows.
   VMRUN_MEANS = switch
   #CPPFLAGS += -DMEASURE_INSN_TIME
4. $ make
5. $ cd /home/(username)/A/benchmark/run_benchmark
6. $ bash ave10.sh switch

### concurrent use
0. Prepare for concurrent use according to README.md in ejs
1. $ cd /home/(username)/A/ejs/build-switch
2. $ cp ../ejsvm/Makefile.template .
3. In Makefile, set var as follows.
   VMRUN_MEANS = mix
   #CPPFLAGS += -DMEASURE_INSN_TIME
4. $ make
5. $ cd /home/(username)/A/benchmark/run_benchmark
6. $ bash ave10.sh opt (spec dir name)
In default, spec dir name is ts-spec.
spec dir is in ejs/opt-threaded-switch and has all spec file for all benchmark.

## output example
'''
====== opt-result/3d-cube.txt ======
../../ejs/build-opt/ejsvm -u testcases/3d-cube.sbc ../../ejs/opt-threaded-switch/ts-spec/3d-cube.spec
74.112
3.627
'''
the above is result of 3d-cube.js.
74.112 is total CPU time (msec)
3.627 is total GC time (msec)

# Get sbc file

1. Copy benchmark
   Copy benchmark dir which has js file into run_benchmark.
   Name the copied dir as 'testjs'.
2. Set var
   In make_sbc.sh, set TESTJS_DIR as follow.
   TESTJS_DIR="testjs"
3. $ bash make_sbc.sh
Then, all sbc file created in testcases.

# Result to excel

1. Run benchmark
2. $ bash output-excel-for-ave-time.sh threaded-result/
   or
   $ bash output-excel-for-ave-time.sh switch-result/
   or
   $ bash output-excel-for-ave-time.sh opt-result/

   output example
   '''
   DIR : opt-result/
   29.018 70.796 33.411 102.858 83.561 20.326 22.426 39.283 40.351 21.459 47.309 47.938 1970.171 67.217
   1.459 3.029 0 0 4.966 0 0 0 0 0 2.370 1.213 14.369 1.536
   '''
   CPU time : 29.018 70.796 33.411 102.858 83.561 20.326 22.426 39.283 40.351 21.459 47.309 47.938 1970.171 67.217
   This order is the same as the result of $ ls testjs/ and $ ls testcases/ and $ ls opt-result/ 
3. Copy the result and paste in excel.
4. Use excel function to split by spaces.