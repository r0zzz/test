/*
    Name: Daniel Roz Arellano
    Date Started: 24/ 09/ 2024
    Date Finished: 24/ 09/ 2024

    Airport Sim.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h> //-- cannot run on workspace T_T

#define SIZE 6
#define LANDINGTIME 6
#define LANDINGRATE 5
#define TAKEOFFTIME 4
#define TAKEOFFRATE 6

typedef struct {
    int flightNum[3];
    int front;
    int rear;
} QUEUE;

void generatePlane(QUEUE *, QUEUE *);
int generateRand(void);
void enQueue(QUEUE *, int);
int deQueue(QUEUE *);
QUEUE createQueue(void);
bool isEmpty(int, int);

int main(void) {
    srand(time(NULL));

    QUEUE landing;
    QUEUE takeOff;
    int firstRand, secondRand;
    bool empty;
    
    landing = createQueue();
    takeOff = createQueue();

    // initialize landing with two planes to start simulation
    for(int i = 0; i < 2; i++) {
        firstRand = generateRand();
        enQueue(&landing, firstRand);
    }

    // prioritize landing queue
    empty = isEmpty(landing.front, landing.rear);
    while(!empty) {
        printf("Landing - %d\n", deQueue(&landing));
        generatePlane(&landing, &takeOff);
        empty = isEmpty(landing.front, landing.rear);
        sleep(LANDINGTIME*(100));
    }
    // takeoff queue
    empty = isEmpty(takeOff.front, takeOff.rear);
    while (!empty) {
        deQueue(&takeOff);
        printf("Take off - %d\n", deQueue(&takeOff));
        generatePlane(&landing, &takeOff);

        // check if landing queue is empty
        empty = isEmpty(landing.front, landing.rear);
        while(!empty) {
            printf("Landing - %d\n", deQueue(&landing));
            generatePlane(&landing, &takeOff);
            empty = isEmpty(landing.front, landing.rear);
            sleep(LANDINGTIME*(100));
        }
        empty = isEmpty(takeOff.front, takeOff.rear);
        sleep(TAKEOFFTIME*(100));
    }
    empty = isEmpty(landing.front, landing.rear);
    if(empty)
        printf("\nlanding is empty");
        
    
    empty = isEmpty(takeOff.front, takeOff.rear);
    if(empty)
        printf("\ntake off is empty");
}
void generatePlane(QUEUE *landing, QUEUE *takeOff) {
    // generate new flight
    int firstRand, secondRand;
    firstRand = generateRand();
    secondRand = generateRand();
    
    if((firstRand / 60 < LANDINGRATE) && (secondRand / 60 < TAKEOFFRATE)) {
        enQueue(landing, firstRand);
    }
    else {
        enQueue(takeOff, secondRand);
    }
}
int generateRand(void) {
    int num = rand() % 501;
    return num;
}
void enQueue(QUEUE *q, int data) {
	q->flightNum[q->rear] = data;
	q->rear = (q->rear + 1) % SIZE;
}
int deQueue(QUEUE *q) {
	int r = q->flightNum[q->front];
	q->front = (q->front + 1) % SIZE;
	return r;
}
QUEUE createQueue(void) {
	QUEUE q;

    for(int i = 0; i < SIZE; i++)
        q.flightNum[i] = 0;
    q.front = 0;
    q.rear = 0;

    return q;
}
bool isEmpty(int front, int rear) {
	bool empty = false;

	if(front == rear)
		empty = true;
	return empty;
}