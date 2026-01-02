#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  size_t size;
  struct chunk *next;
  char free;
};
struct chunk *flist = NULL;

struct chunk *request_space(struct chunk *last, size_t size) {
  struct chunk *tophunk = sbrk(0);
  void *req = sbrk(size + sizeof(struct chunk));
  if ((void *) tophunk != req || req == (void *) -1) {
    printf("Request space failed.\n");
    return NULL;
  }

  if (last) last->next = tophunk;

  tophunk->size = size;
  tophunk->next = NULL;
  tophunk->free = 0;
  return tophunk;
}

struct chunk *find_free_chunk(struct chunk **hunk, size_t size) {
  struct chunk *current = flist;
  while (current && !(current->free && current->size >= size)) {
    *hunk = current;
    current = current->next;
  }
  return current;
}

void *malloc (size_t size) {
  struct chunk *newhunk;
  if (size == 0){
    return NULL;
  }

  if (!flist) {
    newhunk = request_space(NULL, size);
    if (!newhunk) return NULL;
    flist = newhunk;
  } else {
    struct chunk *hunk = flist;
    newhunk = find_free_chunk(&hunk, size);
    if (!newhunk) {
      newhunk = request_space(hunk, size);
      if (!newhunk) return NULL;
    } else {
      newhunk->free = 0;
    }
  }

  return (void *) (newhunk + 1);
}

void free(void *memory) {
  if (!memory) return;
  struct chunk *hunk = (struct chunk *) memory - 1;
  if (hunk->free == 1) {
    printf("Freeing free data -- don't free the free.\n");
    return;
  }
  hunk->free = 1;
  return;
}

void fragstats(void* buffers[], int len) {
}

