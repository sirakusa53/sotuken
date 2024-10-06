# Script utility for "Are We Fast Yet" benchmarks
#   Originally developed by Stefan Marr
#   https://gitlab.soft.vub.ac.be/stefan.marr/awfy-runs
#
# Adapted by Richard Roberts
#

# set up color commands
if [ -t 1 -a -t 2 -a \( `type -t tput` = "file" \) ]; then
  _colors=`tput colors`
  if [ "$_colors" -ge 256 ]; then
    INFO () { tput setaf 33;  /bin/echo "$@"; tput sgr0; }
    OK   () { tput setaf 28;  /bin/echo "$@"; tput sgr0; }
    WARN () { tput setaf 226; /bin/echo "$@"; tput sgr0; }
    ERR  () { tput setaf 196; /bin/echo "$@"; tput sgr0; }
  else
    INFO () { tput setaf 4; /bin/echo "$@"; tput sgr0; }
    OK   () { tput setaf 2; /bin/echo "$@"; tput sgr0; }
    WARN () { tput setaf 3; /bin/echo "$@"; tput sgr0; }
    ERR  () { tput setaf 1; /bin/echo "$@"; tput sgr0; }
  fi
else
  INFO () { /bin/echo "$@"; }
  OK   () { /bin/echo "$@"; }
  WARN () { /bin/echo "$@"; }
  ERR  () { /bin/echo "$@"; }
fi

function load_submodule() {
  INFO Load "$1"
  git submodule update --init --recursive $1
}

function check_for() {
  if [ ! -x `which $1` ]
  then
    ERR "$1 binary not found. $2"
    if [ "non-fatal" -ne "$3" ]
    then
      exit 1
    fi
  fi
}
