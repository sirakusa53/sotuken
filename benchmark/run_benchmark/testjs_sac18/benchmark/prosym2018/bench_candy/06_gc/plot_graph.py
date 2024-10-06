import re
import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties

def getCsvResult(fileName, columnNum = 1):
    pattern = re.compile(r',')
    nameHandle = open(fileName, 'r')
    data = [[] for i in range(columnNum)]
    for i, line in enumerate(nameHandle):
        if (i == 0):
            continue
        result = pattern.split(line)
        for j in range(columnNum):
            if (len(result[j+1]) != 1):
                data[j].append(float(result[j+1][:-1]))
            else:
                data[j].append(float(result[j+1][0]))
    nameHandle.close()
    return data

def getFileName(path):
    files = []
    pattern = re.compile(r'.js')
    for fileName in os.listdir(path):
        files.append(pattern.sub('', fileName))
    return files

def getThreshold(filePath, num, baseNum, isGC = False):
    values = []
    pattern = re.compile(r'\ ')
    nameHandle = open(filePath, 'r')
    for line in nameHandle:
        if (line[0] == '='):
            values.append([])
        blocks = pattern.split(line)
        if (len(blocks) != 25):
            continue
        # values[-1].append(float(blocks[5])) # total time
        if (isGC):
            values[-1].append(float(blocks[11])) # GC time
        else:
            values[-1].append(float(blocks[5])) # total time

    values[num].sort()
    print(values[num][14], values[num][44], baseNum)
    if (baseNum != 0):
        return [values[num][14]/baseNum, values[num][44]/baseNum]
    else:
        return [0, 0]

gcBase = getCsvResult('results/results.gc.csv', 1)
print('gcBase', gcBase)
gcFrame = getCsvResult('results/results.gc.csv', 2)
print('gcFrame', gcFrame)
base = getCsvResult('results/results.omit_frame.csv', 1)
print('base', base)
omitFrame = getCsvResult('results/results.omit_frame.csv', 2)
print('omitFrame', omitFrame)
files = getFileName('testcases')

# base
baseDivBase = []
for i in range(len(files)):
    baseDivBase.append(base[0][i]/base[0][i])

gcBaseDivBase = []
for i in range(len(files)):
    if (gcBase[0][i] != 0):
        gcBaseDivBase.append(gcBase[0][i]/base[0][i])
    else:
        gcBaseDivBase.append(0)

# omit
baseDivFrame = []
for i in range(len(files)):
    baseDivFrame.append(omitFrame[1][i]/base[0][i])

gcBaseDivFrame = []
for i in range(len(files)):
    if (gcBase[0][i] != 0):
        gcBaseDivFrame.append(gcFrame[1][i]/base[0][i])
    else:
        gcBaseDivFrame.append(0)


# get gc error bar
gcBaseError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 0, gcBase[0][i], isGC=True))
    gcBaseError[0].append(abs(gcBaseDivBase[i] - data[0]))
    gcBaseError[1].append(abs(gcBaseDivBase[i] - data[1]))

baseError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 0, base[0][i]))
    baseError[0].append(abs(baseDivBase[i] - data[0]))
    baseError[1].append(abs(baseDivBase[i] - data[1]))


gcFrameError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 1, gcFrame[1][i], isGC=True))
    gcFrameError[0].append(abs(gcBaseDivFrame[i] - data[0]))
    gcFrameError[1].append(abs(gcBaseDivFrame[i] - data[1]))

omitFrameError = [[],[]]
for i in range(len(files)):
    filePath = 'results/omit_frame/' + files[i] + '.txt'
    data = (getThreshold(filePath, 1, base[0][i]))
    omitFrameError[0].append(abs(baseDivFrame[i] - data[0]))
    omitFrameError[1].append(abs(baseDivFrame[i] - data[1]))

# create graph
index = np.arange(len(files))
bar_width = 0.3

#plt.grid(True, 'major', 'y', alpha=.3)
#plt.grid(which='major',color='black',linestyle='-')
fp = FontProperties(fname=r'./ipag.ttf', size=9)
plt.ylim([0, 1.3])
plt.grid(True, 'major', 'y', alpha=.3, linestyle='-')
plt.yticks([x * 0.1 for x in range(1, 14, 1)])
p1 = plt.bar(index - bar_width / 2, baseDivBase, bar_width, yerr=baseError, color='white', edgecolor='black')
gc1 = plt.bar(index - bar_width / 2, gcBaseDivBase, bar_width, color='black')
p2 = plt.bar(index + bar_width / 2, baseDivFrame, bar_width, yerr=omitFrameError, color='grey', edgecolor='black')
gc2 = plt.bar(index + bar_width / 2, gcBaseDivFrame, bar_width, color='black')
plt.xticks(index, files, size='small', rotation=30, ha='right')
plt.ylabel('実行時間の比', fontproperties=fp)
plt.legend((p1[0], p2[0], gc1[0]), ('最適化なし', '最適化あり', 'gc'), prop=fp)
plt.show()

