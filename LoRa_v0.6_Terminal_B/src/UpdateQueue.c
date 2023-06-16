
#include "UpdateQueue.h"
#include "customCommandsTerminalFerry.h"



uint8_t isEmpty(struct queStruct s) {
	if (s.front == -1 && s.rear == -1)
	return 1;
	else
	return 0;
}


uint8_t isFull(struct queStruct s) {
	if ((s.rear + 1) % MAX_QUEUE_SIZE == s.front)
	return 1;
	else
	return 0;
}

void push_back(struct queStruct* s,uint8_t data) {
	if (isFull(*s)) {
		printf("Queue is full.\n");
		return;
		} else if (isEmpty(*s)) {
		s->front = 0;
		s->rear = 0;
		} else {
		s->rear = (s->rear + 1) % MAX_QUEUE_SIZE;
	}
	s->queue[s->rear] = data;
	printf("Added %d\n", data);
}

uint8_t pop_front(struct queStruct* s) {
	uint8_t data;
	if (isEmpty(*s)) {
		printf("Queue is empty.\n");
		return -1;
		} else if (s->front == s->rear) {
		data = s->queue[s->front];
		s->front = -1;
		s->rear = -1;
		} else {
		data = s->queue[s->front];
		s->front = (s->front + 1) % MAX_QUEUE_SIZE;
	}
	return data;
}

