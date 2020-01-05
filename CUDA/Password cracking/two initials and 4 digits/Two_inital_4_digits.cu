#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************
 Compile and run with:
    nvcc -o Two_inital_4_digits Two_inital_4_digits.cu
   
    To run
    ./Two_inital_4_digits

  Dr Kevan Buckley, University of Wolverhampton, 2018
*****************************************************************************/

__device__ int is_a_match(char *attempt) {
  char plain_password1[] = "DP2323";
  char plain_password2[] = "BV1212";
  char plain_password3[] = "WE1723";
  char plain_password4[] = "PO0912";

  char *e = attempt;
  char *f = attempt;
  char *g = attempt;
  char *h = attempt;
  char *p1 = plain_password1;
  char *p2 = plain_password2;
  char *p3 = plain_password3;
  char *p4 = plain_password4;

  while(*e == *p1) { 
   if(*e == '\0') 
    {
	printf("Found password: %s\n",plain_password1);
      break;
    }

    e++;
    p1++;
  }
	
  while(*f == *p2) { 
   if(*f == '\0') 
    {
	printf("Found password: %s\n",plain_password2);
      break;
    }

    f++;
    p2++;
  }

  while(*g == *p3) { 
   if(*g == '\0') 
    {
	printf("Found password: %s\n",plain_password3);
      break;
    }

    g++;
    p3++;
  }

  while(*h == *p4) { 
   if(*h == '\0') 
    {
	printf("Found password: %s\n",plain_password4);
      return 1;
    }

    h++;
    p4++;
  }
  return 0;

}


__global__ void  kernel() {
char u,v,w,x;
  
  char password[7];
  password[6] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstValue = i; 
char secondValue = j; 
    
password[0] = firstValue;
password[1] = secondValue;
	for(u='0'; u<='9'; u++){
	  for(v='0'; v<='9'; v++){
            for(w='0'; w<='9'; w++){
               for(x='0'; x<='9'; x++){
	   
	        password[2] = u;
	        password[3] = v;
                password[4] = w;
                password[5] = x;
          is_a_match(password);
	      }
	   }
	}
      }
   }
   

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


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

  return 0;
}


