#include <stdio.h>
#include <stdlib.h> // atof- array to float
#include <string.h> // for strcmp
#include <ctype.h>  // isdigit
#define stacklen 15 // defining array of length 15 here so we don't have to change everywhere if we change.


void push(double *index, double newval) // push: increments items in stack.
{
    *(index +1) =newval; // we want next index val to be on top as new value 
}

void pop(double *index) // pasing index bc in array we can only add numbers in the bottom so we need to know which index the number is at
{
    *index = 0; // top value in stack with index 0
}

void max(double *index)
{
    double temp = 0;
    if((index) > (index-1))
    {
        pop((index-1));
        temp= *index;
    }
    else if ((index) < (index-1))
    {
        pop(index);
        temp = *(index-1);
    }

    push(index, temp);
}

 void min(double *index)
{
double temp = 0;
    if((index) > (index-1))
    {
        pop((index));
        temp= *index;
    }
    else if ((index) < (index-1))
    {
        pop((index-1));
        temp = *(index-1);
    }

    push(index, temp);
}


void add(double *index) 
{
    double temp= 0; // defining temperory variable where we will save the sum initially
    temp= *(index) + *(index-1); //(-1) bc we are each new number goes on top so we go right to left addition of values where 1st and 2nd index pointed
    pop(index); // popping last number
    index--; 
    pop(index);
    index--;
    push(index, temp); // pushing the new var temp to that location
}

void subtract(double *index)
{
    double temp= 0;
    temp= *(index) - *(index-1);
    pop(index); // bc we want the top 2 numbers in stack
    index--;
    pop(index);
    index--;
    push(index, temp); // 
}

void multiply(double *index)
{
    double temp= 0;
    temp= *(index) * *(index-1);
    pop(index);
    index--;
    pop(index);
    index--;
    push(index, temp);
}

void divide(double *index)
{
    double temp = 0;
    temp= *(index) / *(index-1);

    if (*(index-1)== 0) // denominator == 0 
    {
        printf("ERROR: DIVIDE BY ZERO");
        exit(1); // exits after 1 sec
    }

    pop(index);
    index--;
    pop(index);
    index--;
    push(index, temp);
}

void negate(double *index)
{
    *index = *index * -1; // dont need a temp var to save val in
}
// new val where the index points = that val x -1
void square(double *index)
{
    *index= *(index) * *(index);
}

void checkEmpty(double *index, double stack[stacklen]) // the array we are passing is stacklen big
{
    if(index<=stack) // index starts with 0 so <=16
    {
        printf("ERROR: STACK EMPTY");
        exit(1);
    }
}

void checkOverflow(double *index, double stack[stacklen])
{
    if((stack+stacklen-1)==index) // checks if at last position
    {
        printf("ERROR: STACK OVERFLOW");
        exit(1);
    }
}

void checkError(char lineOfText[])
{
    int i = 0;
    int numberOfDecimals = 0; // variable

    if(lineOfText[0]=='-') // checking if index 0 is -
    {
        lineOfText++; // go to the next char
    }

    while(lineOfText[i]!='\n') // while we're on the same line
    {
        if(lineOfText[i]=='.')
        {
            numberOfDecimals++;
        }
        else if(isdigit(lineOfText[i]) == 0) //if its not a digit
        {
            printf("ERROR: INVALID INPUT\n");
            exit(1);
        }
        i++;
    }
    if(numberOfDecimals>1)
    {
        printf("ERROR: INVALID INPUT\n");
        exit(1);
    }
}
int main()
{
    double stack[stacklen]; // array
    stack[0]=0.0; // first element in stack id 0 by defualt

    double *index = stack; // defining the pointer that index points to stack val
    FILE *myFileHandle; // defining txt file
    myFileHandle = fopen("sum.txt", "r"); //  file name is sum.txt, r for read

    if(myFileHandle != NULL)
    {
        char lineOfText[80]; // new array of 80 characters

        while(fgets(lineOfText, 80, myFileHandle) != NULL) // fgets: to get the next line. 80: bits. myFileHandle: pointer to the file
        {
            if(strncmp (lineOfText, "add", 3)==0) // comparing is add = the word in file.
            {  
                checkEmpty(index,stack); // checking if the stack is empty
                
                add(index); // calling function add.
                index--; 
            }
            else if((strncmp (lineOfText, "subtract", 8)==0))
            {
                checkEmpty(index,stack);
                subtract(index);
                index--;
            }
            else if((strncmp (lineOfText, "multiply", 8)==0))
            {
                checkEmpty(index,stack);
                multiply(index);
                index--;
            }
            else if((strncmp (lineOfText, "divide", 6)==0))
            {
                checkEmpty(index,stack);
                divide(index);
                index--;
            }
            else if((strncmp (lineOfText, "negate", 6)==0))
            { // no need to check if its empty bc the first element is 0 and it works anyways.
                negate(index);
                index--;
            }
            else if((strncmp (lineOfText, "square", 6)==0))
            {
                square(index);
                index--;
            }
            else if ((strncmp(lineOfText, "max",3) ==0))
            {
                checkEmpty(index, stack);
                max(index);
                index--;
            }
            else if ((strncmp(lineOfText, "min",3) ==0))
            {
                checkEmpty(index, stack);
                min(index);
                index--;
            }
            
            
            else if (isdigit(lineOfText[0])!=0||(lineOfText[0]=='-' && isdigit(lineOfText[1])!=0)) // index[0] != 0 OR (index[0] = - and index[1]!= 0)
            {
                checkError(lineOfText);
                checkOverflow(index,stack);
                push(index, atof(lineOfText)); // add the number
                index++;
            }
            else
            {
                printf("ERROR: INVALID INPUT");
                exit(1);
            }
       }
        fclose(myFileHandle);
    }
    printf("%f", *index); // we need the latest element in the array(what index is pointing to)
}
