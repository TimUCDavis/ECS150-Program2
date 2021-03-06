//
// Created by Yulin Yan on 4/24/18.
//
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
        return 1;

    return 0;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *ptr = NULL;

    /* Initialize the queue and enqueue items */
    q = queue_create();

    for (int i = 0; i < 10; i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    assert(data[0] == 2);

    /* Find and get the item which is equal to value '5' */
    queue_iterate(q, find_item, (void*)5, (void**)&ptr);
    assert(ptr != NULL);
    assert(ptr == &data[3]);
    assert(*ptr == 5);

    assert(queue_iterate(NULL, NULL, NULL, NULL) == -1);

    assert(queue_destroy(NULL) == -1);
    assert(queue_enqueue(NULL, NULL) == -1);


}

