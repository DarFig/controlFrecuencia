#!/bin/bash

#top -b -n2 | grep "Cpu(s)" | awk '{print $2+$4}'| tail -n1 >> ./files/log.txt

top -b -n2 -p 1 | fgrep "Cpu(s)" | tail -1 | awk -F'id,' -v prefix="$prefix" '{ split($1, vs, ","); v=vs[length(vs)]; sub("%", "", v); printf "%s%.1f%%\n", prefix, 100 - v }'  >> ./files/log.txt