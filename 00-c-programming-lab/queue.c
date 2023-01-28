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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    // return q directly cuz q is NULL here.
    if (!q)
    {
      return q;
    }

    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if(!q)
      return;
      
    /* How about freeing the list elements and the strings? */
    list_ele_t *process_ptr = q->head;
    list_ele_t *nxt = NULL;
    while (process_ptr)
    {
      // free the string
      free(process_ptr->value);
      nxt = process_ptr->next;
      // free the node 
      free(process_ptr);
      // iterate
      process_ptr = nxt;
    }

    /* Free queue structure */
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
    // q is NULL
    if(!q)
      return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if(!newh) 
      return false;
    char *news = malloc(strlen(s)+1);
    if (!news)
    {
      free(newh);
      return false;
    }
    strcpy(news,s);
    newh->next =NULL;
    newh->value = news;

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->length++;

    if (!q->tail)
    {
      q->tail = q->head;
    }
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
    if (!q)
    {
      return false;
    }

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if(!newh)
      return false;

    char *news = malloc(strlen(s)+1);
    if(!news)
    {
      free(newh);
      return false;
    }
    strcpy(news,s);
    newh->next = NULL;
    newh->value = news;

    if ( q->length == 0 )
    {
      q->tail = q->head = newh;
      q->length++;
      return true;
    }
    
    q->tail->next = newh;
    q->tail = newh;
    q->length++;

    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
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
    if(!q || !q->head)
      return false;
    if (sp && q->head->value)
    {
      // strnpy 不会自动加上终止符terminator 需要手动加
      // strnpy won't add terminator at the end of string automatically.
      strncpy(sp,q->head->value,bufsize-1);
      sp[bufsize-1] = '\0';
    }
    list_ele_t *tmp = q->head;
    if(tmp->value)
      free(tmp->value);

    q->head = tmp->next;
    free(tmp);
    /* You need to fix up this code. */
    q->length--;
    if(q->length == 0)
      q->tail = NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{ 
    if(!q)
      return 0;
    
    return q->length;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */

// 递归达不到性能要求
// void node_reverse(list_ele_t *now)
// {
//   if(!now->next)
//     return;
//   node_reverse(now->next);
  
//   now->next->next = now;

//   return;
// }
void q_reverse(queue_t *q)
{
  if(!q || !q->head)
    return;
  
  list_ele_t *now = q->head;
  list_ele_t *prev = NULL;
  list_ele_t *tmp = NULL;
  // 使用递推才行
  while (now!=NULL)
  {
    tmp = now->next;
    now->next = prev;
    prev = now;
    now = tmp;
  }
  
  // node_reverse(q->head);
  tmp = q->head;
  q->head = q->tail;
  q->tail = tmp;
    /* You need to write the code for this function */
}

