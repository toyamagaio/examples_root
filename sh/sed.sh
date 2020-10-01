#!/bin/bash

base_arg="ThisIsASample"
echo $base_arg

##simpel replace ment
past_arg=`echo $base_arg | sed s/Is/Was/`
echo $past_arg

##append
appended_arg=`echo $base_arg | sed s/$/WhichShowsHowToUseSedCommandInBashScript/`
echo $appended_arg
appended_arg=`echo $base_arg | sed s/^/DoYouThink/ | sed s/$/?/`
echo $appended_arg
