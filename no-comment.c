#include <stdio.h>

#include "error.h"

// Definition of states
typedef enum {
  CODE,
  SINGLE_LINE_COMMENT,
  MULTI_LINE_COMMENT,
  DOUBLE_QUOTE,
  SINGLE_QUOTE,
  BACKSLASH
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

State singleLineState(char currentChar, char previousChar) {
  
}

State multiLineState(char currentChar, char previousChar) {

}

State doubleQuoteState(char currentChar, char previousChar) {

}

State singleQuoteState(char currentChar, char previousChar) {

}

State backslashState(char currentChar, char previousChar) {
  
}

int main() {
  FILE *inputFile;
  State currentState = CODE;
  char currentChar = ' ';
  char previousChar = ' ';
  
  while ((currentChar = fgetc(inputFile)) != EOF) {
    switch (currentState) {
      case CODE:
        currentState = codeState(currentChar, previousChar);
        break;
      case SINGLE_LINE_COMMENT:
        currentState = singleLineState(currentChar, previousChar);
        break;
      case MULTI_LINE_COMMENT:
        currentState = multiLineState(currentChar, previousChar);
        break;
      case DOUBLE_QUOTE:
        currentState = backslashState(currentChar, previousChar);
        break;
      case SINGLE_QUOTE:
        currentState = backslashState(currentChar, previousChar);
        break;
      case BACKSLASH:
        currentState = backslashState(currentChar, previousChar);
        break;
      default:
        break;
    }

    previousChar = currentChar;
  }
    return 0;
}
