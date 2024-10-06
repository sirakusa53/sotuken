import yaml
import matplotlib.pyplot as plt
import numpy as np
import re
import itertools
import sys

VM_LIST='Vms.yaml'
BENCHMARK_LIST='Benchmarks.yaml'

def load_benchmarks():
    with open(BENCHMARK_LIST) as f:
        return yaml.load(f, Loader=yaml.FullLoader)

def load_vms():
    with open(VM_LIST) as f:
        return yaml.load(f, Loader=yaml.FullLoader)

def benchmark_list(benchmarks):
    lst = []
    for suit in benchmarks:
        dir = suit['dir']
        for p in suit['programs']:
            name = next(iter(p))
            opts = p[name]
            lst.append([dir, name, opts])
    return lst

###############################

COLORS3 = [
    '#d7301f',
    '#fdcc8a',
    '#fef0d9',
    '#ffffff',
    '#ffffff',
    '#ffffff',
    '#ffffff'
]

###############################

def extract_result_file(filename):
    try:
        with open(filename) as f:
            for line in f.readlines():
                m = re.match(".*total CPU time =\s+(\d+)\.\d+ msec, total GC time =\s+(\d+)\.\d+ msec.*#GC = (\d+).*", line)
                if m:
                    return (int(m.group(1)), int(m.group(2)), int(m.group(3)))
    except:
        pass
    return None

def extract_result_benchmark(result_prefix, vm, config):
    cputime = []
    gctime = []
    n = int(config['iteration'])
    for i in range(1, n + 1):
        result_file = "%s%d.txt" % (result_prefix, i)
        r = extract_result_file(result_file)
        if r:
            c, g, gccount = r
            cputime.append(c)
            gctime.append(g)
    if len(cputime) == 0:
        return (np.array([0.0, 0.0, 0.0]), np.array([0.0, 0.0, 0.0]), 0)
    return (np.percentile(cputime, [50, 25, 75]),
            np.percentile(gctime, [50, 25, 75]),
            gccount)

def extract_result_vm(vm, config, benchmark_list):
    result = []
    for dir, bench, _ in benchmark_list:
        result_prefix = (
            "%s/%s/result/%s_%s_" % (config['dir'], vm['name'], dir, bench))
        r = extract_result_benchmark(result_prefix, vm, config)
        result.append(r)
    return result

def extract_result(config, benchmark_list):
    result = []
    vmlist = []
    for vm in config['vms']:
        r = extract_result_vm(vm, config, benchmark_list)
        result.append(r)
        vmlist.append(vm)
    return (result, vmlist)

def normalise_datapoint(data, baseline):
    return [x/baseline[0][0] for x in data]

def normalise_vm(baseline, vmdata):
    return [normalise_datapoint(x, y) for x, y in
            itertools.zip_longest(vmdata, baseline)]

def normalise(result):
    return [normalise_vm(result[0], x) for x in result]

def plot_figure(data, vmlist, blist):
    width = 0.8 / len(data)
    # total time
    for (vm_i, vm) in enumerate(data):
        left = []
        height = []
        yerr_up = []
        yerr_low = []
        for (prog_i, prog) in enumerate(vm):
            left.append(prog_i + vm_i * width)
            height.append(prog[0][0])
            yerr_up.append(prog[0][2] - prog[0][0])
            yerr_low.append(prog[0][0] - prog[0][1])
        plt.bar(left, height, width = width,
                color = COLORS3[vm_i], edgecolor = 'black',
                yerr = (yerr_up, yerr_low), label = vmlist[vm_i]['name'],
                error_kw = {"elinewidth": 0.5, "capsize": 1, "capthick": 0.5})
    # GC
    for (vm_i, vm) in enumerate(data):
        left = []
        height = []
        yerr_up = []
        yerr_low = []
        for (prog_i, prog) in enumerate(vm):
            left.append(prog_i + vm_i * width)
            height.append(prog[1][0])
        plt.bar(left, height, width = width,
                color = 'black', edgecolor = 'black')

    plt.xticks([i for i,_ in enumerate(blist)],
               [n for _, n, _ in blist], rotation=270)
    plt.legend()
    plt.tight_layout()
    plt.savefig('exectime.eps', format='eps')        

def print_time(data, vmlist, blist):
    sys.stdout.write('total\n')
    for prog_i, prog in enumerate(blist):
        dir, bname, _ = blist[prog_i]
        sys.stdout.write('%s' % bname)
        for vm_i, vmname in enumerate(vmlist):
            sys.stdout.write('\t%f' % data[vm_i][prog_i][0][0])
        sys.stdout.write('\n')
    sys.stdout.write('GC\n')
    for prog_i, prog in enumerate(blist):
        dir, bname, _ = blist[prog_i]
        sys.stdout.write('%s' % bname)
        for vm_i, vmname in enumerate(vmlist):
            sys.stdout.write('\t%f' % data[vm_i][prog_i][1][0])
        sys.stdout.write('\n')

def print_gccount(data, vmlist, blist):
    sys.stdout.write('GC count\n')
    for prog_i, prog in enumerate(blist):
        dir, bname, _ = blist[prog_i]
        sys.stdout.write('%s' % bname)
        for vm_i, vmname in enumerate(vmlist):
            sys.stdout.write('\t%f' % data[vm_i][prog_i][2])
        sys.stdout.write('\n')

def main():
    config = load_vms()
    benchmarks = load_benchmarks()
    blst = benchmark_list(benchmarks)
    result, vmlist = extract_result(config, blst)
#    data = normalise(result)
#    plot_figure(data, vmlist, blst)
    data = result
    print_time(data, vmlist, blst)
#    print_gccount(result, vmlist, blst)


main()
