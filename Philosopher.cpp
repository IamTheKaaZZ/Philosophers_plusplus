#include "Philosopher.hpp"
#include <mutex>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Philosopher::Philosopher(unsigned const &id, unsigned long const &eat,
                         unsigned long const &sleep, unsigned long const &die,
                         long const &count)
    : id(id), time_to_eat(eat), time_to_sleep(sleep), time_to_die(die),
      eatCount(count), timeAte(0), status(THINK), startTime(0), checkM() {}

Philosopher::Philosopher(const Philosopher &src) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Philosopher::~Philosopher() {
  if (philoThread) {
    delete philoThread;
  }
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

bool Philosopher::checkDeath() {
  long curr_time = get_current_time(getStartTime());
  //   std::cout << "checking at " << curr_time << '\n';
  if (isStarved(curr_time)) {
    setStatus(DIE);
    printMessage();
    return true;
  }
  return false;
}

void Philosopher::printMessage() {
  static std::string action_str[5] = {
      "\033[32mhas taken a fork.\033[0m", "\033[36mis eating.\033[0m",
      "\033[34;1mis sleeping.\033[0m", "\033[35mis thinking.\033[0m",
      "\033[31;1mdied.\033[0m"};
  std::lock_guard<std::mutex> lockM(*this->messageM);
  if (*this->somebodyDied)
    setStatus(DIE);
  else {
    std::cout << '[' << get_current_time(startTime) << " ms] ";
    std::cout << "Philosopher " << getId() << ' ' << action_str[status] << '\n';
  }
  if (this->isDead() && !*this->somebodyDied) {
    *this->somebodyDied = true;
  }
}

void Philosopher::takeForks() {
  if (leftFork == rightFork) {
    setStatus(TOOK_FORK);
    printMessage();
    while (true) {
      if (checkDeath())
        return;
    }
  }
  while (true) {
    if (leftFork->try_lock()) {
      if (rightFork->try_lock()) {
        setStatus(TOOK_FORK);
        printMessage();
        printMessage();
        return;
      } else {
        leftFork->unlock();
        continue;
      }
    } else {
      continue;
    }
  }
}

void Philosopher::eat() {
	std::lock_guard<std::mutex> lockC(checkM);
  setStatus(EAT);
  printMessage();
  timeAte = get_current_time(startTime);
  eatCount--;
  std::this_thread::sleep_for(std::chrono::milliseconds(time_to_eat));
  leftFork->unlock();
  rightFork->unlock();
}

void Philosopher::sleep() {
  setStatus(SLEEP);
  printMessage();
  std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
}

void Philosopher::think() {
  setStatus(THINK);
  printMessage();
}

void Philosopher::death_routine() {
  bool end = false;
  while (!end) {
    getCheckMutex().lock();
    if (checkEnd())
      end = true;
    getCheckMutex().unlock();
    std::this_thread::sleep_for(milliseconds(1));
  }
}

void Philosopher::philosophy_routine() {
  while (!eatCountZero() && !isDead()) {
    takeForks();
    eat();
    sleep();
    think();
  }
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */