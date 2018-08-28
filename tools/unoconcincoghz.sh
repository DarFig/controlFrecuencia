#!/bin/bash

cpupower frequency-set --freq 1500000 > /dev/null
echo "1.5GHz" >> ./files/changes_log.txt