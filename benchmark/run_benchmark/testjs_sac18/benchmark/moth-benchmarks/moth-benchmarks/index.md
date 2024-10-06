# Artifact for Transient Typechecks are (Almost) Free

This document gives an overview of the experimental setup to run benchmarks and produce results for our paper.

The full citation of the paper is:

> Roberts, R., Marr, S., Homer, M. & Noble, J. (2019).
> Transient Typechecks are (Almost) Free.
> 33rd European Conference on Object-Oriented Programming, Schloss Dagstuhl-Leibniz-Zentrum fuer Informatik.
> DOI: [10.4230/LIPIcs.ECOOP.2019.15](https://doi.org/10.4230%2fLIPIcs.ECOOP.2019.15)


This overview provides:

- [brief setup instructions](#getting-started-guide) to facilitate re-execution of the benchmarks and replication of the results' figures,
- and then [reiterates our claims](#artifact-and-claims) and summarizes how our artifact can be used to verify them.

Finally, we provide [step-by-step](#step-by-step) instructions that outline how to build our project from source.

Please note that the VirtualBox image is verified to work.
The step-by-step instructions however may be brittle.
Unfortunately, the VirtualBox comes with extra overhead and performance
implications, while it is the easiest way to get started, it may influence
benchmark execution in unexpected ways.

<a name="getting-started-guide"></a>

## 1. Getting Started Guide

The artifact is provided as a [VirtualBox] image that has our experimental setup and its dependencies already installed. For separate source and data downloads, please see [Section 3](#step-by-step).

#### 1.1 Download

You can download the image using one of these mirrors:

- Zenodo: [Mirror 1]
- Kent Data Repository: [Mirror 2]

Please verify that the MD5 check sum matches `955279be02d3d3ff8f01bd01f3790eb2`.

The plots of the evaluation section, and the raw data from our benchmarks can be downloaded, as well:

- [Mirror 1][M1Data]
- [Mirror 2][M2Data]

#### 1.2 VirtualBox Image

The VirtualBox image was tested with version 5.2.
It contains a Lubuntu 16.04 installation.
The image will boot to a login screen,
which needs the following credentials:

- username: `artifact`
- password: `artifact`

#### 1.3 Basic Experiment Execution

<a name="basicrun"></a>

We use [ReBench] to automate the execution of our benchmarks. ReBench uses a configuration file to determine which benchmarks should be run and which parameter to use for the different experiments. The configuration file can be found at `moth-benchmarks/codespeed.conf` in the home directory. The file tells ReBench to run each of our benchmarks against a number of language implementations: Java, Node.js, Moth in various configurations, and Higgs. As each execution completes, ReBench saves the results to the `benchmark.data` file.

For rendering the performance measurements we use R and Latex.
The R scripts are in the `evaluation` folder, which currently also includes the data files from our run.
Thus, without replacing these files or adapting the R script, it will render our results.
In addition to the R files, `eval-description` contains a latex document and `Makefile` to generate all plots and numbers used in our evaluation section.

Note that running all benchmarks as reported in the paper takes about 30 days.
To check that at least some simple benchmarks are working,
let's compare the baseline performance of the Json benchmark.
This takes about half an hour, and executes only one invocation of the benchmark for Higgs, Java, Node.js, and the Moth variants:

```bash
cd /home/artifact/moth-benchmarks
rebench -in 1 -fNB codespeed.conf \
  s:higgs-awfy-steady:Json \
  s:java-awfy-steady:Json  \
  s:node-awfy-steady:Json  \
  s:moth-awfy-steady:Json
```


To perform run all benchmarks the following command can be used:

```bash
## Run All Benchmarks, but only 1 invocation
cd /home/artifact/moth-benchmarks
rebench -in 1 -fNB codespeed.conf all
# this command produced the benchmark.data file
```

To produce the plots based on our data use in the paper, execute:

```bash
## Generate Plots from Data used for the Paper
cd /home/artifact/eval-description
make
# this produced eval-description.pdf
```

To use the results produced by ReBench, the `.Rnw` files in the `evaluation`
folder of the VirtualBox or data download need to be adapted.
See the `eval-description.pdf` for details.
The scripts currently point to the data file with our data, but changing
the file name passed to `load_data_file()` allows the use of
other files produced by ReBench.
As mentioned above, ReBench stores the measurement data
in the `benchmark.data` file.

Please [Section 3](#step-by-step) for more details.

<a name="artifact-and-claims"></a>

## 2. The Artifact and Claims

The artifact provided with our paper is intended to enable others to verify our claims. Our claims are (rephrased from the paper):

1. that our support for type checking does not occur significant overhead
2. that Moth's performance is comparable to that of Node.js, for the given set of benchmark programs, and
3. that the size of our implementation for type checking is as stated by the paper.

To validate claims 1 and 2, one would need to run the full benchmark set (see [Section 1.3](#basicrun)).
However, a full run will take about 30 days.
Furthermore, using a VirtualBox will likely cause additional performance overhead
and a setup on a dedicated benchmark machine directly may be advisable.
For instructions see [Section 3](#step-by-step).

To verify our data without rerunning the experiments,
we provide the necessary R scripts and a Latex document.
Inspecting these scripts would allow to verify the math, and check whether the plots can be reproduced correctly from the given data. For instructions, see [Section 3.4](#plots).

Because of the virtualization or different hardware, the benchmark results may differ to the ones reported. However, relative to each other, we expect the results to show a similar picture.

Claim 3 can be verified by examining the code responsible for executing the type checking. As outlined by the paper, the support for type checking is primarily handled by the self-optimizing `TypeCheckNode` (170 lines). The types themselves are represented by the `SomStructuralType` class (205 lines). These implementation of these can be found at:

- `moth-benchmarks/implementations/Moth/SOMns/src/som/interpreter/nodes/dispatch/TypeCheckNode.java`
- `moth-benchmarks/implementations/Moth/SOMns/src/som/vm/SomStructuralType.java`

Additional minor changes have been made to Moth to enable the above classes to be used during parsing and execution of the Grace program. To inspect of change Moth, we use [Eclipse Oxygen][eclipse_oxy], and its sources contain a Eclipse project file.

<a name="step-by-step"></a>

## 3. Step-by-Step Instructions

This section gives a detailed overview of how to download and build our project from source.

Please note that these instructions might become outdated. The VirtualBox image
is a stable and working snapshot. Though, a setup using the step-by-step
instructions may be preferred to avoid any performance influence of VirtualBox.

### 3.1 Install Dependencies

The core of [Moth] is [a fork of SOMns][somns]. It uses Truffle and Graal, for just in time compilation. We use Oracle Labs' Java 8 SDK that supports Graal.
For convenience, we have our own setup to build it in a compatible version.

Beyond Java, the following software is also required:

For build tools:

- Git
- Ant
- Python 2.7 and pip

For VMs

- `dmd`, provided as part of the D-compiler (Higgs only)
- `xbuild`, provided by mono-devel (Moth only)
- Node.js 8

For benchmark execution:

- ReBench, `pip install ReBench==1.0rc2`

For rendering benchmarks:

- R
- Latex

On a Ubuntu 16.04, the following script will install all dependencies (requires root rights):

```bash
curl -sL https://deb.nodesource.com/setup_8.x | bash -
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys E084DAB9
echo "deb http://cran.rstudio.com/bin/linux/ubuntu xenial/" > /etc/apt/sources.list.d/r-lang.list
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
apt-get install apt-transport-https ca-certificates
echo "deb https://download.mono-project.com/repo/ubuntu stable-xenial main" > /etc/apt/sources.list.d/mono-official-stable.list
wget http://master.dl.sourceforge.net/project/d-apt/files/d-apt.list -O /etc/apt/sources.list.d/d-apt.list

apt-get update --allow-insecure-repositories
apt-get -y --allow-unauthenticated install --reinstall d-apt-keyring
apt-get update
apt-get install -y r-base
apt-get install -y openjdk-8-jdk openjdk-8-source python-pip ant maven nodejs mono-devel dmd-compiler dub
apt-get --no-install-recommends install -y texlive-base texlive-latex-base texlive-fonts-recommended texlive-latex-extra texlive-fonts-extra cm-super

pip install ReBench==1.0rc2
```

For an executable version of the script see [artifact/provision.sh](./artifact/provision.sh).

### 3.2 Source Code

The source code is provided only as a set of git repositories, because Truffle and Graal cannot be easily packaged as a source archive. Their build system needs a git tree as well as online access to download dependencies.

Clone the `papers/ecoop19` tag of our repository:

```bash
git clone --recursive -b papers/ecoop19 https://github.com/gracelang/moth-benchmarks
```

#### 3.2 Build Graal

The only component that needs to be built manually is the Java 8 SDK with support for Graal. Everything else, is automatically build by ReBench.

The following script checks out our Graal setup at the right version, builds it,
and moves the result to the `~/.local/graal-core` folder.
Afterwards, it ensures that the `GRAAL_HOME` environment variable is set.

```bash
mkdir -p ~/.local
git clone https://github.com/smarr/GraalBasic.git
cd GraalBasic
git checkout d37bbe4de590087231cb17fb8e5e08153cd67a59
./build.sh
cd ..
export GRAAL_HOME=~/.local/graal-core
```

The [artifact/build.sh](./artifact/build.sh) script automates this process.

### 3.3 Executing the Benchmarks

<a name="benchmarks"></a>

To execute the benchmarks, we use the [ReBench](https://github.com/smarr/ReBench) benchmarking tool. The experiments and all benchmark parameters are configured in the `codespeed.conf` file (inside the `moth-benchmarks` folder). The file describes which benchmarks to run on which virtual machines. Note that the names used in the configuration file are post-processed for the paper in the R scripts used to generate graphs, thus, the configuration contains all necessary information to find the benchmark implementations in the repositories, but does not match exactly the names in the paper.

Also note that the configuration contains all information to build the experiments.
Most scripts for that can be found in `moth-benchmarks/implementations/build-*`.

To use ReBench, enter the following commands.
This will build everything and execute all benchmarks, which takes about 30 days:

```bash
cd /home/artifact/moth-benchmarks      # folder with the repository
rebench -fN codespeed.conf
```

As ReBench executes, it saves performance results into `benchmark.data`. If ReBench is terminated and restarted, it will continue from the point where it was terminated.

ReBench offers a wide variety of features to control what is executed.
Please see its documentation for an overview: https://rebench.readthedocs.io/en/latest/usage/

For example, one can select the execution of a specific experiment:

```bash
## execute only the experiments for assessing the impact on startup
rebench -fN codespeed.conf typing-startup
```

When all experiments are already built, as in the VirtualBox image, they do not need
to be rebuild and ReBench can skip the build with the `-B` switch.

<a name="plots"></a>

### 3.4 Recreating the Plots and Statistic Analysis

Before the results can be rendered, a few R libraries have to be installed. For this step R might require superuser rights. See `/home/artifact/evaluation/scripts/libraries.R` for details.

```bash
cd /home/artifact/evaluation/scripts/
sudo Rscript libraries.R
```

After the libraries have been installed, a latex document detailing the structure of the evaluation can be rendered:

```
cd /home/artifact/eval-description/
make
```

This will generate the `eval-description.pdf`, which is linked on the desktop of the VirtualBox.

## 4. Licensing

The material in this repository is licensed under the terms of the MIT License. Please note, the repository links in form of submodules to other repositories which are licensed under different terms.

[VirtualBox]: https://www.virtualbox.org/
[Mirror 1]: https://zenodo.org/record/3241810/files/ecoop19.ova?download=1
[Mirror 2]: http://data.kent.ac.uk/79/2/ecoop19.ova
[ReBench]: https://github.com/smarr/ReBench
[eclipse_oxy]: https://www.eclipse.org/oxygen/
[Moth]: https://github.com/gracelang/Moth
[SOMns]: https://github.com/smarr/SOMns
[M1Data]: https://zenodo.org/record/3241810/files/eval.tar.bz2?download=1
[M2Data]: http://data.kent.ac.uk/79/1/eval.tar.bz2
