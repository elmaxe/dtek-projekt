/* loop.h

   Written 2018-12-06 by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

void init();
void loop();
void enable_interrupt();
void quicksleep(int cyc);

extern int seed;
