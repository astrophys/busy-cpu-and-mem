/*
Author  : Ali Snedden
Date    : 1/24/22
Purpose : 
    1. Create a segmentation fault to test 
        a) enabling segfaults on a Redhat machine
        #) to test `ulimit data`

    #. Enabling core files : 
        a) Tasks
            #. Ensure that `ulimit -c unlimited`
            #. Ensure both abrtd and abrt-ccpp are running
                * service abrtd status
                * service abrt-ccpp status
            #. In /etc/abrt/abrt-action-save-package-data.conf ensure
                `ProcessUnpackaged = yes`
            #. Run a test bad code
                * Typically the file will be written /var/spool/abrt/
                * If you do `cat /proc/sys/kernel/core_pattern`, you'll see some stuff
                * If you `echo "core" > /proc/sys/kernel/core_pattern` it will dump
                  to a local file
        #) Refs :
            #. https://unix.stackexchange.com/a/277338/128519
            #. https://stackoverflow.com/a/42272400/4021436
            #. https://access.redhat.com/solutions/4896
            #. https://access.redhat.com/solutions/56021
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int len = 1500000000;
    int N = 1000;           // Number of loops
    int i = 0;
    int j = 0;

    long * array = (long *)malloc(sizeof(long) * len);
    printf("%l", array[len+len]);       // segfault here

    for(i=0; i<N; i++){
        if(i%10 == 0){
            printf("\ti=%i\n",i);
        }
        fflush(stdout);
        for(j=0; j<len; j++){
            array[j] = 42;
        }
    }

    return 0;
}
