#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

int add_user_password(const char* file_name, const char* username, const char* password) {

  const char *username = username;
  char line[256];

  FILE *fptr;
  fptr = fopen(file_name,"r+"); // if file_name doesn't exist, will it automatically create that file name?
  if (fptr == NULL)
  {
    printf("Unable to open file.");
  }

  while(fgets(line, sizeof(line), fptr)!= NULL) // goes from line from line 
  {
    // Im assuming the data is seperated by commas... how would I check for the username..
    // the username would be first / password would be second? do i first check if the username in file has the 
    // same amount of chars as the user given.. then would I check if the chars are the same?

  }




  return -1;
}


int check_user_password(const char* file_name,
                    const char* username, const char* password) {
  // implement me
  return -1;
}

// FINISHED
int fib3_p(unsigned int n, unsigned int p) {

  int zero = 0;
  int one = 1;
  int two = 2;
  int i;
  int fib_mod;

  for(i = 0; i <= n-3; i++)
  {
      fib_mod = ((zero + one + two) % p);
      zero = one;
      one = two;
      two = fib_mod;
  }
  return two;


  // return -1;
}


char* evolve(const char* state) {
  // implement me
  return NULL;
}  


char* last_state(const char* state) {
  // implement me
  return NULL;
}  
  