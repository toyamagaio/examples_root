# ~/.bashrc

# History settings
HISTSIZE=15000
HISTFILESIZE=5000

# ROOT setup
# export ROOTSYS=/usr/local/cern/root6.20.04_py3
export ROOTSYS=/usr/local/cern/root6.32.00
export ROOTDIR=$ROOTSYS
export PATH=$PATH:$ROOTSYS/bin
export LD_LIBRARY_PATH=$ROOTSYS/lib:$ROOTSYS/lib/root
#/usr/local/cern/geant4.9.6.p04/lib64
#export HEATESOUTPUTDIR=/data/sdd/TES_analysis/output/
# export PYTHONPATH=${ROOTSYS}/lib:

# Key bindings (bash equivalent)
bind '"\e[A": history-search-backward'
bind '"\e[B": history-search-forward'

export SVN_EDITOR=vim

# Load aliases
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# Conda environment
#if [ -f ~/software/anaconda3/etc/profile.d/conda.sh ]; then
#    . ~/software/anaconda3/etc/profile.d/conda.sh
#fi

# Load profile
if [ -f ~/.profile ]; then
    . ~/.profile
fi
