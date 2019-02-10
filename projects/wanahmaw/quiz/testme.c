// Wan Ashraf Wan Ahmad Ezani

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  int minAscii = 32;
  int maxAscii = 126;
    // Produce random values
    // Get every char in the ASCII table
    // From 32 to 126
  char randCh = rand() % (maxAscii + 1 - minAscii) + minAscii;
  return randCh;
}

char *inputString()
{
  int i;
  int len = 5;
  int minAscii = 97;
  int maxAscii = 122;
  char* ranStr = (char*) malloc((len + 1) * sizeof(char));
  
  for (i = 0; i < len; i++) //add a random char & leave last for \0
      ranStr[i] = rand() % (maxAscii + 1 - minAscii) + minAscii;
  ranStr[len] = '\0';

  return ranStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
