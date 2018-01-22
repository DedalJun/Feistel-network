#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>
#include <cmath>
//#include "stdafx.h" 
 
using namespace std;
int binary[2048], keys[30], crbinary[2048];

void str_to_binary(char s[], int &a)
{
	printf( "'%s' Preobrazovanie v binarny kod: " , s );
        int i,c,power, j;
 
     for( i=0 ; s[i]!='\0' ; i++ )
     {
          c = s[i];
          for( power=7 ; power+1 ; power--, a++ )
             if( c >= (1<<power) )
             {
                 c -= (1<<power); 
                 binary[a] = 1;
             }
          else{
             binary[a] = 0;}
     } 
}

void binary_to_str(int a)
{
	char dec;
	int i = 0,j;
    while(1)
     {
        dec = 0;
        for(j=7; j>=0;j--)
        {
             dec += pow(2.0,(double)(j)) * binary[i];
             i++;
             //cout << endl << dec << endl;
        }    
        cout << dec;  
        if(i>a)
        break;              
     }
}

void generate_keys(int r)
{
	for(int i = 0; i < r; i++)
	{
		keys[i] = 0 + rand()%2;
	}
}

int f(int value, int round)
{
	return value ^ keys[round];
}

void Encode(int length, int rounds)
{
	int left[32], right[32], temp[32];
	int c = 0,i;

	while(c < length)
	{
		for(i = c; i < 32+c;i++)
		{
			left[i-c] = binary[i];
			right[i-c] = binary[i+32];
		}

		for(int j = 0; j < rounds; j++)
		{
			for(int p = 0; p < 32; p++)
			{
				temp[p] = right[p] ^ f(left[p],j);
			}

			for(int z = 0; z < 32; z++)
			{
				right[z] = left[z];
				left[z] = temp[z];
			}
		}
		int f = 0, g = 0; 
		for(int j = c; j < 32+c; j++,f++)
		{
			crbinary[j] = left[f];
		}
		for(int j = c+32; j < 64+c; j++,g++)
		{
			crbinary[j] = right[g];
		}
		c += 64;
	}
}

void Decode(int length, int rounds)
{
	int left[32], right[32], temp[32];
	int c = 0,i;

	while(c < length)
	{
		for(i = c; i < 32+c;i++)
		{
			left[i-c] = crbinary[i];
			right[i-c] = crbinary[i+32];
		}

		for(int j = rounds-1; j >= 0; j--)
		{
			for(int p = 0; p < 32; p++)
			{
				temp[p] = left[p] ^ f(right[p],j);
			}

			for(int z = 0; z < 32; z++)
			{
				left[z] = right[z];
				right[z] = temp[z];
			}
		}
		int f = 0, g = 0;
		for(int j = c; j < 32+c; j++, f++)
		{
		    binary[j] = left[f];
		}
		for(int j = c+32; j < 64+c; j++, g++)
		{
			binary[j] = right[g];
		}
		c += 64;
	}
}

int main()
{
     char s[255];
	 int a = 0,rounds;

     printf( "Vvod stroki: " );
     scanf( "%[^\n]s" , s );
	 str_to_binary(s,a);
	 //cout << "\n a = " << a << endl;
	 cout << "\n";
	 for(int i = 0; i < a; i++)
	 cout << binary[i];

	 cout << "\nEnter count of rounds - ";
	 cin >> rounds;
	 generate_keys(rounds);
	
		 while(a % 64 != 0)
		 {
			 binary[a+1] = 0;
			 binary[a+2] = 0;
			 binary[a+3] = 0;
			 binary[a+4] = 0;
			 binary[a+5] = 0;
			 binary[a+6] = 0;
			 binary[a+7] = 0;
			 binary[a+8] = 0;
			 a += 8;
		 }

	 //--------------------------------------------------------------
	 Encode(a,rounds);
	 cout << "\n\nShifr - \n";
	 for(int i = 0; i < a; i++)
	 {
		 cout << crbinary[i];
	 }
	 //--------------------------------------------------------------
	 Decode(a,rounds);
	 cout << "\n\nDShifr - \n";
	 for(int i = 0; i < a; i++)
	 {
		 cout << binary[i];
	 }
     cout << "\nDecoding from binary code - ";
	 binary_to_str(a); 

	 getch();
	return 0;
}