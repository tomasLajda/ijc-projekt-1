// Řešení IJC-DU1, příklad a), 22.3.2024
// Autor: Tomáš Lajda, FIT
// Přeloženo: gcc 11.4.0

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning(const char *fmt, ...) {
  fprintf(stderr, "Warning: ");
  
  va_list args;
  va_start(args, fmt);

  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
}


void error_exit(const char *fmt, ...) {
  fprintf(stderr, "Error: ");

  va_list args;
  va_start(args, fmt);

  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");

  exit(1);
}
