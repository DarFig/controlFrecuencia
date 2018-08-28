#!/bin/bash

for i in {8..63}; do
    echo 0 > /sys/devices/system/cpu/cpu"$i"/online
done

echo "cores down" >> ./files/changes_log.txt