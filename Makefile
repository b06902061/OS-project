all: main.c task.c FIFO.c RR.c SJF.c PSJF.c scheduler.c timer.c
	gcc main.c FIFO.c RR.c SJF.c PSJF.c scheduler.c timer.c -o main
	gcc task.c timer.c -o task

