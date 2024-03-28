#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <errno.h>
#define MAX_MSG_SIZE 128
struct message {
long mtype;
char mtext[MAX_MSG_SIZE];
};
int main() {
key_t key;
int msgid;
struct message msg;
key = ftok(".", 'a');
if (key == -1) {
perror("ftok");
exit(EXIT_FAILURE);
}
msgid = msgget(key, 0666 | IPC_CREAT);
if (msgid == -1) {
perror("msgget");
exit(EXIT_FAILURE);
}
if (fork() == 0) {
msg.mtype = 1; 
strcpy(msg.mtext, "Hello from sender!");
if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
perror("msgsnd");
exit(EXIT_FAILURE);
}
printf("Message sent from sender: %s\n", msg.mtext);
}
else {
if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
perror("msgrcv");
exit(EXIT_FAILURE);
}

printf("Message received by receiver: %s\n", msg.mtext);
}
if (msgctl(msgid, IPC_RMID, NULL) == -1) {
perror("msgctl");
exit(EXIT_FAILURE);
}
return 0;
}
