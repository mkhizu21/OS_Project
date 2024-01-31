#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <csignal>
#include <signal.h>
using namespace std;

#define MAX_QUEUE 100  // use a constant for max queue size

sem_t* semaphore = NULL;

int ram, hard, cores, activecores;
int fd[2];

sigset_t signalSet;
    int sig;
   
struct process_para {
	int pid;
	char filename[100];
	int r;
	int h;
};

int iterate = -1, front = -1;
struct process_para queue[MAX_QUEUE];
struct process_para* running = NULL;
int run = 0;

void signalHandler(int signum) {
	bool sig=false;
	int check_id = getpid();
	for(int i=0;i<=front;i++){
	 if(queue[i].pid==check_id){
	    cout<<check_id<<endl;
	    ram+=queue[i].r;
	    hard+=queue[i].h;
	    activecores--;
		sig=true;
	    break;
	 }
	}
	if(sig){
	cout<<"Function Working"<<endl;
}
else{
cout<<"Function Not Working"<<endl;
}
}

void compliefile(char* filename) {
	char command[100];
	sprintf(command, "g++ -o %s.out %s", filename, filename);
	if (system(command) != 0) {
		perror("g++");
		exit(EXIT_FAILURE);
	}

}

void runfile(char* filename) {
	char cmd[100];
	sprintf(cmd, "x-terminal-emulator -e './%s.out ' &", filename);
	system(cmd);


}
int emptycore() {
	for (int i = 0; i < cores; i++) {
		if (running[i].pid == 0) {
			return i;
		}
	}
}

void insert_to_queue(struct process_para obj) {
	iterate = (iterate + 1) % MAX_QUEUE;
	queue[iterate].pid = obj.pid;
	strcpy(queue[iterate].filename, obj.filename);
	queue[iterate].r = obj.r;
	queue[iterate].h = obj.h;
}
void* threads(void* arg) {
	sem_wait(semaphore);
	if (activecores > 0) {
		activecores--;
		front++;
		while (ram < queue[front].r) {
			continue;
		}
		int x = emptycore();
		running[x].pid = queue[front].pid;
		ram = ram - queue[front].r; // Update RAM
		hard = hard - queue[front].h; // Update Hard
		compliefile(queue[front].filename);
		runfile(queue[front].filename);
	}
	sem_post(semaphore);
	//cout << "OK process" << endl;
}

int create_process(struct process_para obj) {
	pthread_t t;
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_t p;
	p = fork();
	if (p == -1) {
		cout << "Process not created: "  << obj.filename; 
		return 0;
	}
	else if (p == 0) {
		int x = getpid();
		obj.pid = x;
		cout << "ID = " << x;
//		printf("The id is %d\n", x);
		close(fd[0]); // close reading end of pipe
		write(fd[1], &x, sizeof(x)); // write message to pipe
		close(fd[1]); // close
		exit(EXIT_SUCCESS);
	}
	else {
		close(fd[1]); // close writing end of pipe
		int id = 0;
		read(fd[0], &id, sizeof(id)); // read message from pipe
		obj.pid = id;
		if ((iterate + 1) % MAX_QUEUE != front) {
			insert_to_queue(obj);
		}
		else {
			//printf("Queue is full right now try again later : \n");
			cout << "Queue is full right now try again later : \n";
			return 0;
		}
	}
	pthread_create(&t, NULL, threads, semaphore);
	pthread_join(t, NULL);
	return 0;
}

	//void* signalThread(void* args) {
    	 //while (true)
    	 //{
         // Wait for a signal to be received
	  //if (sigwait(&signalSet, &sig) != 0) {
            //cout<<"Error waiting for signal\n"<<endl;
            //break;
          //}
    	 //}
//}

int main() {
	int opt;
	//signal(SIGINT, signalHandler);
        //signal(SIGTERM, signalHandler);
	cout << "Enter RAM(MBs): ";
	cin >> ram;
	cout << "Enter Hard(MBs): ";
	cin >> hard;
	cout << "Enter cores: ";
	cin >> cores;
    getchar(); // consume newline character
    running = (struct process_para*)malloc(cores * sizeof(struct process_para)); // allocate memory for n integers
    for (int i = 0; i < cores; i++) {
        running[i].pid = 0;

    }
    activecores = cores;
    char semaphore_name[100];
    sprintf(semaphore_name, "semaphore_%d", getpid());
	cout << semaphore_name;
    semaphore = sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, cores);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
	do {
		cout << "Welcome To The Main Menu!" << endl << endl;
		cout << "1) Calculator" << endl;
		cout << "2) Calender" << endl;
		cout << "3) Games" << endl;
		cout << "4) Music" << endl;
		cout << "5) Notepad" << endl;
		cout << "6) Date and Time" << endl;
		cout << "7) ShutDown" << endl;
		cout << "Enter Here : ";
		cin >> opt;
		system("clear");

		switch (opt) {
		case 1: {
			struct process_para obj;
        	strcpy(obj.filename, "calculator.cpp");
        	obj.r = 10;
            obj.h = 20;
            create_process(obj);
			break;
		}
		case 2: {
			struct process_para obj;
        	strcpy(obj.filename, "calender.cpp");
        	obj.r = 50;
            obj.h = 80;
            create_process(obj);
			break;
		}
		case 3: {
			int game_opt;
			do {
				cout << "Welcome To The Game Menu!" << endl << endl;
				cout << "1) Candy Crush" << endl;
				cout << "2) Tic Tac Toe" << endl;
				cout << "3) Exit" << endl;
				cout << "Enter Here : ";
				cin >> game_opt;
				switch (game_opt) {
				case 1: {
					system("clear");
				struct process_para obj;
        		strcpy(obj.filename, "candy_crush.cpp");
        		obj.r = 80;
            	obj.h = 100;
            	create_process(obj);
					break;
				}
				case 2: {
					system("clear");
				struct process_para obj;
        		strcpy(obj.filename, "tictactoe.cpp");
        		obj.r = 60;
            	obj.h = 80;
            	create_process(obj);
					break;
				}
				case 3: {
					system("clear");
					cout << "You Are Exiting From Game Menu!" << endl;
					game_opt = 3;
					
					system("clear");
					break;
				}
				default: {
					cout << "Invalid Input!" << endl;
					break;
				}
				}
			} while (game_opt != 3);
			break;
		}
		case 4: {
			struct process_para obj;
        	strcpy(obj.filename, "mus.cpp");
        	obj.r = 10;
            obj.h = 10;
            create_process(obj);
			break;
		}
		case 5: {
			struct process_para obj;
        	strcpy(obj.filename, "notepad.cpp");
        	obj.r = 40;
            obj.h = 60;
            create_process(obj);
			break;
		}
		case 6: {
			struct process_para obj;
        	strcpy(obj.filename, "date2.cpp");
        	obj.r = 40;
            obj.h = 60;
            create_process(obj);
			break;
		}
		case 7: {
			system("clear");
			cout << "Thanks For Using Mutantu" << endl;
			sleep(5);
			system("clear");
			break;
		}
		default: {
			cout << "Invalid Input!" << endl;
			break;
		}
		}
	} while (opt != 7);
	
	if (sem_close(semaphore) < 0) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
	return 0;
}
