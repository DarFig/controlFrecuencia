#!/bin/bash

cpupower frequency-set --governor ondemand > /dev/null
echo "ondemand" >> ./files/changes_log.txt