#ifndef PHILOSOPHER_HPP
#define PHILOSOPHER_HPP

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <sys/time.h>
#include <thread>
#include <chrono>

typedef std::shared_ptr<std::mutex> mutexPtr;
typedef std::shared_ptr<bool> boolPtr;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::seconds;


enum e_status { TOOK_FORK, EAT, SLEEP, THINK, DIE };

class Philosopher {

public:
  Philosopher() = delete;
  Philosopher(unsigned const &id, unsigned long const &eat,
              unsigned long const &sleep, unsigned long const &die,
              long const &count);
  Philosopher(Philosopher const &src);
  ~Philosopher();

  Philosopher &operator=(Philosopher const &rhs) = delete;
  void setStartTime(long const &startTime) { this->startTime = startTime; };
  void setForks(mutexPtr const &left, mutexPtr const &right) {
    this->leftFork = left;
    this->rightFork = right;
  }
  void setMessageMutex(mutexPtr const &mess) { messageM = mess; };
  void setdeathBool(boolPtr const &bptr) { somebodyDied = bptr; };
  std::mutex &getCheckMutex() { return checkM; }
  long const &getStartTime() const { return startTime; }
  unsigned long const &getTimeAte() const { return timeAte; }
  unsigned long const &getTimeDie() const { return time_to_die; }
  unsigned long const &getTimeSleep() const { return time_to_sleep; }
  unsigned long const &getTimeEat() const { return time_to_eat; }
  unsigned const &getId() const { return id; }
  bool eatCountZero() const { return (eatCount == 0); }
  bool isStarved(long const &time) const {
    return (time >= timeAte + time_to_die && !eatCountZero());
  }
  bool isDead() const { return (status == DIE); }
  bool checkDeath();
  bool checkEnd() { return (eatCountZero() || checkDeath()); }
  void setStatus(e_status const &newStatus) { this->status = newStatus; }
  void printMessage();
  void takeForks();
  void eat();
  void sleep();
  void think();
  void	startThread() { philoThread = new std::thread(&Philosopher::philosophy_routine, this); };
  void	startDeath() {
	  deathThread = new std::thread(&Philosopher::death_routine, this);
	  deathThread->detach();
};
  void	joinThread() { philoThread->join(); }
  void death_routine();
  void philosophy_routine();

private:
  unsigned long time_to_eat;
  unsigned long time_to_sleep;
  unsigned long time_to_die;
  unsigned long timeAte;
  unsigned id;
  long eatCount;
  e_status status;
  long startTime;
  std::mutex checkM;
  mutexPtr leftFork;
  mutexPtr rightFork;
  mutexPtr messageM;
  boolPtr somebodyDied;
  std::thread* philoThread;
  std::thread* deathThread;
};

long get_current_time(long startTime);

#endif /* ***************************************************** PHILOSOPHER_H  \
        */