/*
 * Program name:swap_for_min 
 *         input: num,swap
 *        output: min
 *   Explanation：For any positive integer num, we can exchange any two of them (decimal), some exchanges can get a smaller positive 
 * integer, such as 76421, we can get a smaller by swapping the highest and lowest bits Positive integer: 16427. The function of the 
 * program is to calculate the smallest positive integer that can be obtained for any positive integer num (num<=104875, ie its binary
 * form does not exceed 20 bits), and at most swap (swap<20).
 */
//zhou
#include <stdio.h>

typedef unsigned int uint;

#define num_maxlimit 1048575
#define swap_limit 19

static int number_of_digits = 0;
/*
 * Function name:swap_for_min 
 *         input: num,swap
 *        output: num_origion
 *   Explanation：
 *  1、Find the position of the smallest number each time you loop
 *  2、Find the smallest number of the remaining number
 *  3、Judging the lower limit of swap_num  
 *  4、Exchange number 
 */

int *swap_for_min(uint number,uint swap_num)
{
	static int num_orig[6] = {0};
	int num_buf[6] = {0};
	int min_num_pos = 0, min_num = 0;
	int loop_t = 0;
	number_of_digits = 0;
	do
	{
		num_buf[number_of_digits] = number % 10;
		number_of_digits++;
	}while(number /= 10);

	int j = number_of_digits - 1;
	for(int i = 0; i < number_of_digits; i++)
	{
		num_orig[i] = num_buf[j--];
	}

	int m,n;
	for (n = 0; (n < number_of_digits - 1); n++)
	{
		min_num = 9;
		for(m = n + 1;m < number_of_digits;m++)
		{
			if((num_orig[m] < num_orig[n]) && (num_orig[m] <= min_num))
			{
				min_num = num_orig[m];
				min_num_pos = m;
			}
		}

		if(min_num_pos != 0)
		{
			if(loop_t < swap_num)
			{
				num_orig[min_num_pos] = num_orig[n];
				min_num_pos = 0;
				num_orig[n] = min_num;
				loop_t++;
			}
			else
			{
				break;
			}
		} 

	}
	return num_orig;
}


int main()
{
	uint num[20] = {0}, swap[20] = {0}, *swap_number = NULL;
	char s[20]={0};
	while(1)
	{
		printf("\n输入: num=");
		scanf("%d", num);
		printf("swap=");
		scanf("%d", swap);
		if((num[0] > num_maxlimit)||(swap[0] > swap_limit))
		{
			printf("Error: the input number is wrong!\n");
			printf("Maybe the num is not a positive integer,"\
					" or the swap number is bigger than 19\n");
		}
		else
		{
			swap_number = swap_for_min(num[0],swap[0]);
			printf("输出: min=:");
			for(int i = 0; i < number_of_digits; i++)
			{
				printf("%d", *(swap_number + i));
			}
			printf("\n\n");

select:
			printf("Do you want to continue? \nIf yes, input y,else input n:");
			scanf("%s",s);
			if((s[0] == 'y')&&(s[1] == 0))
			{
				printf("\nSwap for the smallest number again!\n");
				continue;
			}
			else if((s[0] == 'n')&&(s[1] == 0))
			{
				printf("\nProgram exited.\n\n");
				return 0;
			}
			else
			{
				printf("\nThe input character is wrong.\n\n");
				goto select;
			}
		}
	}
}
