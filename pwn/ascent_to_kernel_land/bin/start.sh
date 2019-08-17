#!/bin/sh

set -ue

cd /home/ctf

./filter_ctrl_a | qemu-system-i386 -nographic -snapshot -drive file=fs.img,index=1,media=disk,format=raw -drive file=xv6.img,index=0,media=disk,format=raw -smp 2 -m 512
