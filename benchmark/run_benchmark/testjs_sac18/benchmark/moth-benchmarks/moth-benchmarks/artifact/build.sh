#!/bin/bash -eux
echo ""
echo "Build GraalBasic, a Graal-enabled JDK"
echo ""

mkdir -p ~/.local
git clone https://github.com/smarr/GraalBasic.git
cd GraalBasic
git checkout d37bbe4de590087231cb17fb8e5e08153cd67a59

./build.sh

## Clean Graal Build Folder, not needed
export JVMCI_VERSION_CHECK=ignore
export JAVA_HOME=~/.local/graal-core
#/usr/lib/jvm/java-8-openjdk-amd64/
(cd graal-jvmci-8;    ../mx/mx clean)
(cd truffle/compiler; ../../mx/mx clean)
(cd truffle/sdk;      ../../mx/mx clean)
unset JAVA_HOME

cd ..
export GRAAL_HOME=~/.local/graal-core
echo "" >> ~/.profile
echo "# Export GRAAL_HOME for Moth" >> ~/.profile
echo "export GRAAL_HOME=~/.local/graal-core" >> ~/.profile


git clone ${GIT_REPO} ${REPO_NAME}

cd ${REPO_NAME}
git checkout ${COMMIT_SHA}
git submodule update --init --recursive
rebench --faulty --setup-only ${REBENCH_CONF} all

cd ~/eval-description
make
