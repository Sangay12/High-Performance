#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <crypt.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>



/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    cc -o Multi-thread Multi-thread.c -lcrypt -pthread

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./Multi-thread > Multi-thread.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$.bVspZYQofaBc4KhsjlqZSxu4R7r7mH7.Q/uCYlJ.3nRV2x5Jz.TKYX6Aa97sUZhTjmN3rett7GrCFr3aO3uR/",
  "$6$KB$wO5OXgJxqVzltwW29G/XJuG5ZszGOhwhvpEBnFM/ThGmTNiNhnUTBS8lnNWs6SwP6XpUwzKXVTv90S2XEWwy./",
  "$6$KB$JXfY4sYXD0vnuRY3KIvezu913aIc1TJ0CE0oVTWDrsRSXk4/k.RnljKOR3/Vw7wxAOnEsxllD01WU/MJP4IIj1"
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

void cracks(){
 int s;
 pthread_t thread_1, thread_2;
 
 void *kernel_function_1();
 void *kernel_function_2();
 
 for(s=0; s<n_passwords; s++)
 { 
  pthread_create(&thread_1, NULL, kernel_function_1, encrypted_passwords[s]);
  pthread_create(&thread_2, NULL, kernel_function_2, encrypted_passwords[s]);

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
 }
}


void *kernel_function_1(char *salt_and_encrypted){
  int j, k, l;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(j='A'; j<='M'; j++){
    for(k='A'; k<='Z'; k++){
      for(l=0; l<=99; l++){
        sprintf(plain, "%c%c%02d", j, k, l); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
      // else {
         // printf(" %-8d%s %s\n", count, plain, enc);
        //}
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
    // else {
          //printf(" %-8d%s %s\n", count, plain, enc);
       // }
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

int main(int argc, char *argv[])
 {

 struct timespec start, finish;   
  long long int time_elapsed;
 
  clock_gettime(CLOCK_MONOTONIC, &start);

   cracks();

  clock_gettime(CLOCK_MONOTONIC, &finish);
   time_difference(&start, &finish, &time_elapsed);
   printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 

  return 0;
  }




 
  

  


