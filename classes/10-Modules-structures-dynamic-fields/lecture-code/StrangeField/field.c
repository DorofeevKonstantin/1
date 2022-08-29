#include "field.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void allocate_field(struct field* _field)
{
	_field->cells = (char**)malloc(_field->rows * sizeof(char*));
	for (int i = 0; i < _field->rows; i++)
		_field->cells[i] = (char*)malloc(_field->columns * sizeof(char));
}

void deallocate_field(struct field* _field)
{
	for (int i = 0; i < _field->rows; i++)
		free(_field->cells[i]);
}

void clear_field(struct field* _field)
{
	for (int i = 0; i < _field->rows; i++)
		for (int j = 0; j < _field->columns; j++)
			_field->cells[i][j] = '*';
}

void visualize(struct field* _field)
{
	system("cls");
	for (int i = 0; i < _field->rows; i++)
	{
		for (int j = 0; j < _field->columns; j++)
			printf("%c", _field->cells[i][j]);
		printf("\n");
	}
}

void place_ball(struct field* _field, int y, int x)
{
	if (y < 0 || y >= _field->rows || x < 0 || x >= _field->columns)
		return;
	_field->cells[y][x] = 'B';
}


///////////////////////////////////////////////////////////////////////////////////////////////

struct fields_sequence* generate_fields_sequence(int count, int rows, int columns, int ball_y, int ball_x)
{
	srand((unsigned int)time(0));
	struct fields_sequence* fs = (struct fields_sequence*)malloc(sizeof(struct fields_sequence));
	if (fs)
	{
		fs->count = count;
		fs->fields = (struct field*)malloc(fs->count * sizeof(struct field));
		for (int i = 0; i < fs->count; i++)
		{
			fs->fields[i].rows = rows;
			fs->fields[i].columns = columns;
			allocate_field(&(fs->fields[i]));
			clear_field(&(fs->fields[i]));
			place_ball(&(fs->fields[i]), ball_y, ball_x);

			int add_y = rand() % 3 - 1;
			int add_x = rand() % 3 - 1;
			if (add_y == 0)
				ball_x += add_x;
			else
				ball_y += add_y;
		}
	}
	return fs;
}

void free_fields_sequence(struct fields_sequence* fs)
{
	for (int i = 0; i < fs->count; i++)
		deallocate_field(&(fs->fields[i]));
	free(fs->fields);
	free(fs);
}

void fields_sequence_visualize(struct fields_sequence* fs)
{
	for (int i = 0; i < fs->count; i++)
	{
		visualize(&(fs->fields[i]));
		Sleep(100);
	}
}