#include "Table.hpp"
#include "Philosopher.hpp"
#include <memory>
#include <string>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Table::Table(int argc, char **argv) :
	nPhilos(std::stol(argv[1])),
	time_to_die(std::stol(argv[2])),
	time_to_eat(std::stol(argv[3])),
	time_to_sleep(std::stol(argv[4])),
	messageM(std::make_shared<std::mutex>()),
	somebodyDied(std::make_shared<bool>())
{
	if (nPhilos < 1 || nPhilos > 200)
		throw ("Too little or too many Philosophers.\n");
	if (time_to_die <= 0)
		throw ("(Death time < 0) No immortality.\n");
	if (time_to_eat <= 0)
		throw ("(Eat time < 0) No time travelling.\n");
	if (time_to_sleep <= 0)
		throw ("(Sleep time < 0) Philosopher != student.\n");
	if (argc == 6)
	{
		eatCount = std::stol(argv[5]);
		if (eatCount <= 0)
			throw ("(Must eat < 0) (┛ಠ_ಠ)┛彡┻━┻ No spaghetti.\n");
	}
	else
		eatCount = -1;
	//Create the forks
	for (int i = 0; i < nPhilos; i++) {
		auto mPtr = std::make_shared<std::mutex>();
		forks.push_back(mPtr);
	}
	for (int i = 0; i < nPhilos; i++) {
		Philosopher* newP = new Philosopher(i, time_to_eat, time_to_sleep, time_to_die, eatCount);
		newP->setMessageMutex(messageM);
		newP->setdeathBool(somebodyDied);
		if (i == 0) {
			newP->setForks(forks.back(), forks[i]);
		}
		else newP->setForks(forks[i - 1], forks[i]);
		philos.push_back(newP);
	}
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Table::~Table()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/



/*
** --------------------------------- METHODS ----------------------------------
*/

void		Table::startThreads() {
	startTime = get_current_time(0);
	for (Philosopher* p : philos) {
		p->setStartTime(startTime);
		p->startThread();
		p->startDeath();
	}
	for (Philosopher* p : philos) {
		p->joinThread();
	}
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */