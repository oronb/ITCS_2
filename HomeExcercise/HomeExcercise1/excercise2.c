//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void printFormattedIntegers(char* format, char* numbers);
int convertStringToInt(char* string);
void printRomfromDec(int num);
void printBinFromDec(int num);

void main()
{
    //char format[100];
    //char numbers[100];
    char format[200] = "The number %d in roman numerals is %r";
    char numbers[400] = "1928 1928";
    //gets(format);
    //gets(numbers);
    printFormattedIntegers(format, numbers);
}

void printFormattedIntegers(char* format, char* numbers)
{
    char *token;
    int i=0, num;
    const char s[2] = " ";
    token=strtok(numbers, s);

    while(*(format + i) != '\0')
    {
        if(*(format + i) != '%')
        {
            printf("%c", *(format + i));
        }
        else
        {
            num=convertStringToInt(token);
            i++;
            switch (*(format + i))
            {
                case 'd':
                    printf("%d", num);
                    break;
                case 'x':
                    printf("%x", num);
                    break;   
                case 'o':
                    printf("%o", num);
                    break; 
                case 'b':
                    printBinFromDec(num);
                    break; 
                case 'r':
                    printRomfromDec(num);
                    break;                                                   
                default:
                    break;
            }
            token = strtok(NULL, s);
        }
        i++;        
    }
}

int convertStringToInt(char* string)
{
    int j=0, num=0;
    while (*(string + j) != '\0')
    {
        num = num * 10 + (*(string + j) - '0');
        j++;
    } 
    return num;    
}

void printRomfromDec(int num)
{
  int countDig=0; 
  int i=0; // Index
  int divNum=num; //Divided number (The left digit of the number)
  int divNumTen;
  if (num == 0)
    return;
  else if (num == 1)
  {
      printf("I");
      return;
  }
  else if (num == 5) 
  {
      printf("V");
      return;
  }
  else if (num == 10)
  {
      printf("X");
      return;
  }
  else if (num == 50)
  {
      printf("L");
      return;
  }
  else if (num == 100)
  {
      printf("C");
      return;
  }  
  else if (num == 500)
  {
      printf("D");
      return;
  }
  else if (num == 1000)
  {
      printf("M");
      return;
  }
  else if (num == 4000)
  {
      printf("MMMM");
      return;
  }
  else
  {
      if (num < 10)
      {
          divNumTen = 1;
          divNum = num;
      }
      else
      {
          while(divNum >= 10)
          {
              divNum = divNum / 10;
              countDig++;
          }
          //Multiple the left digit in ten pow the number of digits after the left digit 
          divNumTen = 1;
          for(i=1;i<=countDig;i++)
          {
              divNumTen = divNumTen * 10;
          }
      }         
      if((divNum >= 1) && (divNum <= 3))
      {
        for(i = 1; i <= divNum; i++)
            printRomfromDec(divNumTen);
      }
      else if((divNum == 4) || (divNum == 9))
      {
        printRomfromDec(divNumTen);
        printRomfromDec((divNum * divNumTen) + divNumTen);
      }
      else if((divNum >= 6) && (divNum <= 8))
      {
        printRomfromDec(5 * divNumTen);
        printRomfromDec((divNum - 5) * divNumTen);
      }
      //printf("Print %d before sending to recursion", num);
      printRomfromDec(num - (divNum * divNumTen));
      //printRomfromDec(2);

    }    
}

void printBinFromDec(int num)
{
    int dig;
    if(num == 0)
        return;
    else 
    {
        dig = num % 2;
        num = num / 2;
        printBinFromDec(num);
        printf("%d", dig);
    }
}