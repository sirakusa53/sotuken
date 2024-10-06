#!/bin/bash -eux

echo ""
echo "Customize Image"
echo ""

## Set Wallpaper
mkdir -p ~/Downloads
cd ~/Downloads
wget https://stefan-marr.de/ci/artifacts/ecoop19-lubuntu-wall.png
pcmanfm --set-wallpaper=/home/artifact/Downloads/ecoop19-lubuntu-wall.png || echo "Setting Wallpaper Failed"

cd ~/
## Create Links on Desktop
mkdir -p ~/Desktop
ln -s ~/evaluation ~/Desktop/evaluation
ln -s ~/eval-description ~/Desktop/eval-description
ln -s ~/eval-description/eval-description.pdf ~/Desktop/eval-description.pdf

ln -s ~/${REPO_NAME} ~/Desktop/${REPO_NAME}
ln -s ~/${REPO_NAME}/index.md ~/Desktop/README.md

echo ""
echo "Customization Done"
echo ""
