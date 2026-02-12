
make
sudo insmod fwnf_kernel.ko
dmesg | tail
sudo mknod /dev/myfw c <major> 0
sudo chmod 666 /dev/myfw
gcc fwctl.c -o fwctl
sudo ./fwctl


Exit your CLI first
If your firewall CLI is running:
exit

Make sure no program is using /dev/myfw.
You can verify:
lsof /dev/myfw


If nothing prints → safe to remove.
Remove the module
sudo rmmod fwnf_kernel
OR
sudo rmmod fwnf_kernel.ko

Verify it is removed
lsmod | grep fwnf_kernel
If nothing appears → module successfully removed

Check kernel logs
dmesg | tail

You should see:
Firewall unloaded

Remove device file (optional cleanup)
sudo rm /dev/myfw

If You Get Error: “Module is in use”

That means:
CLI still running
Some process still holding /dev/myfw
Or hook not unregistered properly

Fix:
sudo fuser -v /dev/myfw
Kill the process if needed.

Complete Remove Sequence (Clean Way)
exit                     # exit CLI
sudo rmmod fwnf_kernel
sudo rm /dev/myfw
make clean


