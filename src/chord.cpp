//============================================================================
// Name        : chord.cpp
// Author      : Dheeraj
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "includes.h"
#include "defs.h"
#include "udp_listen.h"

#define MYPORT "4950"
#define MAX_PENDING 5
#define MAX_LINE 256
#define MAXBUFLEN 100

vector<pthread_t> threads;
vector<int> rets;

int number = 1;

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

void UDP_message(string from_ip, string message){
	cout<<from_ip<<"\t"<<message<<endl;
}
