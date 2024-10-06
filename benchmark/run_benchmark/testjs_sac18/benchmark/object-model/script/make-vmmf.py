import yaml
import os
import re

BENCHMARK_LIST='Benchmarks.yaml'
VM_LIST='Vms.yaml'
VMS_MK='vms.mk'
TEST_SH='test.sh'
BC_MK='bc.mk'

def load_benchmarks():
    with open(BENCHMARK_LIST) as f:
        return yaml.load(f, Loader=yaml.FullLoader)

def load_vms():
    with open(VM_LIST) as f:
        return yaml.load(f, Loader=yaml.FullLoader)

def parse_heap_size(str):
    m = re.match("(\d+) ?([mMkK])?", str)
    if m:
        size = int(m.group(1))
        if m.group(2) != None:
            size *= 1024
        if m.group(2) == 'm' or m.group(2) == 'M':
            size *= 1024
    return size

def benchmark_list(benchmarks):
    lst = []
    for suit in benchmarks:
        dir = suit['dir']
        for p in suit['programs']:
            name = next(iter(p))
            opts = p[name]
            lst.append([dir, name, opts])
    return lst

def gc_default(gc, vm):
    if not 'CFLAGS' in vm:
        vm['CFLAGS'] = []
    if gc == 'bibop':
        vm['CFLAGS'].append('BIBOP_SEGREGATE_1PAGE')
        vm['CFLAGS'].append('BIBOP_CACHE_BMP_GRANULES')
        vm['CFLAGS'].append('BIBOP_2WAY_ALLOC')
        vm['CFLAGS'].append('BIBOP_FREELIST')
        vm['CFLAGS'].append('BIBOP_FST_PAGE')
        vm['CFLAGS'].append('MARK_STACK')
    if gc == 'native':
        vm['CFLAGS'].append('MARK_STACK')
        vm['_HEADER32'] = 'GC_MS_HEADER32'
    if gc == 'threaded':
        vm['CFLAGS'].append('GC_THREADED_BOUNDARY_TAG')
        vm['CFLAGS'].append('GC_THREADED_MERGE_FREE_SPACE')
        vm['CFLAGS'].append('GC_THREADED_BOUNDARY_TAG_SKIP_SIZE_CHECK')
        vm['CFLAGS'].append('MARK_STACK')
        vm['_HEADER32'] = 'GC_THREADED_HEADER32'

def set_word_size(word_size, vm):
    if '_HEADER32' not in vm:
        raise 'GC does not support 32 bit'
    vm['CFLAGS'].append(vm['_HEADER32'])
    vm['CFLAGS'].append('BIT_INSN32')
    vm['CFLAGS'].append('BIT_ALIGN32')
    vm['CFLAGS'].append('BIT_JSVALUE32')
        
def make_makefile(config, vm):
    if 'srcdir' in vm:
        srcdir = vm['srcdir']
    else:
        srcdir = config['ejsvm']
    vmdir = "%s/%s" % (config['dir'], vm['name'])
    os.makedirs(vmdir, exist_ok=True)
    mfname = "%s/Makefile" % vmdir
    if 'template' in vm:
        template = vm['template']
    else:
        template = config['template']
    
    with open(mfname, "w") as f:
        f.write('EJSVM_DIR=../../%s\n' % srcdir)
        with open(template) as ft:
            for line in ft.readlines():
                f.write(line)
        if 'GC' in vm:
            f.write("OPT_GC = %s\n" % vm['GC'])
            gc_default(vm['GC'], vm)
        if 'WORDSIZE' in vm:
            set_word_size(int(vm['WORDSIZE']), vm)
        if 'GC_CXX' in vm:
            f.write("GC_CXX = %s\n" % vm['GC_CXX'])
        if 'CFLAGS' in vm:
            for m in vm['CFLAGS']:
                f.write('CPPFLAGS += -D%s\n' % m)
        f.write('include $(EJSVM_DIR)/common.mk')

def make_vmsmk(config, benchmarks):
    with open(VMS_MK, 'w') as f:
        for vm in config['vms']:
            vmdir = '%s/%s' % (config['dir'], vm['name'])
            f.write('all: %s/ejsvm\n' % vmdir)
            f.write('%s/ejsvm:\n' % vmdir)
            f.write('\t$(MAKE) -j -C %s\n' % vmdir)
#            make_vm_bc(f, vmdir, benchmarks)

def make_vm_bc(f, vmdir, benchmarks):
    ejsc = 'java -jar %s/ejsc.jar -O' % vmdir
    blist = benchmark_list(benchmarks)
    for dir, name, opts in blist:
        jsfile = 'benchmarks/%s/%s.js' % (dir, name)
        bcfile = '%s/bc/%s/%s.sbc' % (vmdir, dir, name)
        f.write('all: %s\n' % bcfile)
        f.write('%s: %s/ejsvm %s\n' % (bcfile, vmdir, jsfile))
        f.write('\t%s $< -o $@\n' % ejsc)

def testsh_header(f, n):
    f.write("""
N=%d
PROGRAM=
SETCPU=
while :
do
    case "$1" in
        "-n") 
            shift;
            N=$1
            shift ;;
        "-p")
            shift;
            PROGRAM=$1
            shift ;;
        "-linux")
            SETCPU="misc/setcpu"
            shift ;;
        *) break;
    esac
done

function run_benchmark() {
    vmdir="$1"
    bcdir="$2"
    bcname="$3"
    timeout=$4
    opts="$5"

    if [ "x$PROGRAM" \!= "x" ]; then
        if [ "$bcdir" \!= "$PROGRAM" -a "$bcname" \!= "$PROGRAM" ]; then
            return
        fi
    fi

    mkdir -p "$vmdir/result"
    echo "BENCHMARK: $vmdir $bcname"

    sbc="bc/$bcdir/${bcname}.sbc"

    for ((i = 1; i < $N+1; i++))
    do
        result="$vmdir/result/${bcdir}_${bcname}_${i}.txt"
        (sudo $SETCPU timeout $timeout nice -n -20 $vmdir/ejsvm -u $opts $sbc) > $result
        error=$?
        echo -n "RESULT: "
        if [ $? = 0 ]; then
            grep "total CPU time" $result
        elif [ $? = 1 ]; then
            echo "runtime error"
        else
            echo "timeout"
        fi
    done

}
""" % n)

def make_testsh(config, benchmarks):
    with open(TEST_SH, 'w') as f:
        n = config['iteration'] if 'iteration' in config else 1
        testsh_header(f, n)
        for vm in config['vms']:
            vmdir = '%s/%s' % (config['dir'], vm['name'])
            for dir, name, opts in benchmark_list(benchmarks):
                optlst = []
                timeout = 60
                if opts:
                    for k in opts.keys():
                        v = opts[k]
                        if k == 'heapsize':
                            optlst.append('-m %d' % parse_heap_size(v))
                        elif k == 'timeout':
                            timeout = int(v)
                if 'CMDLINE' in vm:
                    optlst.append(vm['CMDLINE'])
                f.write('run_benchmark "%s" "%s" "%s" "%d" "%s"\n' %
                        (vmdir, dir, name, timeout, ' '.join(optlst)))

def make_bcmk(config, benchmarks):
    blist = benchmark_list(benchmarks)
    vmname = next(iter(config['vms']))['name']
    ejsc = '%s/%s/ejsc.jar' % (config['dir'], vmname)
    with open(BC_MK, 'w') as f:
        f.write('EJSC=java -jar %s\n' % ejsc)
        f.write('EJSCFLAGS=-O --out-bit32\n')
        for dir, name, opts in blist:
            jsfile = 'benchmarks/%s/%s.js' % (dir, name)
            bcfile = 'bc/%s/%s.sbc' % (dir, name)
            f.write('all: %s\n' % bcfile)
            f.write('%s: %s bc\n' % (bcfile, jsfile))
            f.write('\t$(EJSC) $(EJSCFLAGS) $< -o $@\n')

config = load_vms()
benchmarks = load_benchmarks()
os.makedirs(config['dir'], exist_ok=True)
for vm in config['vms']:
    make_makefile(config, vm)
make_vmsmk(config, benchmarks)
make_testsh(config, benchmarks)
make_bcmk(config, benchmarks)
