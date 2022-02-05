#include <stdio.h>
#include <stdlib.h>

#include <sm/sm.h>


void
svector_debug_print(SVector *v)
{
	SVectorEl *el = v->zero_el ;
	while(el->next){
		el=el->next ;
		printf("%d %x\n", el->idx, (int)el->val);
	}
}

void
smatrix_debug_print(SMatrix *m, int w, int h)
{
	int i, j, isnil;
	void *vd;

	for(i=0 ; i<h ; ++i){
		for(j=0 ; j<w ; ++j){
			vd = smatrix_get(m, &isnil, j, i);
			if(!isnil)
				printf("%x ", (int)vd);
			else
				printf("nil ");
		}
		puts("");
	}
}

int
main(int argc, char *argv[])
{
	int isnil;
	SMatrix *m = smatrix_init(0) ;
	void *arr[] = {
		3, 23, 1, 3, 5,
		32, 10, 23, 53, 10,
		4842, 231, 23, 2321, 15
	} ;
	smatrix_set_array(m, arr, 5, 3);
	smatrix_set(m, 6, 9, 2222);
	smatrix_set(m, 7, 10, 3333);
	smatrix_set(m, 8, 11, 4444);
	smatrix_debug_print(m, 10, 15);

	return 0 ;
}

