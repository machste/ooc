/**
 * @file    container.ifc.h
 *
 * @brief   Container Interface
 */
#ifndef _CONTAINER_IFC_H_
#define _CONTAINER_IFC_H_

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Container Interface
 */
extern const class *Container;

/**
 * @brief Container Methods
 */
typedef size_t (*len_cb)(void *self);
typedef void *(*get_at_cb)(void *self, int index);
typedef void *(*set_at_cb)(void *self, int index, void *item);
typedef void (*clear_cb)(void *self);

/**
 * @brief Method Table of Container
 */
typedef struct container_mt {
    len_cb len;
    get_at_cb get_at;
    set_at_cb set_at;
    clear_cb clear;
} container_mt;

/**
 * @brief Fix up an Index
 *
 * This static method fixes up an 'index' for a 'Container' with a given
 * 'size'. It allows having negative indexes to reference items in the
 * container (e.g. the last item by an index of -1).
 *
 * @return The fixed up index or -1 to indicate an error
 */
int Container_fixup_index(size_t size, int index);

/**
 * @brief Length of the Container
 *
 * @return The length of the container, an integer >= 0
 */
size_t len(void *self);

/**
 * @brief Get the Item at a Given Index
 *
 * @return Pointer to the item otherwise NULL
 */
void *get_at(void *self, int index);

/**
 * @brief Set the Item at a Given Index
 *
 * @return Pointer of the set item otherwise NULL
 */
void *set_at(void *self, int index, void *item);

/**
 * @brief Clear All Items from the Container
 */
void clear(void *self);

#ifdef __cplusplus
}
#endif

#endif /* _CONTAINER_IFC_H_ */
