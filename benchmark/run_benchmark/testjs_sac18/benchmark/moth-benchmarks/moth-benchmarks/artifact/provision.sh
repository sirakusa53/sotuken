#!/bin/bash -eux

# For Xenial we need the following. TODO: remove once we switched to bionic
wget -O- https://deb.nodesource.com/setup_8.x | bash -

# For Xenial we need:
#  - install R package server
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E084DAB9
echo "deb https://cran.rstudio.com/bin/linux/ubuntu xenial/" > /etc/apt/sources.list.d/r-lang.list

#  - install mono package server
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
apt-get install -y apt-transport-https ca-certificates
echo "deb https://download.mono-project.com/repo/ubuntu stable-xenial main" > /etc/apt/sources.list.d/mono-official-stable.list

#  - install D package server
wget http://master.dl.sourceforge.net/project/d-apt/files/d-apt.list -O /etc/apt/sources.list.d/d-apt.list

apt-get update --allow-insecure-repositories
apt-get -y --allow-unauthenticated install --reinstall d-apt-keyring
apt-get update
apt-get install -y r-base
apt-get install -y --allow-unauthenticated openjdk-8-jdk openjdk-8-source python-pip ant maven nodejs mono-devel dmd-compiler dub

pip install ReBench==1.0rc2

# install Latex
apt-get --no-install-recommends install -y texlive-base texlive-latex-base texlive-fonts-recommended  texlive-latex-extra texlive-fonts-extra cm-super

# enable nice without sudo
echo "artifact       -     nice       -20" >> /etc/security/limits.conf

su artifact <<SHELL
# Create .Rprofile for installing libraries
echo "options(repos=structure(c(CRAN=\"https://cloud.r-project.org/\")))" > .Rprofile
SHELL

# install R dependencies
pushd evaluation/scripts
Rscript libraries.R
popd
