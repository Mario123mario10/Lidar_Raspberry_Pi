#!/bin/sh
qemu-system-aarch64 -m 1024 -smp 2 -cpu cortex-a57 -M virt -nographic \
    -kernel openwrt-19.07.3-armvirt-64-Image -append "root=fe00" \
    -nic user,hostfwd=tcp::8888-:80 \
    -drive if=none,file=openwrt-19.07.3-armvirt-64-root.ext4,id=hd0 -device virtio-blk-device,drive=hd0
