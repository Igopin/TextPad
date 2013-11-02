/* Main list class header file */

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include "defines.h"

/* List class */
class LIST
{
private:
  class ELEMENT
  {
  public:
    char *data;
    ELEMENT *next;
    ELEMENT *prev;

    /* Constructors */
    ELEMENT( void ) : data(NULL), next(NULL), prev(NULL){};   // default
    ELEMENT(char *_data) : data(_data){};                   // data constructor
    ELEMENT(char *_data, ELEMENT *_next, ELEMENT *_prev) :  // full
      data(_data), next(_next), prev(_prev){};

    ~ELEMENT()
    {
      delete data;
    }
  };

  ELEMENT *first;
  ELEMENT *last;
  ELEMENT *cur;

public:
  ELEMENT *start;

  /* Main list constructor */
  LIST( void ) : first(NULL), last(NULL), cur(NULL){};

  /* Set  */
  void Start(){cur = start;};

  /* Set new start function */
  void SetNewStart( bool dir, int num_steps );

  /* Get element function */
  char * GetEl( void );

  /* Get next element function */
  LIST & Next( void );

  /* Get prev element function */
  LIST & Prev( void );

  /* Add new list element */
  void push_end( char *_new );

  /* Add new list element */
  void push_start( char *_new );

  /* Free list function */
  void Free( void );
};

#endif /* _LIST_H_ */

/* END OF 'list.h' FILE */
