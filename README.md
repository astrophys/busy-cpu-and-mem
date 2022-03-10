# Segfault and CPU tools
#### Author : Ali Snedden
#### License: MIT
## Purpose:
This repo contains a code busy-cpu-and-mem.c which takes two arguments, one
for cpu and the other for memory. It can be used in conjunction with 
ulimit's data to generate segfaults (see `/etc/security/limits.conf`)


## Installation and Dependencies :
1. A modern C compiler with OpenMP extensions
2. Get a copy of this code.
3. Compile 
```
gcc -fopenmp -Wall busy-cpu-and-mem.c
```


## Usage:
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
