#ifndef TABLE_HPP
#define TABLE_HPP

#include "Philosopher.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class Table {

public:
  Table() = delete;
  Table(int argc, char **argv);
  Table(Table const &src) = delete;
  ~Table();

  Table &operator=(Table const &rhs) = delete;
  void	startThreads();

private:
  long nPhilos;
  long time_to_eat;
  long time_to_sleep;
  long time_to_die;
  long eatCount;
  long startTime;
  std::vector<Philosopher*> philos;
  std::vector<mutexPtr> forks;
  mutexPtr messageM;
  boolPtr somebodyDied;
};

#endif /* *********************************************************** TABLE_H  \
        */