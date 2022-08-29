#ifndef _FIELD
#define _FIELD

struct field
{
	int rows;
	int columns;
	char** cells;
};

void allocate_field(struct field*);
void deallocate_field(struct field*);
void clear_field(struct field*);
void visualize(struct field*);
void place_ball(struct field*, int, int);

struct fields_sequence
{
	int count;
	struct field* fields;
};

struct fields_sequence* generate_fields_sequence(int count, int rows, int columns, int ball_y, int ball_x);
void fields_sequence_visualize(struct fields_sequence* fs);
void free_fields_sequence(struct fields_sequence*);

#endif