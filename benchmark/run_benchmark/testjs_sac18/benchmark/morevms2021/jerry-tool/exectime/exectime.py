import time
import subprocess
import yaml
import os

BENCHMARK_BASEDIR = '../../benchmark/object-model/benchmarks'
JERRY_BUILD_BASEDIR = '/home/ugawa/ejs/jerry/jerryscript/vms'

BENCHMARK_YAML = 'Benchmarks.yaml'

def load_benchmarks():
    with open(BENCHMARK_YAML) as f:
        return yaml.load(f, Loader=yaml.FullLoader)


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
    start = time.time()
    try:
        ret = subprocess.call(run_cmd, stdout=subprocess.DEVNULL, timeout=180)
    except subprocess.TimeoutExpired:
        return 0
    end = time.time()
    print("ret = %d" % ret)
    return (end - start) * 1000

def parse_size(s):
    if s.endswith('M'): 
        scale = 1024
        s = s[:-1]
    elif s.endswith('K'):
        scale = 1
        s = s[:-1]
    else:
        print("too small")
    return int(s) * scale
        
def exec_all(b):
    results = []
    for suit in b:
        name = suit['name']
        dir = BENCHMARK_BASEDIR + '/' + suit['dir']
        progs = suit['programs']
        for prog in progs:
            for prog_name in prog:
                if prog[prog_name] and 'heapsize' in prog[prog_name]:
                    heap_kb = parse_size(prog[prog_name]['heapsize'])
                else:
                    heap_kb = 10*1024
                js_name = dir + '/' + prog_name + '.js'
                t = execute(heap_kb, js_name)
                print('RESULT: %s %s %d\n' % (name, prog_name, int(t)))
                results.append((name, prog_name, int(t)))
    return results

def main():
    b = load_benchmarks()
    result = exec_all(b)
    with open('exec_time.txt', 'w') as f:
        for r in result:
            f.write("%s %s %d\n" % r)

main()



