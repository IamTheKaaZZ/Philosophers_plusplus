/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:40:19 by bcosters          #+#    #+#             */
/*   Updated: 2022/02/25 17:27:59 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Table.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <iomanip>
#include <sys/time.h>

int	main(int argc, char** argv) {
	if (argc != 6) {
		if (argc < 5) {
			std::cerr << "Not enough arguments.\n"; return 1;
		}
		else if (argc > 6) {
			std::cerr << "Too many arguments.\n"; return 1;
		}
	}
	Table	t(argc, argv);
	t.startThreads();
	return 0;
}