# Keep CPU Busy
#### Author : Ali Snedden
#### License: MIT
## Purpose:
This repo does absolutely no work. It just allocates the specified amount of memory
and processors and then works them to keep them busy. 

This repo contains a code busy-cpu-and-mem.c which when compiled, takes two
arguments, one for cpu and the other for memory.



## Installation and Dependencies :
1. A modern C compiler with OpenMP extensions
2. Get a copy of this code.
3. Compile 
```
gcc -fopenmp -Wall busy-cpu-and-mem.c
```


## Running :
```
./a.out num_cpu mem_use_in_GB num_of_iterations
```
Where first argument is the number of cpu, second argument is the gigabytes of RAM 
for the code to use and the third argument is the number of iterations to use (i.e. a proxy for total run time).

E.g. 16 cores, 50GB, 142 iterations
```
./a.out 16 50 142
```



## Uses for this Code:

### Testing and Creating Segfaults with ulimit
This code can be used in conjunction with ulimit's data to generate segfaults
(see `/etc/security/limits.conf`). In Red Hat 8, it isn't always obvious how to 
generate segfaults and capture the output

1. Enable core files on Red Hat 8, allow them to be unlimited in size.
   Check that `ulmit -c` is `unlimited`: 
    ```
    $ ulimit -c
    unlimited
    ```

2. Ensure both abrtd and abrt-ccpp are running
    ```
    $ service abrtd status          # Should be in 'active' and running
    $ service abrt-ccpp status      # Should be in 'active' 
    ```

3. In `/etc/abrt/abrt-action-save-package-data.conf` ensure `ProcessUnpackaged = yes`
    ```
    $ grep ProcessUnpackaged /etc/abrt/abrt-action-save-package-data.conf
    ProcessUnpackaged = yes
    ```

4. Run a test bad code

    a) Typically the file will be written `/var/spool/abrt/`

    b) If you do `cat /proc/sys/kernel/core_pattern`, you'll see some stuff

    c) If you `echo "core" > /proc/sys/kernel/core_pattern` it will dump
       to a local file

5. Compile and Run the code (e.g. with 8 cores and 20GB RAM)
    ```
    gcc -fopenmp -Wall busy-cpu-and-mem.c
    ./a.out 8 20 142
    ```

### Testing Cgroups
When testing cgroups, it is convenient to have a single code to keep the processor
busy instead of spawning dozens of cpu processes to test the cpu limits

1. Create a directory for all users (careful this will limit root) :
```
$ mkdir /etc/systemd/system/user-.slice.d
```

2. Create the following file (permits only 80% cpu and 8GB of RAM):
```
$ cat /etc/systemd/system/user-.slice.d/cpu.conf
[Slice]
CPUQuota=80%
$ cat /etc/systemd/system/user-.slice.d/memory.conf
[Slice]
MemoryMax=8G
```

3. Implement the limits
```
$ systemctl daemon-reload
```

4. Compile and Run the code (e.g. with 8 cores and 20GB RAM)
    ```
    gcc -fopenmp -Wall busy-cpu-and-mem.c
    ./a.out 8 20 142
    ```




## References:
1. [Naming Convention for Core Files](https://unix.stackexchange.com/a/277338/128519)
2. [Specifying location of core file](https://stackoverflow.com/a/42272400/4021436)
3. [How to enable core file dumps when an application crashes or segmentation faults](https://access.redhat.com/solutions/4896)
4. [How to collect core dump file of a crashing program that is shipped in Red Hat Enterprise Linux 6/7/8?](https://access.redhat.com/solutions/56021)
5. [Setting Limits for Applications (i.e. Cgroups)](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/managing_monitoring_and_updating_the_kernel/setting-limits-for-applications_managing-monitoring-and-updating-the-kernel)
6. [A Linux sysadmin's introduction to cgroups](https://www.redhat.com/sysadmin/cgroups-part-one)
7. [Possible Options with Cgroups](https://www.freedesktop.org/software/systemd/man/systemd.resource-control.html)

#### Other Useful Links :
