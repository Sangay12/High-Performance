#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
/******************************************************************************
Demonstrates how to crack an encrypted password using a simple "brute force"
algorithm. Works on passwords that consist only of 2 Uppercase letters and a 2 digit
integer. Your personalised data set is included in the code.
Compile with:
mpicc -o Pswmpi Pswmpi.c -lcrypt (to compile)
mpirun -n 3 ./Pswmpi(to run)If you want to analyse the results then use the redirection operator to send output to
a file that you can view using an editor or the less utility:
./Pswmpi> mpiresults.txt
Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;
char *encrypted_passwords[] = {
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
This function can crack the kind of password explained above. All combinations that
are tried are displayed and when the password is found, #, is put at the start of the
line. Note that one of the most time consuming operations that it performs is the output
of intermediate results, so performance experiments for this kind of program should
not include this. i.e. comment out the printfs.
*/


int time_difference(struct timespec *start, struct timespec *finish, 
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



void function_1(char *salt_and_encrypted){
int x, y, z; // Loop counters
char salt[7]; // String used in hashing the password. Need space
char plain[7]; // The combination of letters currently being checkedchar *enc;
// Pointer to the encrypted password
char *enc;
int count = 0; // The number of combinations explored so far
substr(salt, salt_and_encrypted, 0, 6);
for(x='A'; x<='M'; x++){
for(y='A'; y<='Z'; y++){
for(z=0; z<=99; z++){
printf("Instance 1");
sprintf(plain, "%c%c%02d", x, y, z);
enc = (char *) crypt(plain, salt);
count++;
if(strcmp(salt_and_encrypted, enc) == 0){
printf("#%-8d%s %s\n", count, plain, enc);
} else {
printf(" %-8d%s %s\n", count, plain, enc);
}
}
}
}
printf("%d solutions explored\n", count);
}


void function_2(char *salt_and_encrypted){
int x, y, z; // Loop counters
char salt[7]; // String used in hashing the password. Need space
char plain[7]; // The combination of letters currently being checked
char *enc;
// Pointer to the encrypted password
int count = 0; // The number of combinations explored so far
substr(salt, salt_and_encrypted, 0, 6);
for(x='N'; x<='Z'; x++){
for(y='A'; y<='Z'; y++){
for(z=0; z<=99; z++){
printf("Instance 2");
sprintf(plain, "%c%c%02d", x, y, z);
enc = (char *) crypt(plain, salt);
count++;
if(strcmp(salt_and_encrypted, enc) == 0){
printf("#%-8d%s %s\n", count, plain, enc);
} else {
printf(" %-8d%s %s\n", count, plain, enc);
}
}}
}
printf("%d solutions explored\n", count);
}


int main(int argc, char *argv[]){
struct timespec start, finish;
long long int difference;
int account = 0;
clock_gettime(CLOCK_MONOTONIC, &start);
int size, rank;
MPI_Init(NULL, NULL);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if(size != 3) {
if(rank == 0) {
printf("This program needs to run on exactly 3 processes\n");
}
} else {
if(rank ==0){
int x;
int y;
MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
MPI_Send(&y, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
} else {
if(rank == 1){
int i;
int number = rank + 10;
MPI_Recv(&number,1,MPI_INT,0,0,
MPI_COMM_WORLD,MPI_STATUS_IGNORE);
for ( i = 0; i<n_passwords;i<i++){
function_1(encrypted_passwords[i]);
}
}
else if(rank == 2){
int i;
int number = rank + 10;MPI_Recv(&number,1,MPI_INT,0,0,
MPI_COMM_WORLD,MPI_STATUS_IGNORE);
for ( i = 0; i<n_passwords;i<i++){
function_2(encrypted_passwords[i]);
}
}
}
}
MPI_Finalize();
clock_gettime(CLOCK_MONOTONIC, &finish);
time_difference(&start, &finish, &difference);
printf("Elapsed Time: %9.5lfs\n", difference/1000000000.0);
return 0;
}

