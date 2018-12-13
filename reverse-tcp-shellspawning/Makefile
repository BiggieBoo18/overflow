CC     = gcc
CFLAGS = -g -fno-stack-protector -zexecstack

remote_target: remote_target.c
	$(CC) $(CFLAGS) -o $@ remote_target.c
