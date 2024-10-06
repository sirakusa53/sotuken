import subprocess
import yaml
import os
import sys
import re

DEFAULT_EJSVM = './ejsvm'
EJSVMRC = 'ejsvmrc.yaml'
ejsvmrc = None

if os.path.exists(EJSVMRC):
    with open(EJSVMRC) as file:
        ejsvmrc = yaml.safe_load(file)

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

def get_vm_params(jsfile):
    basename = os.path.basename(jsfile)
    if ejsvmrc == None:
        return []
    if jsfile in ejsvmrc:
        entry = ejsvmrc[jsfile]
    elif basename in ejsvmrc:
        entry = ejsvmrc[basename]
    else:
        return []
    if entry == None:
        return []
    return decode_and_split(entry)

def ejsvm_path(argv):
    if len(argv) < 2:
        return None
    if os.path.basename(argv[1]).startswith('ejsvm'):
        return argv[1]
    return None

params = get_vm_params(sys.argv[-1])
ejsvm = ejsvm_path(sys.argv)
if ejsvm:
    arg_start = 2
else:
    arg_start = 1
    ejsvm = DEFAULT_EJSVM    

cmd = [ejsvm]
cmd += params
cmd += sys.argv[arg_start:]

print(' '.join(cmd))
subprocess.run(cmd)

