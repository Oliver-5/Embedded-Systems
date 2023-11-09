#include "mbed.h"


int main(void)
{

  char ch = 66;

  switch(ch)
  {
    case 'A':
      printf("%i is an A", ch);
      break;
    case 'B':
      printf("%i is a B", ch);;
      break;
    case 'C':
      printf("%i is a C", ch);;
      break;
    default:
      printf("Error");
  }

  return 0;
}