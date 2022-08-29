#include <stdio.h>

#include "field.h"

int main()
{
	struct fields_sequence* fs = generate_fields_sequence(10, 5, 10, 2, 2); // 10 fields, 5x10 size, 2,2 == position of ball
	fields_sequence_visualize(fs);

	return 0;
}