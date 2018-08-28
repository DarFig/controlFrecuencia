#!/bin/bash

cpupower frequency-set --governor powersave > /dev/null
echo "powersave" >> ./files/changes_log.txt