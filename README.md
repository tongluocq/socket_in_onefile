# socket_in_onefile

1. compile this single into two exe separately.

//gcc   -o golclient  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c &&  gcc   -o golserver  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c 


/*
how to use the two programm in one file socket communication toolbox:

run server in one terminal, it will wait client sending msg


Tongs-MacBook-Pro:Downloads tongluo$ gcc   -o golclient  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c &&  gcc   -o golserver  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c 
Tongs-MacBook-Pro:Downloads tongluo$ ./golserver
./golserver
 I am listening.
start accept
4
>Hello:  (from Client). ss
>server's Hello message sent
>Hello:  (from Client). ss
>server's Hello message sent
>Hello:  (from Client). ss
>server's Hello message sent
>Hello:  (from Client). saa
>server's Hello message sent
>Hello:  (from Client). sdaddd
>server's Hello message sent
>Hello:  (from Client). q1212d
>server's Hello message sent
>Hello:  (from Client). q1221d
>server's Hello message sent
>Hello:  (from Client). as121d
>server's Hello message sent
>Hello:  (from Client). aa121d
>server's Hello message sent
>Hello:  (from Client). ssss1d
>server's Hello message sent
>Hello:  (from Client). 1sss1d
>server's Hello message sent
>Hello:  (from Client). 1sss1d
>server's Hello message sent
>Hello:  (from Client). 1sss1d
>server's Hello message sent
>Hello:  (from Client). 1sss1d
>server's Hello message sent
>Hello:  (from Client). 1sss1d
Tongs-MacBook-Pro:Downloads tongluo$ 

*/

/*

run client in other terminal, then type msg, waiting server's reply


Tongs-MacBook-Pro:Downloads tongluo$ ./golclient 0 hhh
 enter mode of only one command;
./golclient
>>>ss

ss
$>message sent from client. Hello:  (from Client). ss
$>Hello:  (from Server). 
>>>s

s
$>message sent from client. Hello:  (from Client). s
$>Hello:  (from Server). 
>>>s

s
$>message sent from client. Hello:  (from Client). s
$>Hello:  (from Server). 
>>>saa

saa
$>message sent from client. Hello:  (from Client). saa
$>Hello:  (from Server). 
>>>sdaddd

sdaddd
$>message sent from client. Hello:  (from Client). sdaddd
$>Hello:  (from Server). 
>>>q1212

q1212
$>message sent from client. Hello:  (from Client). q1212
$>Hello:  (from Server). 
>>>q1221

q1221
$>message sent from client. Hello:  (from Client). q1221
$>Hello:  (from Server). 
>>>as1

as1
$>message sent from client. Hello:  (from Client). as1
$>Hello:  (from Server). 
>>>aa

aa
$>message sent from client. Hello:  (from Client). aa
$>Hello:  (from Server). 
>>>ssss

ssss
$>message sent from client. Hello:  (from Client). ssss
$>Hello:  (from Server). 
>>>1

1
$>message sent from client. Hello:  (from Client). 1
$>Hello:  (from Server). 
>>>q

Tongs-MacBook-Pro:Downloads tongluo$ 

*/

2. reference

//http://www.cs.tau.ac.il/~eddiea/samples/Non-Blocking/tcp-nonblocking-server.c.html
//https://pubs.opengroup.org/onlinepubs/009695399/functions/send.html
