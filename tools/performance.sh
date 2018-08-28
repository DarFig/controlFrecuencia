#!/bin/bash

cpupower frequency-set --governor performance > /dev/null
echo "performance" >> ./files/changes_log.txt