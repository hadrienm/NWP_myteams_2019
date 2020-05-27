2->fine
4->not found/acces
5->probleme autre

200 Command okay.\r\n

400 Command not found.\r\n
401 Wrong syntax.\r\n
402 Bad argument.\r\n

500 Must log in.\r\n
501 ID not found.\r\n
502 Too long message.\r\n
503 Action not allowed.\r\n
504 User ID not found.\r\n
505 Team ID not found.\r\n

->/help
<-200
<-402

->/login
<-200
<-401

->/logout
<-200
<-500

->/users
<-200
<-500

->/user
<-200
<-401
<-500
<-501

->/send
<-200
<-401
<-500
<-501
<-502

->/messages
<-200
<-401
<-500
<-501

->/subscribe
<-200
<-401
<-500
<-501

->/subscribed
<-200
<-500
<-501

->/unsubscribed
<-200
<-401
<-500
<-501

->/use
<-200
<-500
<-501

->/create
<-200
<-401
<-500
<-502
<-503

->/list
<-200
<-500

->/info
<-200
<-500