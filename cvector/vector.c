#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef enum {
	vector_bool,
	vector_int,
	vector_unsigned_int,
	vector_long,
	vector_unsigned_long,
	vector_long_long,
	vector_unsigned_long_long,
	vector_char,
	vector_unsigned_char,
	vector_float,
	vector_double,
	vector_long_double
} vector_data_type ;

typedef struct vector {
	vector_data_type type;
	void* raw_data;
	void* rtn_val;
	size_t current_size;
	size_t current_start;
	size_t current_end;
} vector ;

vector vector_create ( vector_data_type _type )
{
	vector v = {
		.type = _type,
		.raw_data = NULL,
		.rtn_val = NULL,
		.current_size = 0,
		.current_start = 0,
		.current_end = 0
	};
	return v;
}

void* vector_at ( vector* _vec, size_t _index )
{
	assert ( _index < _vec -> current_end && _index >= _vec -> current_start );
	if ( _vec -> type == vector_bool ) {
		return &((bool*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_int ) {
		return &((int*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_unsigned_int ) {
		return &((unsigned int*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_long ) {
		return &((long*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_unsigned_long ) {
		return &((unsigned long*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_long_long ) {
		return &((long long*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_unsigned_long_long ) {
		return &((unsigned long long*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_char ) {
		return &((char*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_unsigned_char ) {
		return &((unsigned char*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_float ) {
		return &((float*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_double ) {
		return &((double*)_vec -> raw_data)[_index];
	} else if ( _vec -> type == vector_long_double ) {
		return &((long double*)_vec -> raw_data)[_index];
	}
	// execution will never come here untill (_vec == NULL);
	return NULL;
}

void vector_push_back ( vector* _vec, void* _value )
{
//	switch ( _vec -> type ) {
//		case vector_bool:
//			++ _vec -> current_size;
//			break;
//		case vector_int:
//			break;
//	}
	if ( _vec -> type == vector_bool ) {
		++ _vec -> current_size;
		_vec -> raw_data = (bool*) realloc
			( _vec -> raw_data, sizeof ( bool ) * _vec -> current_size );
		((bool*)_vec -> raw_data)[_vec -> current_end] = *(bool*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_int ) {
		++ _vec -> current_size;
		_vec -> raw_data = (int*) realloc
			( _vec -> raw_data, sizeof ( int ) * _vec -> current_size );
		((int*)_vec -> raw_data)[_vec -> current_end] = *(int*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_unsigned_int ) {
		++ _vec -> current_size;
		_vec -> raw_data = (unsigned int*) realloc
			( _vec -> raw_data, sizeof ( unsigned int ) * _vec -> current_size );
		((unsigned int*)_vec -> raw_data)[_vec -> current_end] = *(unsigned int*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_long ) {
		++ _vec -> current_size;
		_vec -> raw_data = (long*) realloc
			( _vec -> raw_data, sizeof ( long ) * _vec -> current_size );
		((long*)_vec -> raw_data)[_vec -> current_end] = *(long*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_unsigned_long ) {
		++ _vec -> current_size;
		_vec -> raw_data = (unsigned long*) realloc
			( _vec -> raw_data, sizeof ( unsigned long ) * _vec -> current_size );
		((unsigned long*)_vec -> raw_data)[_vec -> current_end] = *(unsigned long*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_long_long ) {
		++ _vec -> current_size;
		_vec -> raw_data = (long long*) realloc
			( _vec -> raw_data, sizeof ( long long ) * _vec -> current_size );
		((long long*)_vec -> raw_data)[_vec -> current_end] = *(long long*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_unsigned_long_long ) {
		++ _vec -> current_size;
		_vec -> raw_data = (unsigned long long*) realloc
			( _vec -> raw_data, sizeof ( unsigned long long ) * _vec -> current_size );
		((unsigned long long*)_vec -> raw_data)[_vec -> current_end] = *(unsigned long long*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_char ) {
		++ _vec -> current_size;
		_vec -> raw_data = (char*) realloc
			( _vec -> raw_data, sizeof ( char ) * _vec -> current_size );
		((char*)_vec -> raw_data)[_vec -> current_end] = *(char*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_unsigned_char ) {
		++ _vec -> current_size;
		_vec -> raw_data = (unsigned char*) realloc
			( _vec -> raw_data, sizeof ( unsigned char ) * _vec -> current_size );
		((unsigned char*)_vec -> raw_data)[_vec -> current_end] = *(unsigned char*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_float ) {
		++ _vec -> current_size;
		_vec -> raw_data = (float*) realloc
			( _vec -> raw_data, sizeof ( float ) * _vec -> current_size );
		((float*)_vec -> raw_data)[_vec -> current_end] = *(float*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_double ) {
		++ _vec -> current_size;
		_vec -> raw_data = (double*) realloc
			( _vec -> raw_data, sizeof ( double ) * _vec -> current_size );
		((double*)_vec -> raw_data)[_vec -> current_end] = *(double*) _value;
		++ _vec -> current_end;
	} else if ( _vec -> type == vector_long_double ) {
		++ _vec -> current_size;
		_vec -> raw_data = (long double*) realloc
			( _vec -> raw_data, sizeof ( long double ) * _vec -> current_size );
		((long double*)_vec -> raw_data)[_vec -> current_end] = *(long double*) _value;
		++ _vec -> current_end;
	}
}

void vector_destroy ( vector* _vec )
{
	if ( _vec == NULL ) return;
	if ( _vec -> raw_data != NULL )
		free ( _vec -> raw_data );
	if ( _vec -> rtn_val != NULL )
		free ( _vec -> rtn_val );
	_vec -> current_size = 0;
	_vec -> current_start = 0;
	_vec -> current_end = 0;
}

int main ()
{
	vector vec = vector_create ( vector_long_double );

	srand ( 6 );
	for ( size_t i = 0 ; i < 7 ; ++i ) {
		long double val = rand() % 1000;
		val /= 10;
		printf ( "%.2Lf ", val );
		vector_push_back ( &vec, &val );
		val = 0;
		*(long double*) vector_at ( &vec, i ) = val;
	}
	puts ( "" );

	for ( size_t i = vec.current_start ; i < vec.current_end ; ++i ) {
		fprintf ( stderr, "%.2Lf ", *(long double*) vector_at ( &vec, i ) );
		//printf ( "%.2Lf ", ((long double*)vec.raw_data)[i] );
	}
	puts ( "" );

	vector_destroy ( &vec );

	return 0;
}

