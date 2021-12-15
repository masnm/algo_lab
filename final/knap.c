#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float weight;
	float profit;
	float unit_price;
	float selected_part;
	int input_location;
} tuple ;

int dec_by_unit_price ( const void* a, const void* b )
{
	if ( ((tuple*)a)->unit_price > ((tuple*)b)->unit_price )
		return -1;
	if ( ((tuple*)a)->unit_price < ((tuple*)b)->unit_price )
		return 1;
	else
		return 0;
}

int inc_by_input_loc ( const void* a, const void* b )
{
	if ( ((tuple*)a)->input_location > ((tuple*)b)->input_location )
		return 1;
	if ( ((tuple*)a)->input_location < ((tuple*)b)->input_location )
		return -1;
	else
		return 0;
}

void greedy_knapsack ( tuple* arr, int items, int knapsack )
{
	for ( int i = 0 ; i < items ; ++i ) {
		arr[i].unit_price = arr[i].profit / arr[i].weight;
		arr[i].selected_part = 0.0f;
		arr[i].input_location = i;
	}

	qsort ( arr, items, sizeof ( tuple ), dec_by_unit_price );

	float knapsackLeft = knapsack;
	float max_profit = 0.0f;
	int index;
	for ( index = 0 ; index < items ; ++index ) {
		if ( arr[index].weight > knapsackLeft )
			break;
		else {
			arr[index].selected_part = 1.0;
			knapsackLeft = knapsackLeft - arr[index].weight;
		}
	}
	
//	if ( index < items )
//		arr[index].selected_part = knapsackLeft / arr[index].weight;

	qsort ( arr, items, sizeof ( tuple ), inc_by_input_loc );

	for ( int i = 0 ; i < items ; ++i ) {
		max_profit = max_profit +
			( arr[i].selected_part * arr[i].profit );
	}

	printf("Greedy knapsack profit is: %f\n\n",max_profit);
}

float maxf ( float a, float b ) { return (a>b?a:b); }

void zero_one_knapsack ( tuple* arr, int items, int knapsack )
{
	float dp[knapsack+1];
	for ( int i = 0 ; i < knapsack + 1 ; ++i )
		dp[i] = 0.0f;
	for ( int i = 0 ; i < items ; ++i ) {
		int w = (int)arr[i].weight;
		int v = (int)arr[i].profit;
		for ( int j = knapsack ; j >= w ; --j )
			dp[j] = maxf ( dp[j], v + dp[j-w] );
	}
	float max = 0;
	for ( int i = 0 ; i < knapsack+1 ; ++i )
		max = maxf ( max, dp[i] );
	printf ( "0/1 knapsack profit is : %f\n", max );
}

int main()
{
	int items;
	float knapsack;

	printf ( "Enter the number of items : " );
	scanf ( "%d", &items );
	printf ( "Enter the size of kanapsack : " );
	scanf ( "%f", &knapsack );

	tuple* arr = (tuple*) malloc ( sizeof(tuple) * items );

	for ( int i = 0 ; i < items ; ++i ) {
		float _weight, _profit;
		printf ( "Enter the weight and profit of item %d : ", i+1 );
		scanf ( "%f %f", &_weight, &_profit );
		arr[i].weight = _weight;
		arr[i].profit = _profit;
	}

	greedy_knapsack ( arr, items, knapsack );
	zero_one_knapsack ( arr, items, knapsack );

	free ( arr );

	return 0;
}
