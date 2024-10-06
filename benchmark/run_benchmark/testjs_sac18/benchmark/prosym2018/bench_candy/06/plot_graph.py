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

base = getCsvResult('results/results.omit_frame.csv', 1)
omitFrame = getCsvResult('results/results.omit_frame.csv', 2)
files = getFileName('testcases')

baseDivFrame = []
for i in range(len(files)):
    baseDivFrame.append(omitFrame[1][i]/base[0][i])

# get error bar
omitFrameError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 1, base[0][i]))
    omitFrameError[0].append(abs(baseDivFrame[i] - data[0]))
    omitFrameError[1].append(abs(baseDivFrame[i] - data[1]))


# create graph
index = np.arange(len(files))
bar_width = 0.3

plt.grid(True, 'major', 'y', alpha=.3)
plt.bar(index, baseDivFrame, bar_width, yerr=omitFrameError)
plt.xticks(index, files, size='small', rotation=30, ha='right')
plt.show()
plt.savefig("graph.eps")
