/* Template list class source file  */

#include "list.h"


/* Get list  element function
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - pointer to list element (string):
 *      char *
 **/
char * LIST::GetEl( void )
{
  if (cur != NULL)
    return cur->data;
  else
    return NULL;
} /* End of 'LIST::GetEl' function */

/* Get next list position function
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to next list position:
 *      LIST &
 **/
LIST & LIST::Next( void )
{
  if (cur != NULL)
    cur = cur->next;
  return *this;
} /* End of 'LIST::Next' function */

/* Get previous list position function
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to previous list position:
 *      LIST &
 **/
LIST & LIST::Prev( void )
{
  if (cur != NULL)
    cur = cur->prev;
  return *this;
} /* End of 'LIST::Prev' function */


/* Add new list element to end function
 * ARGUMENTS:
 *  - new list element:
 *       char *_new;
 * RETURNS:
 *  - None.
 **/
void LIST::push_end( char *_new )
{
  ELEMENT *el = last;

  last = new ELEMENT(_new, NULL, last);
  if (el != NULL)
    el->next = last;

  if (first == NULL)
    first = last;

  cur = start = first;

} /* End of 'LIST::push_end' function */

/* Add new list element to begin function
 * ARGUMENTS:
 *  - new list element:
 *       char *_new;
 * RETURNS:
 *  - None.
 **/
void LIST::push_start( char *_new )
{
  ELEMENT *el = first;

  first = new ELEMENT(_new, first, NULL);
  if (el != NULL)
    el->prev = first;

  if (last == NULL)
    last = first;

  cur = start = first;
} /* End of 'LIST::push_start' function */

/* Set list pointer in new position
 * ARGUMENTS:
 *  - direction if TRUE - go to next element(s), FALSE - go to previous element(s):
 *       bool dir;
 *  - num steps to go:
 *       int num_steps;
 * RETURNS:
 *  - None.
 **/
void LIST::SetNewStart( bool dir, int num_steps )
{
  if (dir)
  {
    for (int i = 0; (i < num_steps) && (start != NULL); i++)
      start = start->next;
  }
  else
  {
    for (int i = 0; (i < num_steps) && (start != NULL); i++)
      start = start->prev;
  }
} /* End of 'LIST::SetNewStart' function */

/* Free list function */
void LIST::Free( void )
{
  ELEMENT *next = NULL;

  while (first != NULL)
  {
    next = first->next;
    delete first;
    first = next;
  }
  if (next != NULL)
    delete next;
  cur = NULL;
  start = NULL;
  first = NULL;
  last = NULL;
} /* End of 'LIST::Free' function */

/* END OF 'list.cpp' FILE */
