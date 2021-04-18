# Inserting a Linux Kernel Module
This Linux Kernel Module (LKM) is designed for use in Ubuntu 16.04LTS. It has not been tested on any other versions or operating systems. 

If you do not know what you are doing -- I advise in depth research of the kernel and what exactly is going on before proceeding. Incorrect use of the kernel and kernel modules can result in bricking your operating system. Proceed with caution.

## Files in project
| Name | Purpose |
| --- | ----|
| lkm_insert.c | Primary source file being injected into the kernel |
| Makefile | Self explanatory |

## Inserting the LKM

To start off I recommend opening and monitoring your kernel log to ensure everything is going as it should. 

```cpp
tail -f /var/log/kern.log
```

Now we can compile our module. 

```cpp
make
```

You should now see several more files in your directory. The important one is `lkm_insert.ko`. This is a kernel object file. Now to inject the module into the kernel we will be using insmod.

```cpp
sudo insmod lkm_insert.ko
```

You should now see the module is inserted (via the kernel logs you have up). The number after the kernel module being loaded is the major. You will need this.

```cpp
cd /dev
sudo mknod totallyARealDevice c *major_number_here* 0
cat /dev/totallyARealDevice
```


To remove the module use rmmod.

```cpp
sudo rmmod lkm_insert
```