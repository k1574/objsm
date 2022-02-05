#ifndef _SM_H
#define _SM_H

/* Sparse vector and matrix implementation. */

struct SMatrice
{
	struct SVector *zero_v;
	void *default_value ;
};

struct SVector
{
	struct SVectorEl *zero_el;
	void *default_value;
};

struct SVectorEl {
	int idx;
	void *val;
	struct SVectorEl *next;
};

typedef struct SMatrice SMatrix;
typedef struct SVector SVector;
typedef struct SVectorEl SVectorEl;

SVector *svector_init(void *defval);
void svector_set(SVector *v, int idx, void *val);
void *svector_get(SVector *v, int *isnil, int idx);

SMatrix *smatrix_init(void *defval);
void smatrix_set(SMatrix *v, int idx1, int idx2, void *val);
void *smatrix_get(SMatrix *v, int *isnil, int idx1, int idx2);
void smatrix_set_array(SMatrix *m, void **arr, int w, int h);


#endif
