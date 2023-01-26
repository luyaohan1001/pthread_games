#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdlib.h>

/* Synchronization primitives. */
static pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t condition_variable = PTHREAD_COND_INITIALIZER;

static volatile bool leader_walked = false;

#define LEADER_WALK std::cout << "Leader has walked." << std::endl;

#define FOLLOWER_WALK std::cout << "Follower has walked." << std::endl;

/**
 * @brief Leader thread routine.
 * @param params Unused, dummy variable.
 * @return Unused.
 * @note The reason to use conditional variable:
 *     If not using such block-signal mechanism that the waiting thread has to
 * busy wait.
 */
void *leader_routine(void *params) {
  pthread_mutex_lock(&condition_mutex);
  LEADER_WALK;
  leader_walked = true;
  /* Tries to signal one of the followers to wake up. */
  pthread_cond_signal(&condition_variable);
  pthread_mutex_unlock(&condition_mutex);
  return NULL;
}

/**
 * @brief Leader thread routine.
 * @param params Unused, dummy variable.
 * @return Unused.
 * @note The reason to use conditional variable:
 *     If not using such block-signal mechanism that the waiting thread has to
 * busy wait.
 */
void *follower_routine(void *params) {
  pthread_mutex_lock(&condition_mutex);
  if (leader_walked == false) {
    /* If leader has not walked, then it will wait for the condtion_variable and
     * unlock mutex here. */
    pthread_cond_wait(&condition_variable, &condition_mutex);
  }
  FOLLOWER_WALK;
  pthread_mutex_unlock(&condition_mutex);
  return NULL;
}

int main() {
  pthread_t leader_thread, follower_thread;

  pthread_mutex_init(&condition_mutex, NULL);
  pthread_cond_init(&condition_variable, NULL);

  pthread_create(&leader_thread, NULL, leader_routine, NULL);
  pthread_create(&follower_thread, NULL, follower_routine, NULL);

  /* Make main thread wait for the leader and follower routine finish execution
   * before exit. */
  pthread_join(leader_thread, NULL);
  pthread_join(follower_thread, NULL);

  return 0;
}