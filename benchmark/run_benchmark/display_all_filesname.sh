#!/bin/bash

# 引数の確認
if [ $# -ne 1 ]; then
  echo "Usage: $0 /path/to/directory"
  exit 1
fi

# ディレクトリの存在確認
directory="$1"
if [ ! -d "$directory" ]; then
  echo "Error: Directory not found."
  exit 1
fi

# ディレクトリ内のファイルを再帰的に処理
ls "$directory" | while read -r file; do
  # ファイル名から拡張子を取り除いて表示
  filename=$(basename "$file")
  filename_no_ext="${filename%.*}"
  echo -n "$filename_no_ext "
done
