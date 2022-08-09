#ifndef _FIELD
#define _FIELD

struct field
{
	int rows;
	int columns;
	char** cells;
};

struct fields_sequence
{
	int count;
	struct field* fields;
};

struct fields_sequence* generate_fields_sequence(int count, int rows, int columns, int ball_y, int ball_x);

void fields_sequence_visualize(struct fields_sequence* fs);

#endif