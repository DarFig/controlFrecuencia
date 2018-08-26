# controlFrecuencia


### Governors Problems

**not on servers**

If your system is using the new driver called intel_pstate. There are only two governors available when using this driver: powersave and performance.

- disable the current driver: add intel_pstate=disable to your kernel boot line. Editing /etc/default/grub and adding:

GRUB_CMDLINE_LINUX_DEFAULT="intel_pstate=disable"
And then updating grub.cfg ala grub-mkconfig -o /boot/grub/grub.cfg 

- load the userspace module: modprobe cpufreq_userspace
- load the ondemand module: modprobe cpufreq_ondemand