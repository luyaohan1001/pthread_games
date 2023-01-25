#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SNOWFLAKE "*"
#define SNOW_DENSITY 0.02
#define SNOW_SPEED 100

#define SCROLL_UP 1
#define SCROLL_DOWN -1

/**
 * @brief Generate snowflakes randomly in a row and scroll.
 * @param params Dummy arguments, unused.
 * @return None.
 */
void generate_snowflake(void *params) {
  int max_rows, max_cols;
  int max_flakes_per_row;
  int flake_position;

  /* Get max numbers of rows and columns of current window. */
  getmaxyx(stdscr, max_rows, max_cols);
  (void)max_rows;

  max_flakes_per_row = (int)((double)max_cols * SNOW_DENSITY);

  /* Initialize pseudo number generator. */
  srand(time(NULL));

  while (true) {
    for (int i = 0; i < max_flakes_per_row; ++i) {
      /* Wrap around if flake position is larger than columns. */
      flake_position = rand() % max_cols;
      mvaddstr(0, flake_position, SNOWFLAKE);
    }

    /* Keep cursor from bouncing around. */
    move(0, 0);

    scrl(SCROLL_DOWN);
    scrollok(stdscr, TRUE);

    refresh();

    /* Delay. */
    napms(SNOW_SPEED);
  }
}

/**
 * @brief Main thread.
 * @return 0 on success.
 */
int main() {
  pthread_t snowflake_thread;

  /* Determines the terminal type and initializes all curses data structures. */
  initscr();

  /* Snowflake display thread. */
  pthread_create(&snowflake_thread, NULL, (void *)generate_snowflake, NULL);

  /* Make main thread stop here so the snowflake_thread keeps showing. */
  while (1)
    ;

  /* Restores the terminal after Curses activity */
  endwin();
  return 0;
}