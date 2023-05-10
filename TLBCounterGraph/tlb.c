#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>


//Raising errors
void raise_error(char *error_msg){
	fprintf(stderr, "%s\n", error_msg);
	exit(EXIT_FAILURE);
}


//Debug mode if mode is 1
void debug(int mode, char *debug_msg){
	if (mode == 1){
		printf("DEBUG: %s\n", debug_msg);
	}
	return;
}



int main(int argc, char *argv[]) {
	int DEBUG_MODE = 0;
  
	//Checking if arguments are entered
	if (argc < 3) {
    	raise_error("Arguments not specified");
	}

	long PAGESIZE = sysconf(_SC_PAGESIZE);
	long jump = PAGESIZE / sizeof(int);

  	//Get values from arguments
	int pages = atoi(argv[1]);
	int trials = atoi(argv[2]);

	//VAlidation values
	if (pages <= 0 || trials <= 0) {
  		raise_error("Invalid input");
	}

  
  
	//Allocate memory
	int *a = calloc(pages, PAGESIZE);
	if( a == NULL ){
		raise_error("Cant allocate memory");
	}
	
	
	//Start timer
 	struct timespec start, end;
 	
 	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1) {
  		raise_error("Error initializating clock_gettime");
 	}


	//Array traversal	
	for (int j = 0; j < trials; j++) {
    	for (int i = 0; i < pages * jump; i += jump) {
      		a[i] += 1;
    	}
  	}


  	//Stop timer
  	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1) {
  		raise_error("Error initializating clock_gettime");
  	}
  	
  	printf("%f\n",
         ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec) /
             (trials * pages));
  	free(a);

  return 0;



}