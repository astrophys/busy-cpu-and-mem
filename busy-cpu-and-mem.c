/*
AUTHOR  : Ali Snedden
DATE    : 1/24/22
PURPOSE : 
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
RUN:
    ./a.out nthreads mem_in_GB
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <omp.h>



/*
    ARGS :
        string = char[], string to print
    DESCRIPTION :
        This prints and error and then exits with a non-zero error code
    RETURN :     
        1 =  int, b/c it is an error
    DEBUG : 
    FUTURE :
*/
int exit_with_error(char * string){
    fprintf(stderr, "%s",string);
    return 1;
}




/*
    ARGS :
        argc   = int, number of CL args
        argv[] = char[], CL args
    DESCRIPTION :
        This prints and error and then exits with a non-zero error code
    RETURN :
        0 =  int, b/c it completed w/o error
    DEBUG : 
    FUTURE :
        1. Come up with method to check the number of elements in argv
*/
int main(int argc, char *argv[])
{
    char errMsg[200];       // Used for error messages
    long nThread;            // Number of threads, from CL args
    long nLoop = 1000;       // Number of loops
    long i = 0;
    long j = 0;
    long k = 0;
    long mem = 0;           // Memory in GB
    long n;                 // Number of array elements, from CL args
    long nbytes;            // Total bytes
    long * array = NULL;    // Array to do operations

    /************* Parse CL args *************/
    // Check for correct number of arguments
    if(argc != 3){
        sprintf(errMsg, "ERROR!!! %i args passed, only 3 expected\n", argc);
        exit_with_error(errMsg);
    }
    // Number of threads
    nThread = atoi(argv[1]);
    // Memory
    mem = atol(argv[2]);
    printf("Running with %ld procs and %ld GB\n", nThread, mem);
    printf("pid = %ld; parentid = %ld\n", (long)getpid(), (long)getppid());
    // OpenMP creates nThread copies of array, so account
    nbytes = mem * pow(10,9); 
    n = nbytes / (nThread * sizeof(long));
    // https://stackoverflow.com/a/12285433/4021436
    omp_set_num_threads(nThread);

    #pragma omp parallel private(i, array)
    {
        long tid = omp_get_thread_num();
        printf("Hello from Thread : %ld\n",tid);
        // Initialize - stop compiler complaints
        array = (long *)malloc(n * sizeof(long)); 

        // This loop doesn't do any real work other
        #pragma omp for
        for(k=0; k<nThread; k++){
            for(i=0; i<nLoop; i++){
                if(tid == 0 && i%10 == 0){
                    printf("\ttid: %ld; i=%ld\n",tid,i);
                }
                fflush(stdout);
                for(j=0; j<n; j++){
                    array[j] = tid;
                }
            }
        }
    
    
    }

    return 0;
}
