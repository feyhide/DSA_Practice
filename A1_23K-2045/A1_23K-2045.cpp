#include <iostream>
#include <ctime>
#include <stack>
#include <queue>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <limits>
#include <cstdio> 
#include <cstdlib>
#include <conio.h>

using namespace std;

//set globally these value to access them whereever i need
int sorting = 0;
int searching = 0;

// this function is for getting input of integer without breaking program
int validInt(string type) {
	cout << endl;
    if(type == "Priority"){
    	int num;
	    while (true) {
	        cout << "Enter " << type << " (1-High, 2-Medium, 3-Low) " << " : ";
	        if (cin >> num && num > 0 && num <= 3) {
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	            return num; 
	        } else {
	            cout << "Invalid " << type << ". Please enter a correct value"<<endl;
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	        }
	    }
	    cout << endl;
	}else{
		cout << endl;
        int num;
	    while (true) {
	        cout << "Enter " << type << " : ";
	        if (cin >> num && num > 0) {
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	            return num; 
	        } else {
	            cout << "Invalid " << type << ". Please enter a correct value"<<endl;
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	        }
	    }
	    cout << endl;
	}
}

//function for getting inputs of sort and search from user file
void fetchConfig() {
	cout << "******** Configuration ********" << endl;
	cout << endl;
    ifstream inputFile("config.txt");
    string line1;
    string line2;
    
    if (inputFile.is_open()) {
        if (getline(inputFile, line1)) {
            cout << "Your Sorting Choice: " << line1 << endl;
            if (line1 == "Bubble Sort") {
                sorting = 1;
            } else if (line1 == "Insertion Sort") {
                sorting = 2;
            } else if (line1 == "Selection Sort") {
                sorting = 3;
            } else if (line1 == "Quick Sort") {
                sorting = 4;
            } else if (line1 == "Merge Sort") {
                sorting = 5;
            } else {
            	cout << endl;
                cout << "Invalid sorting choice" << endl;
            	cout << "Setting sorting to Bubble Sort as Default" << endl;
            	cout << endl;
            	sorting = 1;
			}
        }
		cout << endl;
        if (getline(inputFile, line2)) {
            cout << "Your Searching Choice: " << line2 << endl;
            if (line2 == "Binary Search") {
                searching = 1;
            } else if (line2 == "Interpolation Search") {
                searching = 2;
            } else {
            	cout << endl;
                cout << "Invalid searching choice" << endl;
            	cout << "Setting searching to Binary Search as Default" << endl;
            	searching = 1;
            	cout << endl;
			}
        }
        inputFile.close();
    } else {
        cout << "Unable to open the file" << endl;
        cout << "Setting searching to Binary Search as Default" << endl;
        searching = 1;
        cout << "Setting sorting to Bubble Sort as Default" << endl;
        sorting = 1;
    }
	cout << endl;
}


struct Ticket {
    int ticketId;
    string customerName;
    int priority;
    string description;
    time_t creationTime;
    bool isOpen;
    time_t closeTime;
    Ticket* next;
    bool isAssigned;

    Ticket(int id, string name, int priority, string description)
        : ticketId(id), customerName(name), priority(priority), description(description), isOpen(true), next(NULL) {
        creationTime = time(0);
        closeTime = 0;
        isAssigned = false;
    }
};

struct Agent {
    int agentID;
    string name;
    bool isAvailable;
    int* assignedTickets; 
    int assignedCount;
    int assignedCapacity; 

    Agent(int id, string agentName) : agentID(id), name(agentName), isAvailable(true), assignedCount(0), assignedCapacity(3) {
        assignedTickets = new int[assignedCapacity]; 
    }

    ~Agent() { 
        delete[] assignedTickets;
    }
	
	// to add tickets in agent's array
    void addTicket(int ticketId) {
        if (assignedCount < assignedCapacity) {
            assignedTickets[assignedCount++] = ticketId;
        }
    }
    
	// to remove tickets in agent's array
    void removeTicket(int ticketId) {
        for (int i = 0; i < assignedCount; i++) {
            if (assignedTickets[i] == ticketId) {
                for (int j = i; j < assignedCount - 1; j++) {
                    assignedTickets[j] = assignedTickets[j + 1];
                }
                assignedCount--;
                break;
            }
        }
    }
};

class TicketManager {
    Ticket* head;
    stack<Ticket*> resolutionLog;
    queue<Ticket*> pendingTicketsQueue;
	
	// use in closing or other functions as they will only work on linear searching to get ticket ID
	Ticket* linearSearchById(int ticketId){
		int size = getTicketSize();
		Ticket* temp = head;
		while(temp!=NULL){
			if(temp->ticketId == ticketId){
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}
	
	// interpolation search by id and name below
	Ticket* interpolationSearchById(int ticketId) {
        Ticket* low = head;
        Ticket* high = head;
        while (high && high->next) {
            high = high->next; 
        }

        while (low && high && low->ticketId <= ticketId && high->ticketId >= ticketId) {
            if (low == high) {
                if (low->ticketId == ticketId) return low;
                return NULL;
            }

            int pos = low->ticketId + (ticketId - low->ticketId) * (high->ticketId - low->ticketId) / (high->ticketId - low->ticketId);
            Ticket* mid = low;

            while (mid && mid->ticketId < pos) {
                mid = mid->next;
            }

            if (mid && mid->ticketId == ticketId) return mid;

            if (mid && mid->ticketId < ticketId) {
                low = mid->next; 
            } else {
                high = mid; 
            }
        }
        return NULL;
    }
	
	Ticket* interpolationSearchByName(string name) {
	    Ticket* low = head;
	    Ticket* high = head;
	
	    while (high && high->next) {
	        high = high->next;
	    }
	
	    int totalTickets = getTicketSize();
	
	    while (low && high && low != high) {
	        if (low->customerName <= name && high->customerName >= name) {
	            int lowLength = low->customerName.length();
	            int highLength = high->customerName.length();
	
	            if (highLength - lowLength == 0) {
	                return NULL;
	            }
	
	            int pos = ((name.length() - lowLength) * (totalTickets - 1)) / (highLength - lowLength);
	
	            Ticket* mid = low;
	            for (int i = 0; i < pos && mid != high; i++) {
	                mid = mid->next;
	            }
	
	            if (mid && mid->customerName == name) {
	                return mid;
	            }
	
	            if (mid && mid->customerName.length() < name.length()) {
	                low = mid->next;
	            } else {
	                high = mid;
	            }
	        } else {
	            return NULL;
	        }
	    }
	    return NULL;
	}
	
	//binary search by id and name below
    Ticket* binarySearchById(int ticketId) {
	    Ticket* start = head;
	    Ticket* end = NULL;
	
	    while (start != end) {
	        Ticket* mid = getMiddle(start, end);
	        if (!mid){
	        	return NULL;
			}
	
	        if (mid->ticketId == ticketId)
	            return mid;
	        else if (mid->ticketId < ticketId)
	            start = mid->next; 
	        else
	            end = mid;  
	    }
	    return NULL;
	}

	
    Ticket* binarySearchByName(string name) {
	    Ticket* start = head;
	    Ticket* end = NULL;
	
	    while (start != end) {
	        Ticket* mid = getMiddle(start, end);
	        if (!mid) {
	            return NULL;
	        }
	
	        if (mid->customerName.length() == name.length()) {
	            return mid;
	        } else if (mid->customerName.length() < name.length()) {
	            start = mid->next;
	        } else {
	            end = mid;
	        }
	    }
	    return NULL;
	}
	
	// to get middle of node(Tickets)
	Ticket* getMiddle(Ticket* start, Ticket* end) {
	    if (!start){
	    	return NULL;
		}
	    Ticket* slow = start;
	    Ticket* fast = start->next;
	
	    while (fast != end && fast->next != end) {
	        fast = fast->next;
	        if (fast != end) {
	            slow = slow->next;
	            fast = fast->next->next;
	        }
	    }
	    return slow;
	}
	
    // to get size of tickets node
    int getTicketSize() {
        Ticket* temp = head;
        int count = 0;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // bubble sort with respect to attribute
    void bubbleSort(int attribute) {
        if (!head) return;

        bool swapped;
        do {
            swapped = false;
            Ticket* current = head;
            while (current->next) {
                if (shouldSwap(current, current->next, attribute,0)) {
			        swap(current->ticketId, current->next->ticketId);
			        swap(current->customerName, current->next->customerName);
			        swap(current->priority, current->next->priority);
			        swap(current->description, current->next->description);
			        swap(current->creationTime, current->next->creationTime);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // insertion sort with respect to attribute
    void insertionSort(int attribute) {
        if (!head) return;

        Ticket* sorted = NULL;
        Ticket* current = head;

        while (current) {
            Ticket* next = current->next;
            if (!sorted || shouldSwap(sorted, current, attribute,0)) {
                current->next = sorted;
                sorted = current;
            } else {
                Ticket* temp = sorted;
                while (temp->next && shouldSwap(current, temp->next, attribute,0)) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    // selection sort with respect to attribute
    void selectionSort(int attribute) {
        if (!head) return;
		Ticket* temp = head;
		
		while(temp){
			Ticket* min = temp;
			Ticket* current = temp->next;
			
			while(current){
				if(shouldSwap(min,current,attribute,0)){
					min = current;
				}
				current = current->next;
			}	
			
			if(min != temp){
				swap(min->ticketId, temp->ticketId);
		        swap(min->customerName, temp->customerName);
		        swap(min->priority, temp->priority);
		        swap(min->description, temp->description);
		        swap(min->creationTime, temp->creationTime);
			}
			
			temp = temp->next;
		}
    }

    // merge function for merge sort
    Ticket* merge(Ticket* left, Ticket* right,int attribute) {
        if (!left){
        	return right;
		}
        if (!right){
        	return left;
		}
        Ticket* tempHead = new Ticket(0,"00",0,"00");
	    Ticket* temp = tempHead;
		while(left && right){
	        if(shouldSwap(right,left,attribute,0)){
	        	temp->next = left;
				left = left->next;
			}else{
				temp->next = right;
				right = right->next;
			}
			temp = temp->next;
	    }
	    
	    if(left){
			temp->next = left;
		}
		if(right){
			temp->next = right;
		}
		Ticket* mergedHead = tempHead->next;
	    delete tempHead; 
	    return mergedHead;
    }


    // merge sort with respect to attribute
    Ticket* mergeSort(Ticket* head,int attribute) {
        if (!head || !head->next){
			return head;
		}

        Ticket* mid = getMiddle(head,NULL);
       	Ticket* left = head;
    	Ticket* right = mid->next;
    	mid->next = NULL;
	    left = mergeSort(head,attribute);
        right = mergeSort(right,attribute);

        return merge(left, right,attribute);
    }

    // partition function for quick sort
    Ticket* partition(Ticket* low, Ticket* high, int attribute) {
        Ticket* pivot = high;
        Ticket* i = low;

        for (Ticket* j = low; j != high; j = j->next) {
            if (shouldSwap(pivot,j,attribute,1)) {
                swap(i->ticketId, high->ticketId);
		        swap(i->customerName, high->customerName);
		        swap(i->priority, high->priority);
		        swap(i->description, high->description);
		        swap(i->creationTime, high->creationTime);
                i = i->next;
            }
        }
        swap(i->ticketId, high->ticketId);
        swap(i->customerName, high->customerName);
        swap(i->priority, high->priority);
        swap(i->description, high->description);
        swap(i->creationTime, high->creationTime);
        return i;
    }

    // quick sort with respect to attribute
    void quickSort(Ticket* low, Ticket* high,int attribute) {
        if (low && high && low != high) {
            Ticket* p = partition(low, high,attribute);
            quickSort(low, p,attribute);
            quickSort(p->next, high,attribute);
        }
    }

    bool shouldSwap(Ticket* a, Ticket* b, int attribute,int isQuickSort) {
		if(!isQuickSort){
			switch (attribute) {
	            case 1:
	                return a->priority > b->priority;
	            case 2: 
	                return a->creationTime > b->creationTime; 
	            case 3: 
	                return a->customerName.length() > b->customerName.length();
	            default:
	                return false;
	        }
		}else{
			switch (attribute) {
	            case 1:
	                return a->priority >= b->priority;
	            case 2: 
	                return a->creationTime >= b->creationTime; 
	            case 3: 
	                return a->customerName.length() >= b->customerName.length();
	            default:
	                return false;
	        }
		}
    }
    
    // to get tail of node tickets
    Ticket* getLastNode(){
    	Ticket* last = head;
        while (last && last->next) {
            last = last->next;
        }
        return last;
	}
public:
    TicketManager() : head(NULL) {}
    
    // function to sort ticket by asking preference
    void sortTickets() {
        cout << endl;
        
        int attributePref;
        cout << "Choose Attribute to which you want to sort tickets" << endl;
        cout << "1. Priority" << endl;
        cout << "2. Created Time" << endl;
        cout << "3. Customer Name" << endl;
        attributePref = validInt("Attribute Preference");
        
        if(attributePref < 1 || attributePref > 3){
        	cout << "Invalid Preference" << endl;
        	cout << "Setting Attribute Preference to Customer Name" << endl;
        	attributePref = 3;
		}
        
        int size = getTicketSize();
        if (size > 10) {
        	cout << "Data is greater than threshold using Merge Sort" << endl;
			clock_t start = clock();
            head = mergeSort(head,attributePref);
            
            cout << "----------------------------------------------------" << endl;
			clock_t end = clock();
			double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
			printTickets();
            cout << "Tickets sorted using Merge Sort." << endl;
			cout << "Time taken by function: " << duration << endl;
        	cout << "----------------------------------------------------" << endl;
		} else {
            switch (sorting) {
                case 1:{
            		cout << "----------------------------------------------------" << endl;
                	clock_t start = clock();
                    bubbleSort(attributePref);
					clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
                    printTickets();
                    cout << "Tickets sorted using Bubble Sort" << endl;
                    cout << "Time taken by function: " << duration << endl;
					cout << "----------------------------------------------------" << endl;
                    break;
				}
                case 2:{
                	cout << "----------------------------------------------------" << endl;
                    clock_t start = clock();
                    insertionSort(attributePref); 
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
					printTickets();
                    cout << "Tickets sorted using Insertion Sort" << endl;
                    cout << "Time taken by function: " << duration << endl;
                    cout << "----------------------------------------------------" << endl;
                    break;
            	}
                case 3:{
                	cout << "----------------------------------------------------" << endl;
                    clock_t start = clock();
                    selectionSort(attributePref); 
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
                    printTickets();
                    cout << "Tickets sorted using Selection Sort" << endl;
                    cout << "Time taken by function: " << duration << endl;
                    cout << "----------------------------------------------------" << endl;
                    break;
                }
                case 4:{
                	cout << "----------------------------------------------------" << endl;
                    clock_t start = clock();
					Ticket* last = getLastNode();
					quickSort(head, last,attributePref);
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
                    printTickets();
                    cout << "Tickets sorted using Quick Sort" << endl;
                    cout << "Time taken by function: " << duration << endl;
					cout << "----------------------------------------------------" << endl;
                    break;
                }
                case 5:{
                	cout << "----------------------------------------------------" << endl;
                	clock_t start = clock();
					head = mergeSort(head,attributePref);
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
					printTickets();
                    cout << "Tickets sorted using Merge Sort" << endl;
					cout << "Time taken by function: " << duration << endl;
                    cout << "----------------------------------------------------" << endl;
					break;
				}
                default:{
                    cout << "Invalid choice" << endl;
                    break;
                }
            }
        }
        cout << endl;
    }
    
    // inserting tickets from head
    void addTicket(string name, int priority, string description) {
		int id = getTicketSize() + 1;
		Ticket* newTicket = new Ticket(id, name, priority, description);
        newTicket->next = head;
        head = newTicket;
        pendingTicketsQueue.push(newTicket);
        cout << "******** Ticket added ********" << endl;
        cout << "Ticket ID : " << id << endl;
		cout << "Customer Name : " << name << endl;
		cout << "Priority : " << priority << endl;
		cout << "Description : " << description << endl;
	}
	
	// removing ticket with id
    void removeTicket(int ticketId,bool allowPrint) {
		Ticket* temp = head;
        Ticket* prev = NULL;
        while (temp && temp->ticketId != ticketId) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp){
        	cout << "Ticket not found " << endl;
        	return;	
		}
		
		removeTicketFromPendingQueue(temp->ticketId);
		
        if (prev) prev->next = temp->next;
        else head = temp->next;
        delete temp;
        if(allowPrint){
        	cout << "Ticket removed : " << ticketId << endl;
		}
    }
	
	//searching algo with respect to method and id
    Ticket* searchTicketById(int ticketId,int method) {
        switch (method) {
            case 1:
                return interpolationSearchById(ticketId);
            case 2:
                return binarySearchById(ticketId);
            case 3:
            	return linearSearchById(ticketId);
            default:
                return NULL;
        }
    }
    
    //searching algo with respect to method and name
    Ticket* searchTicketByName(string name, int method) {
        switch (method) {
            case 1:
                return interpolationSearchByName(name);
            case 2:
                return binarySearchByName(name);
            default:
                return NULL;
        }
    }
	
	// function to close tickets by pushing copy of them to reslog
    void closeTicket(int ticketId) {
        cout << endl;
		Ticket* ticket = searchTicketById(ticketId,3);
		cout << ticket->ticketId <<endl;
        if (ticket && !ticket->isAssigned){
			cout << "Ticket is not assigned to any agent yet" << endl;
			return;
		}
		if (ticket && ticket->isOpen) {
			ticket->isOpen = false;
            ticket->closeTime = time(0);
            Ticket* copyTicket = new Ticket(*ticket);
            resolutionLog.push(copyTicket);
            cout << "Ticket closed : " << ticketId << endl;
            
        } else {
            cout << "Ticket not found or already closed" << endl;
        }
        cout << endl;
    }

	// to view reslog
    void viewResolutionLog() {
        cout << endl;
        stack<Ticket*> tempLog = resolutionLog;
        cout << "******** Recent Ticket Resolutions ********" << endl;
        while (!tempLog.empty()) {
            Ticket* ticket = tempLog.top();
            tempLog.pop();
            cout << "--------------------------" << endl;
			cout << "Ticket ID : " << ticket->ticketId << endl;
			cout << "Customer Name : " << ticket->customerName << endl;
			cout << "Opened at : " << ctime(&ticket->creationTime);
			cout << "Closed at : " << ctime(&ticket->closeTime);
        	cout << "--------------------------" << endl;
        	cout << endl;
		}
        cout << endl;
    }
	
	// to view pending queue of tickets
    void viewPendingQueue() {
        cout << endl;
        queue<Ticket*> tempQueue = pendingTicketsQueue;
        cout << "******** Pending Tickets ********" << endl;
        while (!tempQueue.empty()) {
            Ticket* ticket = tempQueue.front();
            tempQueue.pop();
        	cout << "Ticket ID : " << ticket->ticketId << endl;
			cout << "Customer Name : " << ticket->customerName << endl;
			cout << "Priority : " << ticket->priority << endl;
			cout << "Created at : " << ctime(&ticket->creationTime);
			cout << endl;
		}
    	cout << endl;
    }
	
	// to get ticket from pending queue
    queue<Ticket*>& getPendingTicketsQueue() {
        return pendingTicketsQueue;
    }
    
    // to remove ticket from pending queue
    void removeTicketFromPendingQueue(int id){
    	queue<Ticket*> tempQueue;
    	Ticket* tempTicket;
		while(!pendingTicketsQueue.empty()){
    		tempTicket = pendingTicketsQueue.front();
    		pendingTicketsQueue.pop();
    		if(tempTicket->ticketId != id){
				tempQueue.push(tempTicket);
			}
		}
		pendingTicketsQueue = tempQueue;
	}
	
	void printTickets(){
    	cout << endl;
    	Ticket* temp = head;
    	while(temp != NULL){
    		cout << "--------------------------" << endl;
	        cout << "Ticket ID : " << temp->ticketId << endl;
			cout << "Customer Name : " << temp->customerName << endl;
			cout << "Created at : " << ctime(&temp->creationTime);
			cout << "Priority : " << temp->priority << endl;
			cout << "--------------------------" << endl;
			cout << endl;
    		temp = temp->next;
		}
    	cout << endl;
	}
};

class AgentManager {
    Agent** agents;
    int agentCount;
    int agentCapacity; 

public:
    AgentManager() : agentCount(0), agentCapacity(2) { 
        agents = new Agent*[agentCapacity]; 
    }

    ~AgentManager() { 
        for (int i = 0; i < agentCount; i++) {
            delete agents[i]; 
        }
        delete[] agents; 
    }
	
	// to add agent in dma
    void addAgent(string name) {
        cout << endl;
        if (agentCount >= agentCapacity) { 
            agentCapacity *= 2;
            Agent** newAgents = new Agent*[agentCapacity];
            for (int i = 0; i < agentCount; i++) {
                newAgents[i] = agents[i];
            }
            delete[] agents;
            agents = newAgents;
        }
        int id = agentCount + 1;
        agents[agentCount++] = new Agent(id, name); 
        cout << "******** Agent Added ********" << endl;
        cout << "Agent ID : " << id << " , Agent Name : " << name << endl;
        cout << endl;
    }
	
	// to assign ticket wrt priority to those who have fewer tasks
    void assignTicket(queue<Ticket*>& pendingTicketsQueue, TicketManager* allTickets) {
	    cout << endl;
	    if (pendingTicketsQueue.empty()) {
	        cout << "No tickets pending in queue" << endl;
	        return;
	    }
	
	    cout << "******** Assigning tickets to agents ********" << endl;
	    for (int prior = 1; prior <= 3; prior++) {
	        bool hasPendingTickets = true;
	
	        while (hasPendingTickets) {
	            hasPendingTickets = false; 
	            queue<Ticket*> tempTicketQueue;
	
	            while (!pendingTicketsQueue.empty()) {
	                Ticket* ticket = pendingTicketsQueue.front();
	                pendingTicketsQueue.pop();
	
	                if (ticket->priority == prior) {
	                    int minAssignedCount = INT_MAX;
	                    int selectedAgentIndex = -1;
	
	                    for (int i = 0; i < agentCount; i++) {
	                        if (agents[i]->isAvailable) {
	                            int currentAssignedCount = agents[i]->assignedCount;
	                            if (currentAssignedCount < minAssignedCount) {
	                                minAssignedCount = currentAssignedCount;
	                                selectedAgentIndex = i; 
	                            }
	                        }
	                    }
	
	                    if (selectedAgentIndex != -1) {
	                        agents[selectedAgentIndex]->addTicket(ticket->ticketId);
	                        ticket->isAssigned = true;
	                        cout << "Ticket ID : " << ticket->ticketId << " , Priority : " << ticket->priority 
	                             << " assigned to Agent " << agents[selectedAgentIndex]->name << endl;
	
	                        if (agents[selectedAgentIndex]->assignedCount == 3) {
	                            agents[selectedAgentIndex]->isAvailable = false;
	                        }
	                        hasPendingTickets = true; 
	                    } else {
	                        tempTicketQueue.push(ticket);
	                    }
	                } else {
	                    tempTicketQueue.push(ticket);
	                }
	            }
	            while (!tempTicketQueue.empty()) {
	                Ticket* ticket = tempTicketQueue.front();
	                tempTicketQueue.pop();
	                pendingTicketsQueue.push(ticket);
	            }
	        }
	    }
	    cout << endl;
	}
	
	// to remove ticket from agent;s array once ticket is closed
    void removeTicketFromAgent(int ticketId, TicketManager* allTickets) {
	    for (int i = 0; i < agentCount; i++) {
	        Agent* agent = agents[i];
	
	        for (int j = 0; j < agent->assignedCount; j++) {
	            if (agent->assignedTickets[j] == ticketId) {
	                agent->removeTicket(ticketId);
	                allTickets->removeTicket(ticketId, 0); 
	                if (agent->assignedCount < 3) {
	                    agent->isAvailable = true;
	                }
	                return; 
	            }
	        }
	    }
	}
	
	// to view tasks agent have to do
    void viewAgentLoad(TicketManager* allTickets) {
        cout << endl;
        cout << "******** Agent Load ********" << endl;

        for (int i = 0; i < agentCount; i++) {
            cout << "----------------------------------------------------" << endl; 
            cout << "Agent ID : " << agents[i]->agentID << endl;
            cout << "Name : " << agents[i]->name << endl;
            cout << "Assigned Tickets : " << agents[i]->assignedCount << endl;

            for (int j = 0; j < agents[i]->assignedCount; j++) {
                int ticketId = agents[i]->assignedTickets[j];
                Ticket* temp = allTickets->searchTicketById(ticketId, 3);

                if (temp) {
                    cout << "--------------------------" << endl;
                    cout << "Ticket ID : " << temp->ticketId << endl;
                    cout << "Customer Name : " << temp->customerName << endl;
                    cout << "Created at : " << ctime(&temp->creationTime); 
                    cout << "Priority : " << temp->priority << endl;
                    cout << "--------------------------" << endl; 
                } else {
                    cout << "Ticket ID : " << ticketId << " not found." << endl; 
                }
            } 	
            cout << "----------------------------------------------------" << endl; 
        }
        cout << endl; 
    }
};

void showMenu() {
    cout << "\n******** One-Stop Management System ********\n";
    cout << "1. Add Ticket" << endl;
	cout << "2. Remove Ticket" << endl;
	cout << "3. Sort Tickets" << endl;
	cout << "4. Search Ticket" << endl;
	cout << "5. Close Ticket" << endl;
    cout << "6. Add Agent" << endl;
	cout << "7. Assign Ticket to Agent" << endl;
	cout << "8. View Resolution Log" << endl;
    cout << "9. View Pending Tickets" <<endl;
	cout << "10. View Agent Load" << endl;
	cout << "11. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
	
	fetchConfig();
	cout << "Press any key to continue..." << endl;
    _getch();
    system("cls");
    
    TicketManager ticketManager;
    AgentManager agentManager;
    int choice;

    while (true) {
        showMenu();
        choice = validInt("Choice");

        if (choice == 1) {
        	// asking details to create ticket
        	
            int priority;
            string name, description;
            cout << endl;
        	cout << "Enter Customer Name : ";
            getline(cin >> ws, name);
            priority = validInt("Priority");
            cout << endl;
        	cout << "Enter Description : ";
            getline(cin >> ws, description);
            
			cout << "----------------------------------------------------" << endl; 
            clock_t start = clock();
            ticketManager.addTicket(name, priority, description);
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl; 
        }
        else if (choice == 2) {
        	// asking details to remove ticket
            int id;
            id = validInt("Ticket ID to remove");
            
            cout << "----------------------------------------------------" << endl; 
			clock_t start = clock();
            ticketManager.removeTicket(id,true);
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl; 
        }
        else if (choice == 3) {
        	// sort tickets
        	ticketManager.sortTickets();
		}
        else if (choice == 4) {
        	// search tickets by asking user method
        	int choice;
        	cout << endl;
            cout << "Choose searching method:" << endl;
            cout << "1. By Id" << endl;
            cout << "2. By Name" << endl;
            cin >> choice;
        	switch(choice){
				case 1:{
					int id;
		            id = validInt("Ticket ID to search");
		            
		            cout << "----------------------------------------------------" << endl; 
					clock_t start = clock();
                    Ticket* ticket = ticketManager.searchTicketById(id,searching);
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
					
		            if (ticket){
		                cout << "******** Ticket Found ********" << endl;
		                cout << "Ticket ID : " << ticket->ticketId << endl;
						cout << "Customer : " << ticket->customerName << endl;
		            }else{
		                cout << "Ticket not found" << endl;
					}
					cout << endl;
					cout << "Time taken by function: " << duration << endl;
					cout << "----------------------------------------------------" << endl; 
					
					break;
				}
				case 2:{
					string name;	
					cout << "Ticket Name to search" << endl;
	            	getline(cin >> ws, name);
		            cout << "----------------------------------------------------" << endl;
					clock_t start = clock();
                    Ticket* ticket = ticketManager.searchTicketByName(name,searching);
		            clock_t end = clock();
					double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
					
		            if (ticket){
		                cout << "******** Ticket Found ********" << endl;
		                cout << "Ticket ID : " << ticket->ticketId << endl;
						cout << "Customer : " << ticket->customerName << endl;
		            }else{
		                cout << "Ticket not found" << endl;
					}
					cout << endl;
					cout << "Time taken by function: " << duration << endl;
					cout << "----------------------------------------------------" << endl;
					cout << endl;
					break;
				}
				default:{
   	            	cout << "Invalid choice" << endl;
        			cout << endl;
					break;
				}
        	}
			
		}
		else if (choice == 5) {
			// to close ticket first put in reslog then remove ticket from agent;s arr then delete it by calling removeTickets from ticket manager inside agentManager.removeTicketFromAgent 
			cout << endl;
		    int id;
		    id = validInt("Ticket ID to close");
		    clock_t start = clock();
            ticketManager.closeTicket(id);
            agentManager.removeTicketFromAgent(id,&ticketManager);
            
            cout << "----------------------------------------------------" << endl;
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
            cout << endl;
        }
        else if (choice == 6) {
        	// asking details to add agent
            cout << endl;
			int id;
            string name;
            cout << "Enter Agent Name : ";
            cout << endl;
        	getline(cin >> ws, name);
        	
        	cout << "----------------------------------------------------" << endl;
            clock_t start = clock();
            agentManager.addAgent(name);
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
            cout << endl;
        }
        else if (choice == 7) {
        	// to assign automaticaly tasks to agents
        	cout << endl;
        	cout << "----------------------------------------------------" << endl;
            clock_t start = clock();
            agentManager.assignTicket(ticketManager.getPendingTicketsQueue(),&ticketManager);
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
            cout << endl;
        }
        else if (choice == 8) {
        	// to view reslog
        	cout << endl;
        	cout << "----------------------------------------------------" << endl;
            clock_t start = clock();
            ticketManager.viewResolutionLog();
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
     		cout << endl;
        }
        else if (choice == 9) {
        	// to view pending queue
			cout << endl;
        	cout << "----------------------------------------------------" << endl;
            clock_t start = clock();
            ticketManager.viewPendingQueue();
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
     		cout << endl;
        }
        else if (choice == 10) {
        	// to view load of agents
        	cout << endl;
        	cout << "----------------------------------------------------" << endl;
            clock_t start = clock();
            agentManager.viewAgentLoad(&ticketManager);
            clock_t end = clock();
            double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC; 
            cout << "Time taken by function: " << duration << endl;
            cout << "----------------------------------------------------" << endl;
     		cout << endl;
        }
        else if (choice == 11) {
        	cout << endl;
            cout << "Exiting the system" << endl;
            break;
        }
        else {
        	cout << endl;
        	ticketManager.printTickets();
            cout << "Invalid option" << endl;
        }
    }
    return 0;
}

