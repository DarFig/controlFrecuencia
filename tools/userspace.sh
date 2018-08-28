#!/bin/bash

cpupower frequency-set --governor userspace > /dev/null
echo "userspace" >> ./files/changes_log.txt