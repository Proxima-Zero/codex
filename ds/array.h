#ifndef CODEX_ARRAY_H_
#define CODEX_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "codex/mem/allocator.h"
#include "codex/encoding/serializer.h"


typedef struct Array Array;

typedef void (*ArrayItemReleaseCb) (void **item_ptr);

// IMPORTANT NOTE: it is assumed that same allocator are used for elements
extern const ArrayItemReleaseCb JUST_FREE_IT;

struct Array {
	Allocator *a;
	uint8_t *data;
	size_t len;
	size_t cap;
	size_t elem_size;
	// just set if needed. defaults (NULL) is no item release at all
	ArrayItemReleaseCb item_release;

	// add value to array. pval is an address of value to be copied to the array
	void  (*add)     (struct Array *self, void *pval);
	void* (*get)     (struct Array *self, size_t i);
	// sets value of array. value on pval address will be copied
	void  (*set)     (struct Array *self, size_t i, void *pval);
	// fast remove without preserving order - element is just replaced by last one
	void  (*fremove) (struct Array *self, size_t i);

	bool  (*equals)  (struct Array *self, struct Array *other);

	void  (*sort)    (struct Array *self, int (*compar) (const void*, const void*));

	void  (*release) (struct Array **pself);

	Serializer* (*form_serializer) (Allocator *a, Serializer *item_serializer);
};

struct _ArrayStatic {
  Array prototype;

  Array* (*form) (Allocator *a, size_t elem_size);
};

extern const struct _ArrayStatic ARRAY;

#endif
