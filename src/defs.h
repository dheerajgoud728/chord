/*
 * defs.h
 *
 *  Created on: 12-Feb-2011
 *      Author: dheeraj
 */

#ifndef DEFS_H_
#define DEFS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>

using namespace std;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

string char_to_str(char * chr){
	stringstream ss;
	string ret;
	ss<<chr;
	ss>>ret;
	return ret;
}

#endif /* DEFS_H_ */
