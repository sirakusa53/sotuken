Run ''-Os'' VMs:
  $ cp Os_VMs/* .
  $ ./inline_bench_time.sh

Run ''-O2'' VMs:
  $ cp O2_VMs/* .
  $ ./inline_bench_time.sh

Generate files:
result_(VM name)_(test name).txt ... Full execute time records
results_time.txt                 ... Average execute time records for all tests

Makefiles:
Makefiles/Makefile_O2_A          ... Makefile for "ejsvm_original" and "ejsvm_noinline" with -O2 opt
Makefiles/Makefile_O2_B          ... Makefile for "ejsvm_inlined" and "ejsvm_case_expansion" with -O2 opt
Makefiles/Makefile_Os_A          ... Makefile for "ejsvm_original" and "ejsvm_noinline" with -Os opt
Makefiles/Makefile_Os_B          ... Makefile for "ejsvm_inlined" and "ejsvm_case_expansion" with -Os opt