#!/bin/bash

for i in {8..63}; do
    echo 1 > /sys/devices/system/cpu/cpu"$i"/online >> ./files/changes_log.txt
done