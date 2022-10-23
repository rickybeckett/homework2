#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

int add_user_password(const char* file_name, const char* username, const char* password) {
  char line[256];

  FILE *fptr;

  FILE *file;
  int file_exists = 0;
  file = fopen(file_name, "r");
  if (file != NULL) {
    fclose(file);
    file_exists = 1;
  }


  fptr = fopen(file_name,"a+");
  if (fptr == NULL)
  {
    return -1;
  }

  int check = check_user_password(file_name, username, password);

  if(check == -2) {

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

  char line[256];

  FILE *fptr;
  fptr = fopen(file_name,"r"); 
  if (fptr == NULL)
  {
    return -1;
  }

  int return_value = -2;
  while(fgets(line, sizeof(line), fptr)!= NULL) // goes from line from line 
  {
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

  if(n <= 2) return n;
  
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
}


char* evolve(const char* state) {

  int size_of_game = strlen(state);
  
  char* game_copy;
  game_copy = (char*)malloc(size_of_game);
  
  int i;
  int pebb_count = 0;

  // "-" ascii value is 45
  // "@" ascii value is 64

  for(i = 0; i < size_of_game; i++) // copies the given array into a workable array
  {
    game_copy[i] = '-';
    
    if(state[i] == '@')
    {
      pebb_count++; // counter of how many pebbles
    }
  }

  int* amount_of_pebb = malloc(pebb_count); // sets amount of spaces for array amount_of_peb
  int counter = 0;
  for(i = 0; i < size_of_game; i++) // adds location to amount of pebs
  {
    if(state[i] == '@')
    {
      amount_of_pebb[counter] = i;
      counter++; 
    }
  }

  //int arr_len = (sizeof(amount_of_pebb) / sizeof(amount_of_pebb[0]));
  for(i = 0; i < pebb_count; i++) 
  {
    int current_position = amount_of_pebb[i];

    int next_left = -1;
    int next_right = -1;
    if(i > 0) {
      next_left = amount_of_pebb[i-1];
    }
    if(i < pebb_count - 1) {
      next_right = amount_of_pebb[i+1];
    }

    if(next_left == -1) {
      //most left
      if(next_right > -1) {
        //New position = amount_of_pebb[i] + 1
        if(game_copy[current_position + 1] == '-') {
          game_copy[current_position + 1] = '@';
        }else{
          game_copy[current_position + 1] = '-';
        }
      }else{
        //no other pebbles - do nothing
      }
    }else if(next_right == -1) {
      //most right
      if(next_left > -1) {
        //New position = amount_of_pebb[i] - 1
        if(game_copy[current_position - 1] == '-') {
          game_copy[current_position - 1] = '@';
        }else{
          game_copy[current_position - 1] = '-';
        }
      }else{
        //no other pebbles - do nothing
      }
    }else {
      //middle
      int distance_left = amount_of_pebb[i] - amount_of_pebb[i-1];
      int distance_right = amount_of_pebb[i+1] - amount_of_pebb[i]; 

      if(distance_left == distance_right) {
        //delete
        game_copy[current_position] = '-';
      }else if(distance_left < distance_right) {
        //New position = amount_of_pebb[i] - 1
        if(game_copy[current_position - 1] == '-') {
          game_copy[current_position - 1] = '@';
        }else{
          game_copy[current_position - 1] = '-';
        }
      }else {
        //New position = amount_of_pebb[i] + 1
        if(game_copy[current_position + 1] == '-') {
          game_copy[current_position + 1] = '@';
        }else{
          game_copy[current_position + 1] = '-';
        }
      }
    }
  }

  return game_copy;
  //TODO not here: if pebb_count <= 1 game is over


  // printf("amount of pebles: %d", data_count);

  // general alg: loop through the string, locate where theres something that isn't a dash, have variables of
  // where each of the non-dash elements are, find the distance between those elements, then implement rules, 
  // REPEAT FOR ALL

  // rule A alg:  
  // get the location of where element is, get location of where the left closest element 
  // (number less than, closest to original num), right closest element (number more than, closest to orignial num)
  // whichever is smallest (subtract between the original and left/right), move one back / one forward

  // rule B alg:
  // find location of all elements, if have element to the left and right, subtract both distances from original, 
  // if both answers are equal, erase that element 

  // rule C alg:
  // if element has no other element to the left, and has elements to the right, move it one space to the right 

  // rule D alg:
  // vv of C

  // rule E alg:
  // if both elements end up on the same space (this would happen only after an evolution), erase both from the 
  // string

  // rule F / G alg:
  // no pebles left OR one peble left, the game ends

  // rule H alg:
  // ?? look at first example, how would this be repeating???

  // returns empty string if given empty string
  // return NULL;
}  


char* last_state(const char* state) {
  // implement me

  int repeat = 1;

  char* previous_state;
  previous_state = (char*)malloc(strlen(state));

  for(int i=0; i<strlen(state); i++)  {
    previous_state[i] = state[i];
  }

  char* new_state;

  while(repeat == 1) {

    new_state = evolve(previous_state);

    //is the game over?
    int pebb_count = 0;
    int size_of_game = strlen(new_state);
    int i;

    for(i = 0; i < size_of_game; i++) // copies the given array into a workable array
    {
      if(new_state[i] == '@')
      {
        pebb_count++; // counter of how many pebbles
      }
    }

    //if 1 or 0 pebbles left don't repeat
    if(pebb_count <= 1) {
      repeat = 0;
    }

    //test if new state = state, if yes then don't repeat
    if(strcmp(previous_state, new_state) == 0) {
      repeat = 0;
    }
    
    //make previous the new
    for(int i=0; i<strlen(new_state); i++)  {
      previous_state[i] = new_state[i];
    }

  }

  return new_state;
}  
