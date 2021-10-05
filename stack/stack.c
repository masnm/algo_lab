#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

const int max_stack_size = 1005;

typedef enum {
	overflow,
	underflow,
	empty_acc,
	alloc_fail,
	unknown_type
} error_code ;

typedef enum {
	stack_int,
	stack_char,
	stack_float,
	stack_long_long
} data_type ;

typedef struct stack {
	data_type type;
	size_t size;
	void* data;
	void* top;
	size_t c_top;
} stack ;

stack stack_create ( data_type type );
void stack_push ( stack* s, void* val );
bool stack_pop ( stack* s );
void* stack_top ( stack* s );
bool stack_empty ( stack* s );
void stack_print ( stack* s );
void stack_destroy ( stack* s );
void error_exit ( stack* s, error_code code );

void error_exit ( stack* s, error_code code )
{
	assert ( false );
}

stack stack_create ( data_type type )
{
	size_t effective_size = 0;
	if ( type == stack_int ) {
		effective_size = max_stack_size * sizeof(int);
	} else if ( type == stack_char  ) {
		effective_size = max_stack_size * sizeof(char);
	} else if ( type == stack_float  ) {
		effective_size = max_stack_size * sizeof(float);
	} else if ( type == stack_long_long  ) {
		effective_size = max_stack_size * sizeof(long long);
	} else {
		error_exit ( NULL, unknown_type );
	}
	stack s;
	s.type = type;
	s.size = max_stack_size;
	s.data = malloc ( effective_size );
	s.top = malloc ( effective_size / max_stack_size );
	s.c_top = 0;
	if ( s.data == NULL || s.top == NULL )
		error_exit ( &s, alloc_fail );
	return s;
}

void stack_push ( stack* s, void* val )
{
	if ( 1 + s -> c_top >= s -> size )
		error_exit ( s, overflow );
	++ s -> c_top;
	if ( s -> type == stack_int ) {
		((int*)s -> data)[s -> c_top] = *(int*)val;
	} else if ( s -> type == stack_char  ) {
		((char*)s -> data)[s -> c_top] = *(char*)val;
	} else if ( s -> type == stack_float  ) {
		((float*)s -> data)[s -> c_top] = *(float*)val;
	} else if ( s -> type == stack_long_long  ) {
		((long long*)s -> data)[s -> c_top] = *(long long*)val;
	} else {
		error_exit ( NULL, unknown_type );
	}
#warning find better solution here
	if ( s -> type == stack_int ) {
		int x = ( (int*)s -> data ) [ s -> c_top ];
		*((int*)s -> top) = x;
	} else if ( s -> type == stack_char ) {
		char x = ( (char*)s -> data ) [ s -> c_top ];
		*((char*)s -> top) = x;
	} else if ( s -> type == stack_float ) {
		float x = ( (float*)s -> data ) [ s -> c_top ];
		*((float*)s -> top) = x;
	} else if ( s -> type == stack_long_long ) {
		long long x = ( (long long*)s -> data ) [ s -> c_top ];
		*((long long*)s -> top) = x;
	} else {
		error_exit ( NULL, unknown_type );
	}
}

bool stack_pop ( stack* s )
{
	if ( s -> c_top < 1 )
		error_exit ( s, underflow );
	-- s -> c_top;
	if ( s -> type == stack_int ) {
		int x = ( (int*)s -> data ) [ s -> c_top ];
		*((int*)s -> top) = x;
	} else if ( s -> type == stack_char ) {
		char x = ( (char*)s -> data ) [ s -> c_top ];
		*((char*)s -> top) = x;
	} else if ( s -> type == stack_float ) {
		float x = ( (float*)s -> data ) [ s -> c_top ];
		*((float*)s -> top) = x;
	} else if ( s -> type == stack_long_long ) {
		long long x = ( (long long*)s -> data ) [ s -> c_top ];
		*((long long*)s -> top) = x;
	} else {
		error_exit ( NULL, unknown_type );
	}
	return true;
}

void* stack_top ( stack* s )
{
	if ( s -> c_top < 1 )
		error_exit ( s, empty_acc );
	return s -> top;
}

void stack_print ( stack* s )
{
	printf ( "Type = " );
	if ( s -> type == stack_int ) puts ( "int" );
	else if ( s -> type == stack_char ) puts ( "char" );
	else if ( s -> type == stack_float ) puts ( "float" );
	else if ( s -> type == stack_long_long ) puts ( "long long" );
	else {
		error_exit ( NULL, unknown_type );
	}
	printf ( "Max Size = %zd\n", s -> size );
	printf ( "Data Address = %p\n", s -> data );
	printf ( "Current Top = " );
	if ( s -> top != NULL ) {
		if ( s -> type == stack_int )
			printf ( "%d\n", *(int*)s -> top );
		else if ( s -> type == stack_char )
			printf ( "%c\n", *(char*)s -> top );
		else if ( s -> type == stack_float )
			printf ( "%f\n", *(float*)s -> top );
		else if ( s -> type == stack_long_long )
			printf ( "%lld\n", *(long long*)s -> top );
	} else {
		printf ( "%p\n", s -> top );
	}
	printf ( "Current Filled = %zd\n", s -> c_top );
	if ( s -> data != NULL ) printf ( "Current contents are\n" );
	for ( size_t i = 1 ; i <= s -> c_top ; ++i ) {
		if ( s -> type == stack_int )
			printf ( "%d ", ((int*)s -> data)[i] );
		else if ( s -> type == stack_char )
			printf ( "%c ", ((char*)s -> data)[i] );
		else if ( s -> type == stack_float )
			printf ( "%f ", ((float*)s -> data)[i] );
		else if ( s -> type == stack_long_long )
			printf ( "%lld ", ((long long*)s -> data)[i] );
	}
	puts ( "\n" );
}

void stack_destroy ( stack* s )
{
	free ( s -> data );
	s -> data = NULL;
	s -> size = 0;
	s -> c_top = 0;
	free ( s -> top );
	s -> top = NULL;
}

int main ()
{
	stack s = stack_create ( stack_char );
	for ( int i = 0 ; i < 15 ; ++i ) {
		char x = 'Z' - i;
		if ( i & 1 ) {
			printf("poping at %d %c\n", i, *(char*)stack_top(&s) );
			stack_pop ( &s );
		}
		stack_push ( &s, &x );
	}
	stack_print ( &s );
	stack_destroy ( &s );

	s = stack_create ( stack_int );
	for ( int i = 0 ; i < 15 ; ++i ) {
		int x = 45 - i;
		if ( i & 1 ) {
			printf("poping at %d %d\n", i, *(int*)stack_top(&s) );
			stack_pop ( &s );
		}
		stack_push ( &s, &x );
	}
	stack_print ( &s );
	stack_destroy ( &s );

	s = stack_create ( stack_float );
	for ( int i = 0 ; i < 15 ; ++i ) {
		float y = i;
		y /= 10;
		float x = 45 - (float)i - y;
		if ( i & 1 ) {
			printf("poping at %d %f\n", i, *(float*)stack_top(&s) );
			stack_pop ( &s );
		}
		stack_push ( &s, &x );
	}
	stack_print ( &s );
	stack_destroy ( &s );


	return 0;
}
