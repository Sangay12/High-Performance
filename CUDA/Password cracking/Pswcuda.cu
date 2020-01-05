#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************
 Compile and run with:
    nvcc -o Pswcuda Pswcuda.cu
   
    To run
    ./Pswcuda

  Dr Kevan Buckley, University of Wolverhampton, 2019
*****************************************************************************/
__device__ int is_a_match(char *attempt) {
char passw_a[] = "KJ1231";
char passw_b[] = "IP9812";
char passw_c[] = "MM3212";
char passw_d[] = "VC0054";
char *q = attempt;
char *r = attempt;
char *t = attempt;
char *o = attempt;
char *pa1 = passw_a;
char *pa2 = passw_b;
char *pa3 = passw_c;
char *pa4 = passw_d;
while(*q == *pa1) {if(*q == '\0')
{
printf("Found password: %s\n",passw_a);
break;
}
q++;
pa1++;
}
while(*r == *pa2) {
if(*r == '\0')
{
printf("Found password: %s\n",passw_b);
break;
}
r++;
pa2++;
}
while(*t == *pa3) {
if(*t == '\0')
{
printf("Found password: %s\n",passw_c);
break;
}
t++;
pa3++;
}
while(*o == *pa4) {
if(*o == '\0')
{
printf("Found password: %s\n",passw_d);
return 1;
}
o++;
pa4++;
}
return 0;
}

/****************************************************************************
The kernel function assume that there will be only one thread and uses nested loops
to generate all possible passwords and test whether they match the hidden password.
*****************************************************************************/

__global__ void kernel() {
char v,b,m,n;
char password[7];
password[6] = '\0';
int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstValue = i;
char secondValue = j;
password[0] = firstValue;
password[1] = secondValue;
for(v='0'; v<='9'; v++){
for(b='0'; b<='9'; b++){
for(m='0'; m<='9'; m++){
for(n='0'; n<='9'; n++){
password[2] = v;
password[3] = b;
password[4] = m;
password[5] = n;
if(is_a_match(password)) {
//printf("Success");
}
else {
//printf("tried: %s\n", password);
}
}
}
}
}
}
int time_difference(struct timespec *start,
struct timespec *finish,
long long int *difference) {
long long int ds = finish->tv_sec - start->tv_sec;
long long int dn = finish->tv_nsec - start->tv_nsec;
if(dn < 0 ) {ds--;
dn += 1000000000;
}
*difference = ds * 1000000000 + dn;
return !(*difference > 0);
}
int main() {
struct timespec start, finish;
long long int time_elapsed;
clock_gettime(CLOCK_MONOTONIC, &start);
kernel <<<26,26>>>();
cudaThreadSynchronize();
clock_gettime(CLOCK_MONOTONIC, &finish);
time_difference(&start, &finish, &time_elapsed);
printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
(time_elapsed/1.0e9));
return 0;
}
