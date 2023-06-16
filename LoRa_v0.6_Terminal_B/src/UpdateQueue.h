#ifndef UPDATE_QUEUE_H
#define UPDATE_QUEUE_H

#include <stdio.h>

/* Max size of order queue */
#define MAX_QUEUE_SIZE		3


/* Queue structure for on demand order handling */
struct queStruct
{
	uint8_t queue[MAX_QUEUE_SIZE];
	uint8_t front;
	uint8_t rear;
};


/*********************************************************************
* Function: uint8_t isEmpty(struct queStruct s);
*
* Overview: Checks if order queue is empty
*
* PreCondition: 
*
* Input: Queue structure
*
* Output: Empty = 1
*
********************************************************************/
uint8_t isEmpty(struct queStruct s);

/*********************************************************************
* Function: uint8_t isFull(struct queStruct s);
*
* Overview: Checks if order queue is full
*
* PreCondition: 
*
* Input: Queue structure
*
* Output: Full = 1
*
********************************************************************/
uint8_t isFull(struct queStruct s);

/*********************************************************************
* Function: void push_back(struct queStruct* s, uint8_t data);
*
* Overview: Place data at first free element
*
* PreCondition: 
*
* Input:
	struct queStruct*s: queue structure
	uint8_t data: data value to be placed
*
* Output: None
*
********************************************************************/
void push_back(struct queStruct* s, uint8_t data);


/*********************************************************************
* Function: uint8_t pop_front(struct queStruct* s);
*
* Overview: Deletes first element from order queue
*
* PreCondition: 
*
* Input: Queue structure
*
* Output: None
*
********************************************************************/
uint8_t pop_front(struct queStruct* s);



#endif
