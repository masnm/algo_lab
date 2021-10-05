#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

const int max_array_size = 1005;

typedef enum {
	overflow,
	empty_acc,
	alloc_fail,
	unknown_type
} array_error_code ;

typedef enum {
	array_bool,
	array_int,
	array_long,
	array_long_long,
	array_char,
	array_float,
	array_double,
	array_long_double
} array_data_type ;

typedef struct array {
	array_data_type type;
	size_t size;
	void* data;
	void* top;
	size_t c_top;
} array ;

void array_destroy ( array* a )
{
	if ( a == NULL ) return;
	if ( a -> top != NULL )
		free ( a -> top );
	if ( a -> data != NULL )
		free ( a -> data );
	a -> size = 0;
	a -> c_top = 0;
}

void array_error_exit ( array* a, array_error_code code )
{
	if ( a != NULL )
		array_destroy ( a );
	if ( code == overflow )
		puts ( "Pushing on Filled Array" );
	else if ( code == empty_acc )
		puts ( "Accessing an Empty Array" );
	else if ( code == alloc_fail )
		puts ( "Memory allocation Failed" );
	else if ( code == unknown_type )
		puts ( "Unknown array type" );
	else
		puts ( "Unknown error code" );
	fflush ( stdout );
	assert ( false );
}

bool array_empty ( array* a )
{
	return a -> c_top == 0;
}

bool array_full ( array* a )
{
	return 1 + a -> c_top == a -> size;
}

bool array_push_back ( array* a, void* val )
{
	if ( array_full ( a ) )
		array_error_exit ( a, overflow );
	++ a -> c_top;
	if ( a -> type == array_bool )
		((bool*) a -> data) [ a -> c_top ] = *(bool*)val;
	else if ( a -> type == array_int )
		((int*) a -> data) [ a -> c_top ] = *(int*)val;
	else if ( a -> type == array_long )
		((long*) a -> data) [ a -> c_top ] = *(long*)val;
	else if ( a -> type == array_long_long )
		((long long*) a -> data) [ a -> c_top ] = *(long long*)val;
	else if ( a -> type == array_char )
		((char*) a -> data) [ a -> c_top ] = *(char*)val;
	else if ( a -> type == array_float )
		((float*) a -> data) [ a -> c_top ] = *(float*)val;
	else if ( a -> type == array_double )
		((double*) a -> data) [ a -> c_top ] = *(double*)val;
	else if ( a -> type == array_long_double )
		((long double*) a -> data) [ a -> c_top ] = *(long double*)val;
	else array_error_exit ( NULL, unknown_type );
	return true;
}

void* array_at ( array* a, size_t index )
{
	// Maybe some more error cheak
	if ( array_empty ( a ) || a -> c_top < index )
		array_error_exit ( a, empty_acc );
	if ( a -> type == array_bool ) {
		*((bool*) a -> top ) = ((bool*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_int ) {
		*((int*) a -> top ) = ((int*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_long ) {
		*((long*) a -> top ) = ((long*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_long_long ) {
		*((long long*) a -> top ) = ((long long*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_char ) {
		*((char*) a -> top ) = ((char*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_float ) {
		*((float*) a -> top ) = ((float*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_double ) {
		*((double*) a -> top ) = ((double*) a -> data) [ index ];
		return a -> top;
	} else if ( a -> type == array_long_double ) {
		*((long double*) a -> top ) = ((long double*) a -> data) [ index ];
		return a -> top;
	} else {
		array_error_exit ( NULL, unknown_type );
	}
	return NULL;
}

size_t array_size ( array* a )
{
	return a -> c_top;
}

array array_create ( array_data_type type )
{
	size_t effective_size = 0;
	if ( type == array_bool ) {
		effective_size = max_array_size * sizeof(bool);
	} else if ( type == array_int ) {
		effective_size = max_array_size * sizeof(int);
	} else if ( type == array_long ) {
		effective_size = max_array_size * sizeof(long);
	} else if ( type == array_long_long ) {
		effective_size = max_array_size * sizeof(long long);
	} else if ( type == array_char ) {
		effective_size = max_array_size * sizeof(char);
	} else if ( type == array_float ) {
		effective_size = max_array_size * sizeof(float);
	} else if ( type == array_double ) {
		effective_size = max_array_size * sizeof(double);
	} else if ( type == array_long_double ) {
		effective_size = max_array_size * sizeof(long double);
	} else {
		array_error_exit ( NULL, unknown_type );
	}
	array a;
	a.type = type;
	a.size = max_array_size;
	a.data = malloc ( effective_size );
	a.top = malloc ( effective_size / max_array_size );
	a.c_top = 0;
	if ( a.data == NULL || a.top == NULL )
		array_error_exit ( &a, alloc_fail );
	return a;
}

void array_print ( array* a )
{
	printf ( "Array Type : " );
	if ( a -> type == array_bool ) puts ( "bool" );
	else if ( a -> type == array_int ) puts ( "int" );
	else if ( a -> type == array_long ) puts ( "long" );
	else if ( a -> type == array_long_long ) puts ( "long long" );
	else if ( a -> type == array_char ) puts ( "char" );
	else if ( a -> type == array_float ) puts ( "float" );
	else if ( a -> type == array_double ) puts ( "double" );
	else if ( a -> type == array_long_double ) puts ( "long double" );
	else array_error_exit ( NULL, unknown_type );
	printf ( "Array max size : %zd\n", a -> size );
	printf ( "Array Data Address : %p\n", a -> data );
	printf ( "Array top : %p\n", a -> top );
	printf ( "Current Array Size : %zd\n", a -> c_top );
	if ( a -> c_top != 0 ) {
		for ( size_t i = 1 ; i <= a -> c_top ; ++i ) {
			if ( a -> type == array_bool )
				printf ( "%d ", ((bool*) a -> data)[i] );
			else if ( a -> type == array_int )
				printf ( "%d ", ((int*) a -> data)[i] );
			else if ( a -> type == array_long )
				printf ( "%ld ", ((long*) a -> data)[i] );
			else if ( a -> type == array_long_long )
				printf ( "%lld ", ((long long*) a -> data)[i] );
			else if ( a -> type == array_char )
				printf ( "%c ", ((char*) a -> data)[i] );
			else if ( a -> type == array_float )
				printf ( "%f ", ((float*) a -> data)[i] );
			else if ( a -> type == array_double )
				printf ( "%lf ", ((double*) a -> data)[i] );
			else if ( a -> type == array_long_double )
				printf ( "%Lf ", ((long double*) a -> data)[i] );
			else array_error_exit ( NULL, unknown_type );
		}
	}
	puts ( "\n" );
}

int main ()
{
	array a = array_create ( array_long_long );
	for ( int i = 0 ; i < 15 ; ++i ) {
		long long rnd = rand() % 10;
		array_push_back ( &a, &rnd );
	}
	puts ( "\n" );
	for ( int i = 1 ; i < 16 ; ++i ) {
		printf ( "%lld ", *(long long*)array_at ( &a, i ) );
	}
	puts ( "\n" );
	array_print ( &a );
	array_destroy ( &a );

	a = array_create ( array_long_double );
	for ( int i = 0 ; i < 15 ; ++i ) {
		long double rnd = rand() % 100;
		rnd /= 10;
		array_push_back ( &a, &rnd );
	}
	puts ( "\n" );
	for ( int i = 1 ; i < 16 ; ++i ) {
		printf ( "%Lf ", *(long double*)array_at ( &a, i ) );
	}
	puts ( "\n" );
	array_print ( &a );
	array_destroy ( &a );


	return 0;
}

