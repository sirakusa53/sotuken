import subprocess
import os

#BENCHMARK_BASEDIR = '../../benchmark/object-model/benchmarks'

BENCHMARKS = [
    {
        'dir': 'moth',
        'progs': [
            'Bounce-small',
            'CD-small',
            'DeltaBlue-small',
            'Havlak-small',
            'Json-small',
            'List-small',
            'Mandelbrot-small',
            'NBody-small',
            'Permute-small',
            'Queens-small',
            'Richards-small',
            'Sieve-small',
            'Storage-small',
            'Towers-small',
            'CD-dyn-small',
            'DeltaBlue-dyn-small'
        ]
    }
    # ,
    # {
    #     'dir': 'ours',
    #     'progs': [
    #         'dht11'
    #     ]
    # }
    # ,
    # {
    #     'dir': 'sunspider',
    #     'progs': [
    #         '3d-cube',
    #         '3d-morph',
    #         'access-binary-trees',
    #         'access-fannkuch',
    #         'access-nbody',
    #         'access-nsieve',
    #         'bitops-3bit-bits-in-byte',
    #         'bitops-bits-in-byte',
    #         'bitops-bitwise-and',
    #         'controlflow-recursive',
    #         'math-partial-sums',
    #         'math-spectral-norm',
    #         'string-base64',
    #         'string-fasta'
    #     ]
    #
    # }
]

def execute(heap_size_kb, sbc):
    heap_size_byte = heap_size_kb * 1024
    run_cmd = ["./ejsvm", "-u", "-m", str(heap_size_byte), sbc]
    try:
        ret = subprocess.call(run_cmd, stdout=subprocess.DEVNULL, timeout=180)
    except subprocess.TimeoutExpired:
        print("timeout");
        ret = 1
    print("%s %d => %d\n" % (sbc, heap_size_kb, ret))
    return ret

def find_min_heap(init_kb, sbc):
    left = 1
    right = init_kb

    while execute(right, sbc) != 0:
        left = right
        right += right

    while left + 1 < right:
        c = int((left + right) / 2)
        if execute(c, sbc) == 0:
            right = c
            print("success => [%d, %d)\n" % (left, right)) 
        else:
            left = c
            print("fail => [%d, %d)\n" % (left, right)) 

    return right

def main():
    result = []
    for suit in BENCHMARKS:
        suit_name = suit['dir']
        progs = suit['progs']
        dir = '../' + suit_name
        for prog in progs:
            prog_sbc = dir + '/' + prog + '.sbc'
            min_heap_kb = find_min_heap(1, prog_sbc)
            print("RESULT: %s %s %d\n" % (suit_name, prog, min_heap_kb))
            result.append((suit_name, prog, min_heap_kb))

    with open('min_heap.txt', 'w') as f:
        for r in result:
            print(r)
            f.write("%s %s %d\n" % r)

#ret = execute(400, "CD-small.js")
#ret = find_min_heap(512, "CD-small.js")
#print(ret)

main()

#ret = execute(700, "moth/CD-dyn-small.sbc")
#print(ret)



               
