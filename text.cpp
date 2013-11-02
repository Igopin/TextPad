/* Text class source file  */

#include <stdio.h>
#include "text.h"

/* Load text out file function
 * ARGUMENTS:
 *  - file name to open an load:
 *      char *file_name;
 * RETURNS:
 *  - maximal string length in file:
 *      int
 **/
int WINTEXT::LoadFile( char *file_name )
{
  int
    max_str_len = 0,
    pos = 0,           /* Position in string buffer */
    str_len,
    num_of_read,       /* Number of readed symbols */
    file_size;
  char *buf;           /* String buffer to adding in list */
  FILE *F;

  if ((F = fopen(file_name, "rb")) == NULL)
  {
    str_buf = NULL;
    return 0;
  }

  fseek(F, 0, SEEK_END);
  file_size = ftell(F);
  fseek(F, 0, SEEK_SET);

  str_buf = new char[file_size];
  num_of_read = fread(str_buf, 1, file_size, F);
  if (num_of_read > file_size)
  {
    free(str_buf);
    return 0;
  }
  fclose(F);

  /* Create strings list */
  while (pos < file_size )
  {
    str_len = pos;
    while (str_buf[pos] != '\n' && pos < file_size)
      pos++;

    str_len = pos - str_len;
    pos -= str_len;

    if (str_len > max_str_len)
      max_str_len = str_len;

    buf = new char [str_len + 1];
    if (buf == NULL)
      return 0;
    for (int j = 0; j < str_len; j++)
      buf[j] = str_buf[pos++];
    buf[str_len] = 0;
    str_list.push_end(buf);
    num_of_str++;
    pos++;
  }
  return max_str_len;
} /* End of 'WINTEXT::LoadFile' function */

/* Draw text function
 * PARAMS:
 *   - ofsset from beginnig string :
 *       int start_str_pos;
 *   - reference to client field:
 *       VEC2 clinet_field;
 * RETURNS:
 *   - None;
 */
void WINTEXT::Draw( HDC &hDC, int start_str_pos, VEC2 &client_f )
{
  int
    i = 0,   /* Simple counter */
    strl;    /* Length of string to draw */
  char *s;   /* String to draw */

  str_list.Start();
  while (str_list.GetEl() != NULL && i < client_f.y)
  {
    s = str_list.GetEl();
    if ((strl = strlen(s)) >= start_str_pos)
      TextOut(hDC, 2, font_size.y * i++, (LPCSTR)(s + start_str_pos), strl - start_str_pos);
    else
      TextOut(hDC, 2, font_size.y * i++, NULL, 0);
    str_list.Next();
  }
  str_list.Start();
} /* End of 'WINTEXT::Draw' function */


/* Move start list pointer to next element operator
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to list:
 *      LIST &
 **/
LIST &WINTEXT::operator++( int )
{
  str_list.SetNewStart(TRUE, 1);
  return str_list;
} /* End of 'WINTEXT::operator++' function */

/* Move start list pointer to previous element operator
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to list:
 *      LIST &
 **/
LIST &WINTEXT::operator--( int )
{
  str_list.SetNewStart(FALSE, 1);
  return str_list;
} /* End of 'WINTEXT::operator--' function */

/* Move start list pointer to next element operator (i - times)
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to list:
 *      LIST &
 **/
void WINTEXT::operator+=( int i )
{
  str_list.SetNewStart(TRUE, i);
} /* End of 'WINTEXT::operator+=' function */

/* Move start list pointer to previous element operator (i - times)
 * ARGUMENTS:
 *  - None.
 * RETURNS:
 *  - reference to list:
 *      LIST &
 **/
void WINTEXT::operator-=( int i )
{
  str_list.SetNewStart(FALSE, i);
} /* End of 'WINTEXT::operator-=' operator */

/* END OF 'text.cpp' FILE */
