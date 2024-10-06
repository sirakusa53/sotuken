import subprocess
import os

BENCHMARK_BASEDIR = '../../benchmark/object-model/benchmarks'
JERRY_BUILD_BASEDIR = '/home/ugawa/ejs/jerry/jerryscript/vms'

BENCHMARKS = [
    # {
    #     'dir': 'moth',
    #     'progs': [
    #         'Bounce-small',
    #         'CD-small',
    #         'DeltaBlue-small',
    #         'Havlak-small',
    #         'Json-small',
    #         'List-small',
    #         'Mandelbrot-small',
    #         'NBody-small',
    #         'Permute-small',
    #         'Queens-small',
    #         'Richards-small',
    #         'Sieve-small',
    #         'Storage-small',
    #         'Towers-small',
    #         'CD-dyn-small',
    #         'DeltaBlue-dyn-small'
    #     ]
    # },
    {
        'dir': 'ours',
        'progs': [
            'dht11'
        ]
    },
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

    # }
]


def get_jerry_path(heap_size_kb):
    build_dir = JERRY_BUILD_BASEDIR + ('/build.%d' % heap_size_kb)
    jerry_path = build_dir + '/bin/jerry'
    return (jerry_path, build_dir)

def build(heap_size_kb):
    (jerry_path, build_dir) = get_jerry_path(heap_size_kb)
    if os.path.exists(jerry_path):
        print("%s exists\n" % jerry_path)
        return
    build_cmd = ['python3',
                 '../jerryscript/tools/build.py',
                 '--builddir', build_dir,
                 '--build-type', 'MinSizeRel',
                 '--mem-heap', str(heap_size_kb)]
    print("build %s\n" % jerry_path)
    subprocess.call(build_cmd, stdout=subprocess.DEVNULL)

def execute(heap_size_kb, js):
    (jerry_path, build_dir) = get_jerry_path(heap_size_kb)
    print("try %s with %d kb\n" % (js, heap_size_kb))
    build(heap_size_kb)
    run_cmd = [jerry_path, js]
    print("exec")
    ret = subprocess.call(run_cmd, stdout=subprocess.DEVNULL)
    print("ret = %d" % ret)
    return ret

def find_min_heap(init_kb, js):
    left = 1
    right = init_kb

    while execute(right, js) != 0:
        left = right
        right += right

    while left + 1 < right:
        c = int((left + right) / 2)
        if execute(c, js) == 0:
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
        dir = BENCHMARK_BASEDIR + '/' + suit_name
        for prog in progs:
            prog_js = dir + '/' + prog + '.js'
            min_heap_kb = find_min_heap(1, prog_js)
            print("RESULT: %s %s %d\n" % (suit_name, prog, min_heap_kb))
            result.append([suit_name, prog, min_heap_kb])

    with open('min_heap.txt', 'w') as f:
        for r in result:
            f.write("%s %s %d\n" % r)

#ret = execute(400, "CD-small.js")
#ret = find_min_heap(512, "CD-small.js")
#print(ret)

main()

               
