#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

int add_user_password(const char* file_name, const char* username, const char* password) {
  char line[256];

  FILE *fptr;

  //check if file exists first
  FILE *file;
  int file_exists = 0;
  file = fopen(file_name, "r");
  if (file != NULL) {
    fclose(file);
    file_exists = 1;
  }

  //open or create file
  fptr = fopen(file_name,"a+");
  if (fptr == NULL)
  {
    return -1;
  }

  int check = check_user_password(file_name, username, password);

  if(check == -2) {
    //Add line break only if new file?
    if(file_exists == 1) fputs("\n", fptr);  
    fputs(username, fptr);
    fputs(",", fptr);
    fputs(password, fptr);
    fclose(fptr);
    return 1;
  }

  if(check == 1 || check == -3) {
    fclose(fptr);
    return 0;
  }
}


int check_user_password(const char* file_name,
                    const char* username, const char* password) {
  // implement me
  char line[256];

  FILE *fptr;
  fptr = fopen(file_name,"r"); // if file_name doesn't exist, will it automatically create that file name?
  if (fptr == NULL)
  {
    return -1;
  }

  //format of the files
  //username1,password1
  //username2,password2
  int return_value = -2;
  while(fgets(line, sizeof(line), fptr)!= NULL) // goes from line from line 
  {
    //look for username in first token, password in second token
    //If the username is found and the password matches, the function returns 1.
    //If the username is not found, the function returns -2.
    //If the username is found but the password doesn’t match, the function returns -3.
    // check for length of username, that each char matches and that the next char is a ,
    char* parsed_username;
    char* parsed_password;
    char* pch = strtok (line,",");
    int i = 0;
    while (pch != NULL)
    {
      if(i == 0){
        parsed_username = pch;
      }else{
        parsed_password = pch;
      }
      pch = strtok (NULL, ",");
      i++;
    }

    if(strcmp(username, parsed_username) == 0) {
      //check password
      if(strcmp(password, parsed_password) == 0) {
        return_value = 1;
        break;
      }else {
        return_value = -3;
        break;
      }
    }
  }

  fclose(fptr);
  return return_value;
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
  