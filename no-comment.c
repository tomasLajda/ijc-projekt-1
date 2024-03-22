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
  else if(currentChar == '\"') {
    return DOUBLE_QUOTE;
  }
  else if(currentChar == '\"') {
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

int main() {
  FILE *inputFile;
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
        break;
      case DOUBLE_QUOTE:
        currentState = doubleQuoteState(currentChar, previousChar, &doubleBackslash);
        break;
      case SINGLE_QUOTE:
        currentState = singleQuoteState(currentChar, previousChar, &doubleBackslash);
        break;
      default:
        break;
    }

    previousChar = currentChar;
  }
    return 0;
}
