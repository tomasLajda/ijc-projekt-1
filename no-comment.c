// Řešení IJC-DU1, příklad b), 22.3.2024
// Autor: Tomáš Lajda, FIT
// Přeloženo: 11.4.0

#include <stdio.h>
#include <stdbool.h>

#include "error.h"

// Definition of states
typedef enum {
  CODE,
  SINGLE_LINE_COMMENT,
  MULTI_LINE_COMMENT,
  DOUBLE_QUOTE,
  SINGLE_QUOTE
} State;

// Functions for each state
State codeState(char currentChar, char previousChar) {
  if(previousChar == '/') {
    if(currentChar == '/') {
      return SINGLE_LINE_COMMENT;
    }
    else if(currentChar == '*') {
      return MULTI_LINE_COMMENT;
    }
  }
  
  if(currentChar == '"') {
    return DOUBLE_QUOTE;
  }
  
  if(currentChar == '\'') {
    return SINGLE_QUOTE;
  }

  return CODE;
}

State singleLineState(char currentChar) {
  if(currentChar == '\n') {
    return CODE;
  }

  return SINGLE_LINE_COMMENT;
}

State multiLineState(char currentChar, char previousChar) {
  if(previousChar == '*' && currentChar == '/') {
    return CODE;
  }

  return MULTI_LINE_COMMENT;
}

State doubleQuoteState(char currentChar, char previousChar, bool* doubleBackslash) {
  if(currentChar == '"' && (previousChar != '\\' || (*doubleBackslash))) {
    return CODE;
  }

  if(previousChar == '\\' && currentChar == '\\' && !(*doubleBackslash)) {
    *doubleBackslash = true;
  }
  else {
    *doubleBackslash = false;
  }

  return DOUBLE_QUOTE;
}

State singleQuoteState(char currentChar, char previousChar, bool* doubleBackslash) {
  if(currentChar == '\'' && (previousChar != '\\' || (*doubleBackslash))) {
    return CODE;
  }

  if(previousChar == '\\' && currentChar == '\\' && !(*doubleBackslash)) {
    *doubleBackslash = true;
  }
  else {
    *doubleBackslash = false;
  }

  return SINGLE_QUOTE;
}

int main(int argc, char *argv[]) {
  FILE *inputFile;

  if (argc > 1) {
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
      error_exit("file did not open");
    }
  } else {
    inputFile = stdin;
  }

  State currentState = CODE;
  char currentChar = ' ';
  char previousChar = ' ';
  bool doubleBackslash = false;
  
  while ((currentChar = fgetc(inputFile)) != EOF) {
    switch (currentState) {
      case CODE:
        currentState = codeState(currentChar, previousChar);
        break;
      case SINGLE_LINE_COMMENT:
        currentState = singleLineState(currentChar);
        break;
      case MULTI_LINE_COMMENT:
        currentState = multiLineState(currentChar, previousChar);
        if(currentState == CODE) {
          continue;
        }
        break;
      case DOUBLE_QUOTE:
        currentState = doubleQuoteState(currentChar, previousChar, &doubleBackslash);
        break;
      case SINGLE_QUOTE:
        currentState = singleQuoteState(currentChar, previousChar, &doubleBackslash);
        break;
      default:
        error_exit("unexpected state");
        break;
    }

    if(currentState != SINGLE_LINE_COMMENT && currentState != MULTI_LINE_COMMENT ) {
      if(currentState == CODE && previousChar == '/') {
        fprintf(stdout, "%c", previousChar);
      }
      
      if(!(currentState == CODE && currentChar == '/')) {
        fprintf(stdout, "%c", currentChar);
      } 
    }

    previousChar = currentChar;
  }

  if (argc > 1) {
    fclose(inputFile);
  }
  
  return 0;
}
