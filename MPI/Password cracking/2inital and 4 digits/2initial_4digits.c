#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>


/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 4 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    mpicc -o 2initial_4digits 2initial_4digits.c -lcrypt

  Run with:

    mpirun -n 3 ./2initial_4digits > 2initial_4digitsresults.txt

******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] =  {

"$6$KB$4YKQJLNLT4r280KA3GrPxIaJBj2nFbdnYlaEK.F8kv/WmyM4ISpsEBQJb6neCVx9dYGGygos1RFUTkgCRUvhJ1", 
"$6$KB$WFXsjERK61h4.DnDCinwJxpWy.r6uVuMiTveCfRPvNXpG60KNYKO2ETSI1WhZxn07biY91T/L/ey8y2nOZ/4f.",
"$6$KB$d3bWDsteyKYt9I46LYe5fmEzDi6p7d3z4C4UDpZS06rBm5V1V65qJP2i97avkUPs6xOjiUGuY5.qdYAiiwjHd0",
"$6$KB$uH1/n54WoNfQOZuqlDKRm1NTWUEAEjQLwPcFjspj6UhxLaj5RWsu2p5C.eHfbf8UGoTg6PHJPb.PHJXhJVzov/"

};


/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/



void kernel_function_1(char *salt_and_encrypted){
  int x, y, z, k;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
       for(k=0; k<=99; k++){
        sprintf(plain, "%c%c%02d%02d", x, y, z, k); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
       }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

// Calculate the difference between two times. Returns zero on
// success and the time difference through an argument. It will 
// be unsuccessful if the start time is after the end time.

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

void kernel_function_2(char *salt_and_encrypted){
  int p, q, r, u;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(p='N'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        for(u=0; u<=99; u++){
        sprintf(plain, "%c%c%02d%02d", p, q, r, u); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
       }
      }
    }
  }
  printf("%d solutions explored\n", count);
}




int main(int argc, char *argv[])
 {

 struct timespec start, finish;   
  long long int time_elapsed;
 
  clock_gettime(CLOCK_MONOTONIC, &start);

  int size, rank;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3) {
    if(rank == 0) {
      printf("This program needs to run on exactly 3 processes\n");
    }
  } 
  else {
    if(rank == 0){
      int h;
      int x;
      int y;
     
       MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);  
       MPI_Send(&y, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
	
    } else {
      if(rank == 1){
	int h;
        int Num = rank + 10;
      	MPI_Recv(&Num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for ( h = 0; h<n_passwords; h++){
		kernel_function_1(encrypted_passwords[h]);
	}
      }
	else if(rank == 2){
	int h;
      	int Num = rank + 10;
      	MPI_Recv(&Num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for (h = 0; h<n_passwords; h++){
		kernel_function_2(encrypted_passwords[h]);
	}
      }
    }
  }
  MPI_Finalize(); 

  clock_gettime(CLOCK_MONOTONIC, &finish);
   time_difference(&start, &finish, &time_elapsed);
   printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 

  return 0;
  }





 
  

  


