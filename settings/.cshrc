setenv ANALYZER ~/analyzer-1.6
setenv ROOTSYS /usr/local/hep/root_v6.14.00
#setenv ROOTSYS /usr/local/hep/root_v5.34.36
setenv CERN /cern
setenv CERN_LEVEL 2006
#setenv PATH ${PATH}:/bin:/usr/local/cmake-2.8.10.2/bin
setenv PATH ${PATH}:${ROOTSYS}/bin:$CERN/$CERN_LEVEL/bin:/usr/local/bin:/usr/bin
setenv LD_LIBRARY_PATH /usr/local/lib:/usr/lib
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${ROOTSYS}/lib:${ROOTSYS}/lib/root:${ANALYZER}/

#setenv PATH ${PATH}:/usr/local/cmake-3.12.0/bin
#setenv CC /usr/local/gcc-8.1.0/bin/gcc
#setenv CXX /usr/local/gcc-8.1.0/bin/g++
#setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/usr/local/gcc-8.1.0/lib64
#alias cmake '/usr/local/cmake-3.12.0/bin/cmake'
#alias gcc '/usr/local/gcc-8.1.0/bin/gcc'
#alias g++ '/usr/local/gcc-8.1.0/bin/g++'


set autolist = ambiguous
set color
set complete = enhance 
set history = 5000 
set savehist = (5000 merge)

bindkey -k up history-search-backward
bindkey -k down history-search-forward

alias ls 'ls -CF --color=auto \!*'
alias ll 'ls -l \!*'
alias la 'ls -la \!*'
alias cp 'cp -i \!*'
alias rm 'rm -i \!*'
alias mv 'mv -i \!*'
alias script 'script -a \!*'
alias texrm '/bin/rm -f \!*.{dvi,toc,aux,log,lof,lot,bbl,blg}'
alias org '/bin/mv -f \!*{,.org}'
alias bak '/bin/mv -f \!*{,.org};/bin/cp \!*{.org,}'
alias more less
alias title 'echo -n  "^[]0;\!*^G"'
alias rs 'eval `resize`'
alias kterm 'kterm -sb -fg black -bg white '
alias xterm 'xterm -sb -fg black -bg white +bdc'
alias help 'less $HOME/.myhelp/\!*.help'
alias paw 'pawX11'
alias less 'less -M'
alias duskin 'rm *~ .*~ #* .#* core'
#alias emacs 'emacs -fn rk14'
alias em 'emacs -nw'
alias vi 'vim'
alias sorcsh "source ~/.cshrc"
alias a2ps '/usr/bin/a2ps -X jp --prologue=color'
#alias clean 'rm -f *~'
alias clean '~/aa.sh'
alias root 'root -l '
alias jlab 'ssh -X toyama@login.jlab.org'
alias mainz 'ssh -X mainz'
alias h2r '/cern/root_v5.24.00.i386_fc8_gcc4.1.2/bin/h2root'
alias lam 'ssh -Y -X toyama@lambda.phys.tohoku.ac.jp'
alias farm 'ssh -Y -X toyama@farmio'
alias kinoko 'ssh -Y -X unidaq@172.25.27.224'
alias gamma 'ssh -Y -X toyama@gamma.lns.tohoku.ac.jp'

setenv MANPATH /usr/local/man:/usr/local/gnu/man:/usr/man:/usr/local/X11R6/man:/opt/fortran/share/man:/opt/ansic/share/man


#setenv VERBOSE 1

##setenv CVSROOT :ext:toyama@cvs.jlab.org:/group/hks/e01011soft
##setenv CVS_RSH /usr/bin/ssh
setenv CVSROOT :ext:toyama@farmio:/home/cvs
#setenv CVSROOT /home/cvs
setenv CVSEDITOR vim
setenv PAGER less
setenv CVS_RSH ssh

setenv PGPLOT_DIR /home/toyama/cosy/pgplot
setenv PGPLOT_DEV /xserv
setenv PGPLOT_FORGROUND white
setenv PGPLOT_BACKGROUND black

setenv SVN_EDITOR vim

#source geant4 definitions
if (-e ~/.g4rc ) then
        source ~/.g4rc
endif

#source condor definitions
if (-e /usr/local/condor/condor.csh ) then
        source /usr/local/condor/condor.csh
endif


### KiNOKO ###
setenv KINOKO_ROOT /usr/local/hep/kinoko
setenv KINOKO_XTERM /usr/bin/xterm
setenv KINOKO_RSH /usr/bin/ssh
setenv KINOKO_CONTROL_PORT_BASE 40000
setenv KINOKO_DATASTREAM_PORT_BASE 42000
setenv KINOKO_SHELL_PORT_BASE 45000
setenv KCOM_PATH ".:${KINOKO_ROOT}/bin"
setenv KORB_PROJECT_PATH ${KINOKO_ROOT}
setenv PATH "${PATH}:${KINOKO_ROOT}/bin"
#setenv KINOKO_WEB_ROOT=${HOME}/public_html/webkinoko

