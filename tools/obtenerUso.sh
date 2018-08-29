#!/bin/bash

nuc=$(nproc)

ps aux |awk  '{print $3}' | tail -n+2 | paste -sd+ | bc | awk -v i=$nuc '{ print $1/i }' >> ./files/log.txt
