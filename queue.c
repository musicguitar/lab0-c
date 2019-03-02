/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->qsize = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    while (q_remove_head(q, NULL, 0))
        ;

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;

    if (q->tail == NULL)
        q->tail = newh;

    q->qsize++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;
    if (q == NULL)
        return false;

    newt = malloc(sizeof(queue_t));
    if (!newt)
        return false;

    newt->value = malloc(strlen(s) + 1);
    if (!newt->value) {
        free(newt);
        return false;
    }

    strcpy(newt->value, s);
    newt->next = NULL;

    if (q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;

    if (q->head == NULL)
        q->head = newt;

    q->qsize++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *remove_head;
    if (q == NULL || q->head == NULL)
        return false;

    remove_head = q->head;


    if (sp != NULL && bufsize > 0) {
        strncpy(sp, remove_head->value, bufsize);
        sp[bufsize - 1] = '\0';
    }

    free(remove_head->value);
    q->head = remove_head->next;
    free(remove_head);
    q->qsize--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;

    return q->qsize;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *pre, *cur, *next;
    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;

    pre = q->head;
    cur = pre->next;

    while (cur != NULL) {
        next = cur->next;

        cur->next = pre;
        if (pre == q->head) {
            pre->next = NULL;
            q->tail = pre;
        }

        pre = cur;
        cur = next;
    }

    q->head = pre;
}
