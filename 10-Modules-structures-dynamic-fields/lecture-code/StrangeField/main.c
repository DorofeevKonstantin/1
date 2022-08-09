#include <stdio.h>

#include "field.h"

int main()
{
	// strange program for ball movement on fields sequence
	struct fields_sequence* fs = generate_fields_sequence(100, 20, 80, 10, 40);
	fields_sequence_visualize(fs);
	free_fields_sequence(fs);
	return 0;
}