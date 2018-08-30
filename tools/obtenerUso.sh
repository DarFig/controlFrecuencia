#!/bin/bash

#nuc=$(nproc)

#ps aux |awk  '{print $3}' | tail -n+2 | paste -sd+ | bc | awk -v i=$nuc '{ printf "%.1f\n", $1/i }' >> ./files/log.txt
top -b -n2 | grep "Cpu(s)" | awk '{printf "%0.0f\n", $2+$4}'| tail -n1 >> ./files/log.txt