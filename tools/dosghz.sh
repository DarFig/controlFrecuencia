#!/bin/bash

cpupower frequency-set --freq 2000000 > /dev/null
echo "2.0GHz" >> ./files/changes_log.txt