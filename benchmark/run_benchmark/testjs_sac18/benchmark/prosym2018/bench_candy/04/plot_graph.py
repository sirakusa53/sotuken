import re
import os
import numpy as np
import matplotlib.pyplot as plt

def getCsvResult(fileName, columnNum = 1):
    pattern = re.compile(r',')
    nameHandle = open(fileName, 'r')
    data = [[] for i in range(columnNum)]
    for i, line in enumerate(nameHandle):
        if (i == 0):
            continue
        result = pattern.split(line)
        for j in range(columnNum):
            data[j].append(float(result[j+1][:-1]))
    nameHandle.close()
    return data

def getFileName(path):
    files = []
    pattern = re.compile(r'.js')
    for fileName in os.listdir(path):
        files.append(pattern.sub('', fileName))
    return files

def getThreshold(filePath, num, baseNum):
    values = []
    pattern = re.compile(r'\ ')
    nameHandle = open(filePath, 'r')
    for line in nameHandle:
        if (line[0] == '='):
            values.append([])
        blocks = pattern.split(line)
        if (len(blocks) != 25):
            continue
        values[-1].append(float(blocks[5])) # total time
    values[num].sort()
    print(values[num][14], values[num][44], baseNum)
    return [values[num][14]/baseNum, values[num][44]/baseNum]

base = getCsvResult('results/results.old.csv', 1)
omitArguments = getCsvResult('results/results.omit_arguments.csv', 2)
omitFrame = getCsvResult('results/results.omit_frame.csv', 2)
files = getFileName('testcases')

baseDivLatest = []
for i in range(len(files)):
    baseDivLatest.append(omitArguments[0][i]/base[0][i])

baseDivArguments = []
for i in range(len(files)):
    baseDivArguments.append(omitArguments[1][i]/base[0][i])

baseDivFrame = []
for i in range(len(files)):
    baseDivFrame.append(omitFrame[1][i]/base[0][i])

# get error bar
latestError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_arguments/' + files[i] + '.txt'
    data = (getThreshold(filePath, 0, base[0][i]))
    latestError[0].append(abs(baseDivLatest[i] - data[0]))
    latestError[1].append(abs(baseDivLatest[i] - data[1]))

omitArgumentsError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_arguments/' + files[i] + '.txt'
    data = (getThreshold(filePath, 1, base[0][i]))
    omitArgumentsError[0].append(abs(baseDivArguments[i] - data[0]))
    omitArgumentsError[1].append(abs(baseDivArguments[i] - data[1]))

omitNewframeError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 1, base[0][i]))
    omitNewframeError[0].append(abs(baseDivFrame[i] - data[0]))
    omitNewframeError[1].append(abs(baseDivFrame[i] - data[1]))


# create graph
index = np.arange(len(files))
#bar_width = 0.3
bar_width = 0.7

plt.grid(True, 'major', 'y', alpha=.3)
plt.bar(index - bar_width, baseDivLatest, bar_width, yerr=latestError)
plt.bar(index, baseDivArguments, bar_width, yerr=omitArgumentsError)
#plt.bar(index + bar_width, baseDivFrame, bar_width, yerr=omitNewframeError)
#plt.bar(index, baseDivFrame, bar_width, yerr=omitNewframeError)
plt.xticks(index, files, size='small', rotation=30, ha='right')
plt.show()
plt.savefig("graph.eps")
