//============================================================================
// Name        : chord.cpp
// Author      : Dheeraj
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "includes.h"
#include "defs.h"

#define MYPORT "4950"
#define MAX_PENDING 5
#define MAX_LINE 256
#define MAXBUFLEN 100

vector<pthread_t> threads;
vector<int> rets;

int number = 1;

void* listen(void * dummy);
void call_listen();
void UDP_message(string from_ip, string message);
/*void f_1();
void f_2();
void f_3();*/

int main(int argc, char ** argv)
{
   string inp;
   call_listen();
   char t[10] = "hello!";
   cout<<char_to_str(t);
   while(1){
	   cin>>inp;
	   /*int ret;
	   ret = pthread_create(&tmp_t, NULL, (void*)&f_1);*/
   }
   return 0;
}

void* listen(void* dummy){
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		goto end;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		close(sockfd);
		exit(1);
	}

	freeaddrinfo(servinfo);

	printf("listener: waiting to recvfrom...\n");

	addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		close(sockfd);
		exit(1);
	}

	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
	printf("listener: packet is %d bytes long\n", numbytes);
	buf[numbytes] = '\0';
	printf("listener: packet contains \"%s\"\n", buf);
	cout<<s;
	cout<<"\t"<<number<<endl;
end:
	close(sockfd);
    call_listen();
    UDP_message(char_to_str(s), char_to_str(buf));
}

void call_listen(){
	   pthread_t l_thread;
	   int l_ret;
	   int dummy = 0;
	   l_ret = pthread_create(&l_thread, NULL, listen, (void *)dummy);
	   number++;
}

void UDP_message(string from_ip, string message){
	cout<<from_ip<<"\t"<<message<<endl;
}
