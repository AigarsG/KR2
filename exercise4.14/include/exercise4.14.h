#ifndef EXERCISE4_14_HEADER
#define EXERCISE4_14_HEADER

#define MYBASE "my base"

#define swap(t, x, y) 			\
do {					\
	t tmp = x;			\
	x = y;				\
	y = tmp;			\
} while (0)				

#define concattok(front, back) front ## back

#endif
