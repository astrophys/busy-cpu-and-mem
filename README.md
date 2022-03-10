# Keep CPU Busy
#### Author : Ali Snedden
#### License: MIT
## Purpose:
This repo does absolutely no work. It just allocates the specified amount of memory
and processors and then works them to keep them busy. 

This repo contains a code busy-cpu-and-mem.c which when compiled, takes two
arguments, one for cpu and the other for memory.

## Usage :
Uses for this code:

### Testing and Creating Segfaults with ulimit
This code can be used in conjunction with ulimit's data to generate segfaults
(see `/etc/security/limits.conf`). In Red Hat 8, it isn't always obvious how to 
generate segfaults and capture the output

1. Enable core files on Red Hat 8 : 
    a) Ensure that `ulimit -c unlimited`

2. Ensure both abrtd and abrt-ccpp are running
    a) `service abrtd status`
    b) `service abrt-ccpp status`

3. In `/etc/abrt/abrt-action-save-package-data.conf` ensure `ProcessUnpackaged = yes`

4. Run a test bad code
    a) Typically the file will be written `/var/spool/abrt/`
    b) If you do `cat /proc/sys/kernel/core_pattern`, you'll see some stuff
    c) If you `echo "core" > /proc/sys/kernel/core_pattern` it will dump
       to a local file

### Testing Cgroups
2. When testing cgroups, it is convenient to have a single code to keep the processor
   busy instead of spawning dozens of cpu processes to test the cpu limits


## Installation and Dependencies :
1. A modern C compiler with OpenMP extensions
2. Get a copy of this code.
3. Compile 
```
gcc -fopenmp -Wall busy-cpu-and-mem.c
```


## Running :
```
./a.out num_cpu mem_use_in_GB
```
Where first argument is the number of cpu and second argument is the gigabytes of RAM 
for the code to use.

E.g. 
```
./a.out 16 50
```



#### References:
1.

#### Other Useful Links :
