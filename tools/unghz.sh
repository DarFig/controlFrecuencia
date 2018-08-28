#!/bin/bash

cpupower frequency-set --freq 1000000 > /dev/null
echo "1.0GHz" >> ./files/changes_log.txt