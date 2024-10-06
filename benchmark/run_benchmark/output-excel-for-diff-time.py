import sys
import re

# コマンドライン引数からファイル名を取得
if len(sys.argv) < 2:
    print("Usage: python process_data.py <input_file>")
    sys.exit(1)

input_file = sys.argv[1]

# ファイルからテキストデータを読み込み
try:
    with open(input_file, 'r') as file:
        input_text = file.read()
        print(input_text)
except FileNotFoundError:
    print(f"File '{input_file}' not found.")
    sys.exit(1)

# 正規表現を使用してデータを抽出
results_left = re.findall(r'< total CPU time = (\d+\.\d+) msec', input_text)
results_right = re.findall(r'> total CPU time = (\d+\.\d+) msec', input_text)
output = ' '.join(map(str, results_left))
print(output)
output = ' '.join(map(str, results_right))
print(output)    
