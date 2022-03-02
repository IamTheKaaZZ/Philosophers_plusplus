/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SharedUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:06:12 by bcosters          #+#    #+#             */
/*   Updated: 2022/02/28 09:40:11 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.hpp"
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

long get_current_time(long startTime) {
  auto millisec_since_epoch =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  return millisec_since_epoch - startTime;
}
