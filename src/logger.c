/*
 * author: alikaanbaci
 * created date: Thursday August 8th 2019
 */

#include<stdarg.h>
#include<stdio.h>

void red () {
  printf("\033[1;31m");
}

void blue () {
  printf("\033[0;34m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}

void log_error(const char* message, ...){ 
  va_list args;   
  red();
  printf("[ERROR] : ");
  reset();
  va_start(args, message);    
  vprintf(message, args);   
  va_end(args); 
  printf("\n");
  }

void log_info(const char* message, ...){   
  va_list args;   
  blue();
  printf("[INFO]  : ");
  reset();
  va_start(args, message);    
  vprintf(message, args);   
  va_end(args); 
  printf("\n");
  }

void log_debug(const char* message, ...){  
  va_list args;   
  yellow();
  printf("[DEBUG] : ");
  reset();
  va_start(args, message);    
  vprintf(message, args);   
  va_end(args); 
  printf("\n");
  }
