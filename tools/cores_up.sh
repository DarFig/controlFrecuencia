#!/bin/bash

for i in {8..63}; do
    echo 1 > /sys/devices/system/cpu/cpu"$i"/online
done

echo "cores up" >> ./files/changes_log.txt