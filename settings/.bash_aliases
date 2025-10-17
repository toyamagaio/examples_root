#!/bin/bash

alias ls='ls -CF --color=auto'
alias ll='ls -lh'
alias la='ls -lha'
alias cp='cp -i'
alias rm='rm -i'
alias mv='mv -i'
alias script='script -a'
alias texrm='/bin/rm -f *.{dvi,toc,aux,log,lof,lot,bbl,blg}'
alias org='/bin/mv -f "$@"{,.org}'
alias bak='/bin/mv -f "$@"{,.org}; /bin/cp "$@"{.org,}'
alias more='less'
alias title='echo -ne "\033]0;$@\007"'
alias rs='eval $(resize)'
alias kterm='kterm -sb -fg black -bg white'
alias xterm='xterm -sb -fg black -bg white +bdc'
alias help='less $HOME/.myhelp/$1.help'
alias paw='pawX11'
alias less='less -M'
alias duskin='rm *~ .*~ #* .#* core'
alias ps2pdf='ps2pdf -sPAPERSIZE=a4'
alias em='emacs -nw'
alias vi='vim'
alias sorbash='source ~/.bashrc'
alias a2ps='/usr/bin/a2ps -X jp --prologue=color'
alias clean='rm -f *~'
alias root='root -l'

# SSH aliases
alias lam='ssh -X lambda'
alias farm='ssh -X farm'
alias kinoko='ssh -Y unidaq@172.25.26.173'
for i in {1..30}; do
    alias f$i="ssh -X farm$i"
done
