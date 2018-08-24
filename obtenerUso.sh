#!/bin/bash

top -b -n2 | grep "Cpu(s)" | awk '{print $2+$4}'| tail -n1 >> log.txt