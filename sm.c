#include <sm/sm.h>
#include <stdlib.h>

SMatrix *
smatrix_init(void *defval)
{
	SMatrix *m = malloc(sizeof(*m)) ;
	m->zero_v = svector_init(defval) ;
	m->default_value = defval ;
	return m ;
}

void
smatrix_set(SMatrix *m, int idx1, int idx2, void *val)
{
	int isnil;
	SVector *v;

	svector_get(m->zero_v, &isnil, idx1);
	if(isnil)
		svector_set(m->zero_v, idx1, svector_init(m->default_value));

	v = svector_get(m->zero_v, 0, idx1) ;
	svector_set(v, idx2, val);
}

void
smatrix_set_array(SMatrix *m, void **arr, int w, int h)
{
	int i, j;
	for(i=0 ; i<h ; ++i){
		for(j=0 ; j<w ; ++j){
			smatrix_set(m, j, i, arr[i*w + j]);
		}
	}
}

void *
smatrix_get(SMatrix *m, int *isnil, int idx1, int idx2)
{
	void *ret;
	SVector *v = svector_get(m->zero_v, isnil, idx1) ;
	if(isnil && *isnil){
		return v ;
	}

	ret = svector_get(v, isnil, idx2) ;
	return ret ;
}

SVector *
svector_init(void *defval)
{
	SVector *v = malloc(sizeof(*v)) ;
	v->zero_el = malloc(sizeof(*(v->zero_el))) ;
	v->default_value = defval ;
	v->zero_el->idx = -9999999 ; /* Must be the lowest index. */
	v->zero_el->val = 0 ;
	v->zero_el->next = 0 ;
	return v ;
}

void
svector_set(SVector *v, int idx, void *val)
{
	SVectorEl *bel, *el = v->zero_el ;
	while(el->next && (idx > el->next->idx))
		el = el->next ;

	if(idx == el->idx){
		/* Nothing. */
	}else if(el->next){
		bel = el->next ;
		el->next = malloc(sizeof(*(el->next))) ;	
		el->next->next = bel ;
		el = el->next ;
	}else{
		el->next = malloc(sizeof(*(el->next))) ;
		el = el->next ;
		el->next = 0 ;
	}

	el->idx = idx ;
	el->val = val ;
}

static SVectorEl *
svector_get_el(SVector *v, int *isnil, int idx)
{
	SVectorEl *el = v->zero_el ;
	while(el->next && (idx > el->next->idx))
		el = el->next;

	if(!el->next){
		goto def_exit;
	} else if(idx == el->next->idx){
		if(isnil) *isnil = 0 ;
		return el->next ;
	}

def_exit:
	if(isnil) *isnil = 1 ;
	return 0;
}

void *
svector_get(SVector *v, int *isnil, int idx)
{
	SVectorEl *el = svector_get_el(v, isnil, idx) ;
	if(el)
		return el->val ;
	return v->default_value ;
}


