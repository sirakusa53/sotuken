import os
import shutil
import subprocess
import sys
import yaml
import re
import numpy as np
import matplotlib.pyplot as plt

PYTHON       = sys.executable
EJS_DIR      = "ejs"
JS_DIR       = "benchmarks"
VM_DIR       = "vms"
MAKEFILE_DIR = "makefiles"
HC_DIR       = "hc"
OHC_DIR      = "ohc"
RESULT_DIR   = "results"


TIME_EXEC_COUNT = 5
BENCHMARKS = [f[:-3] for f in os.listdir(JS_DIR) if f.endswith(".js")]

class EJSVMRC:
    def __init__(self, rc_path):
        if os.path.exists(rc_path):
            with open(rc_path) as file:
                self.rc = yaml.safe_load(file)
        else:
            self.rc = None

    def decode_and_split(params):
        result = []
        for p in params:
            param = re.split(r' +', p)
            if param[0] == '-m':
                if param[1][-1] == 'K' or param[1][-1] == 'k':
                    param[1] = str(int(param[1][:-1]) * 1024)
                elif param[1][-1] == 'M' or param[1][-1] == 'm':
                    param[1] = str(int(param[1][:-1]) * 1024 * 1024)
            result += param
        return result
    
    def get_vm_params(self, prog_path):
        basename = os.path.basename(prog_path)
        if self.rc == None:
            return []
        if prog_path in self.rc:
            entry = self.rc[prog_path]
        elif basename in self.rc:
            entry = self.rc[basename]
        else:
            return []
        if entry == None:
            return []
        return EJSVMRC.decode_and_split(entry)

class VM:
    def __init__(self, name, vm_dir):
        self.name = name
        self.vm_dir = vm_dir
        self.ohc_dir = None
        self.options = []

    def set_ohc_dir(self, path):
        self.ohc_dir = path

    def add_option(self, options):
        self.options += options

    def get_bc_dir(self):
        return self.vm_dir + "/sbc"

    def get_spec_file(self):
        return self.vm_dir + "/ejsvm.spec"

    def sbc_path(self, prog):
        return self.get_bc_dir() + "/" + prog + ".sbc"

    def vm_path(self):
        return self.vm_dir + "/ejsvm"

    def run(self, options, prog, output_path = None):
        vm_path = self.vm_path()
        sbc_path = self.sbc_path(prog)
        options += ejsvmrc.get_vm_params(sbc_path)
        cmd = [vm_path] + options + [sbc_path]
        if output_path:
            with open(output_path, 'w') as f:
                subprocess.call(cmd, stdout=f)
        else:
            subprocess.call(cmd)
    
    def run_dump_hcg(self, prog, output_dir):
        hc_path = "%s/%s.hc" % (output_dir, prog)
        self.run(["--dump-hcg", hc_path], prog)

    def measure_execution_time(self, prog, result_path):
        options = ["-u"]
        options += self.options
        if self.ohc_dir:
            ohc_path = "%s/%s.ohc" % (self.ohc_dir, prog)
            options += ["--load-hcg", ohc_path]
        self.run(options, prog, result_path)
        
def build_vm(vm_name):
    vm_dir = VM_DIR + "/" + vm_name
    makefile = MAKEFILE_DIR + "/Makefile." + vm_name
    makefile_path = vm_dir + "/Makefile"
    os.makedirs(vm_dir, exist_ok = True)
    if not os.path.exists(makefile_path):
        shutil.copy(makefile, makefile_path)
    subprocess.call(["make", "-j"], cwd = vm_dir)
    return VM(vm_name, vm_dir)

def compile_js(prog, output_dir, spec_file):
    ejsc = EJS_DIR + "/ejsc/js/ejsc.js"
    ejsc_command = ["node", ejsc, "--spec", spec_file, "-O", "-o"]
    ejsc_command.append("%s/%s.sbc" % (output_dir, prog))
    ejsc_command.append("%s/%s.js" % (JS_DIR, prog))
    os.makedirs(output_dir, exist_ok = True)
    subprocess.call(ejsc_command)

def optimize_hcg(prog, hc_dir, ohc_dir):
    hc_path = "%s/%s.hc" % (hc_dir, prog)
    ohc_path = "%s/%s.ohc" % (ohc_dir, prog)
    hcopt_path = "%s/tools/hcopt.py" % EJS_DIR
    cmd = [PYTHON, hcopt_path, "--ohc", ohc_path, hc_path]
    print(cmd)
    subprocess.call(cmd)
    
def make_vms(vm_names):
    vms = {}
    for vm_name in vm_names:
        vms[vm_name] = build_vm(vm_name)
    return vms

def compile_progs(vms, progs):
    for vm_name in vms:
        vm = vms[vm_name]
        for prog in progs:
            compile_js(prog, vm.get_bc_dir(), vm.get_spec_file())
        
def collect_and_optimize_hcg(progs):
    os.makedirs(HC_DIR, exist_ok = True)
    os.makedirs(OHC_DIR, exist_ok = True)
    vm = build_vm("dump")
    for prog in progs:
        compile_js(prog, vm.get_bc_dir(), vm.get_spec_file())
        vm.run_dump_hcg(prog, HC_DIR)
        optimize_hcg(prog, HC_DIR, OHC_DIR)
            
def do_benchmarking(vms, progs, result_dir, count):
    os.makedirs(result_dir, exist_ok = True)
    for vm_name in vms:
        vm = vms[vm_name]
        for prog in progs:
            for i in range(count):
                result_path = ("%s/%s_%s_%d.txt" %
                               (result_dir, vm_name, prog, i))
                vm.measure_execution_time(prog, result_path)

class Results:
    def load_results(self, vms, progs, result_dir, parser):
        results = []
        for vm_name in vms:
            for prog in progs:
                for f in [result_dir + '/' + f for f in os.listdir(result_dir)
                          if re.match("%s_%s_\d+.txt" % (vm_name, prog), f)]:
                    result = parser.parse(f)
                    if result:
                        results.append((vm_name, prog, result))
        return results

    def get(self, vm_name, prog, index, normalize, q):
        if normalize:
            baseline = self.get(normalize, prog, 0, None, 50)
        else:
            baseline = 1
        data = []
        for r in [r for v, p, r in self.results if v == vm_name and p == prog]:
            data.append(r[index] / baseline)
        if len(data) == 1:
            return data[0]
        elif len(data) > 2:
            return np.percentile(data, q)
        else:
            return 0
    
class TimeResultParser:
    def parse(self, file_path):
        with open(file_path) as f:
            for line in f.readlines():
                m = re.match(r'.*total CPU time =\s+(\d+)\.\d+ msec, total GC time =\s+(\d+)\.\d+ msec.*#GC = (\d+).*', line)
                if m:
                    return (int(m.group(1)), int(m.group(2)), int(m.group(3)))

class TimeResults(Results):
    def __init__(self, vms, progs, result_dir):
        parser = TimeResultParser()
        self.results = self.load_results(vms, progs, result_dir, parser)
    
    def get_total(self, vm_name, prog, normalize = None, q = 50):
        return self.get(vm_name, prog, 0, normalize, q)

    def get_gc(self, vm_name, prog, normalize = None, q = 50):
        return self.get(vm_name, prog, 1, normalize, q)

class CacheHitParser:
    def parse(self, file_path):
        with open(file_path) as f:
            bytes_meta = 0
            for line in f.readlines():
                m = re.match(r'total count *\d+ hit *\d+ \(ratio (0.\d+)\)', line)
                if m:
                    cache_hit = float(m.group(1))
                m = re.match(r'  type 11 a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_prop = int(m.group(1))
                m = re.match(r'  type 06 a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_simpleobj = int(m.group(1))
                m = re.match(r'  type 18 a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_meta += int(m.group(1))
                m = re.match(r'  type 19 a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_meta += int(m.group(1))
                m = re.match(r'  type 1c a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_meta += int(m.group(1))
                m = re.match(r'  type 1d a.max = +\d+ a.bytes = +(\d+) .*', line)
                if m:
                    bytes_meta += int(m.group(1))
            return (cache_hit, bytes_prop + bytes_simpleobj, bytes_meta)
                             
                    
class CacheHitResults(Results):
    def __init__(self, vms, progs, result_dir):
        parser = CacheHitParser()
        self.results = self.load_results(vms, progs, result_dir, parser)
        print([(vm, prog, r) for vm, prog, r in self.results if prog == 'Mandelbrot-small'])
    
def plot_time_figure(results, vms, output_path):
    width = 0.8 / len(vms)
    for (i, vm_name) in enumerate(vms):
        left = []
        total = []
        gc = []
        yerr_u = []
        yerr_d = []
        for (j, prog) in enumerate(progs):
            left.append(j + i * width)
            m = results.get_total(vm_name, prog, "base", 50)
            total.append(m)
            yerr_u.append(results.get_total(vm_name, prog, "base", 70) - m)
            yerr_d.append(m - results.get_total(vm_name, prog, "base", 25))
            gc.append(results.get_gc(vm_name, prog, "base", 50))
        plt.bar(left, total, width = width, edgecolor = 'black',
                yerr = (yerr_u, yerr_d),
                label = vm_name,
                error_kw = {'elinewidth': 0.1, 'capsize': 1, 'capthick': 0.5})
        plt.bar(left, gc, width = width, color = 'black', edgecolor = 'black')
    plt.xticks([i for i in range(len(progs))], progs, rotation = 270)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_path, format = 'eps')
    plt.cla()

def generate_figure(vms, progs, result_dir):
    results = TimeResults(vms, progs, result_dir)
    plot_time_figure(results, vms, progs, "time.eps")
    
def plot_single_figure(results, vms, progs, index, output_path,
                       normalize = None):
    width = 0.8 / len(vms)
    for (i, vm_name) in enumerate(vms):
        left = []
        vals = []
        for (j, prog) in enumerate(progs):
            left.append(j + i * width)
            m = results.get(vm_name, prog, index, normalize, 50)
            vals.append(m)
        print(vals)
        plt.bar(left, vals, width = width, edgecolor = 'black',
                label = vm_name)
    plt.xticks([i for i in range(len(progs))], progs, rotation = 270)
#    plt.legend()
    plt.tight_layout()
    plt.savefig(output_path, format = 'eps')
    plt.cla()

def generate_cache_hit_figure(vms, progs, result_dir):
    results = CacheHitResults(vms, progs, result_dir)
    plot_single_figure(results, vms, progs, 0, "cache.eps")
    plot_single_figure(results, vms, progs, 1, "objsize.eps")
    plot_single_figure(results, vms, progs, 2, "metasize.eps")

def main():
    collect_and_optimize_hcg(BENCHMARKS)

    time_vms = make_vms(["base", "dyn", "load"])
    compile_progs(time_vms, BENCHMARKS)
    time_vms["load"].set_ohc_dir(OHC_DIR)
    do_benchmarking(time_vms, BENCHMARKS, RESULT_DIR + "/time", TIME_EXEC_COUNT)
    generate_figure(time_vms, BENCHMARKS, RESULT_DIR + "/time")

    prof_vms = make_vms(["base-prof", "dyn-prof", "load-prof"])
    compile_progs(prof_vms, BENCHMARKS)
    prof_vms["load-prof"].set_ohc_dir(OHC_DIR)
    for vm in prof_vms:
        prof_vms[vm].add_option(["--gc-prof", "--ic-prof"])
    do_benchmarking(prof_vms, BENCHMARKS, RESULT_DIR + "/prof", 1)
    generate_cache_hit_figure(prof_vms, BENCHMARKS, RESULT_DIR + "/prof")
    

ejsvmrc = EJSVMRC(JS_DIR + "/ejsvmrc.yaml")
main()
