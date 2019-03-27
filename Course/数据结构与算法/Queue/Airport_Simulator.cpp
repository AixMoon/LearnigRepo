#include <iostream>
#include <queue>
#include <unistd.h>
#include "Possion.h"
using namespace std;
typedef int feedback;
const int success = 1;
const int fail = 0;
const int ERROR_FULL = 101;
enum flightStatus{
	null,
	toLand,
	toTakeoff
};
enum runawayAct{
	idle,
	letTakeoff,
	letLand
};
string percentage(int A, int B){
	char *temp = new char[100];
	sprintf(temp, "%3.2f%%", (double)A / (double)B * 100);
	string output = temp;
	return output;
}
class Plane
{
  private:
	int ID;
	int comingTime;
	flightStatus status;
  public:
  	Plane(){
		ID = -1;
		comingTime = -1;
		status = null;
	}
	Plane(int _ID, int _comingTime, flightStatus _status){
		usleep(100000);
		ID = _ID;
		comingTime = _comingTime;
		status = _status;
		cout << "[PLANE MESSAGE] Plane NO." << ID << " approaching. Trying to " << ((status == toLand) ? "land " : "take off ") << endl;
	}
	feedback land(int currentTime){
		usleep(300000);
		cout << "[PLANE MESSAGE] Plane NO." << ID << "has landed safely." << endl
			 << "                Waiting time before landing: " << currentTime - comingTime << "." << endl;
	}
	feedback takeoff(int currentTime){
		usleep(300000);
		cout << "[PLANE MESSAGE] Plane NO." << ID << "has taken off safely." << endl
			 << "                Waiting time before taking off: " << currentTime - comingTime << "." << endl;
	}
	feedback reject(int currentTime){
		usleep(300000);
		if(status == toLand){
			cout << "[AIRPORT MESSAGE] Plane NO." << ID << "'s landing request is rejected." << endl
				 << "                  It has been directed to other airports." << endl;
		}
		else{
			cout << "[AIRPORT MESSAGE] Plane NO." << ID << " 's taking off request is rejected." << endl
				 << "                  This flight is delayed." << endl;
		}
	}
	int getTime(){
		return comingTime;
	}
};

class Runaway{
  private:
	queue<Plane> landingQueue;
	queue<Plane> takeoffQueue;
	int limit;
	runawayAct act;
	int landingRequests;
	int landingAccepted;
	int landingRejected;
	int takeoffRequests;
	int takeoffAccepted;
	int takeoffRejected;
	int idleUnit;
	int landingWaitedTime;
	int takeoffWaitedTime;

  public:
	Runaway(int _limit){
		limit = _limit;
		landingRequests = 0;
		landingAccepted = 0;
		takeoffRequests = 0;
		takeoffAccepted = 0;
		takeoffRejected = 0;
		idleUnit = 0;
		landingWaitedTime = 0;
		takeoffWaitedTime = 0;
	}
	feedback CanLand(const Plane &current){
		landingRequests++;
		feedback result;
		if (landingQueue.size() < limit){
			result = success;
			landingQueue.push(current);
		}
		else{
			result = fail;
			landingRejected++;
		}
		return result;
	}
	feedback CanTakeoff(const Plane &current){
		takeoffRequests++;
		feedback result;
		if (takeoffQueue.size() < limit){
			result = success;
			takeoffAccepted++;
			takeoffQueue.push(current);
		}
		else{
			result = fail;
			takeoffRejected++;
		}
		return result;
	}
	runawayAct Act(int timeNow, Plane &moving){
		runawayAct result;
		if (!landingQueue.empty()){
			landingAccepted++;
			moving = landingQueue.front();
			landingWaitedTime += timeNow - moving.getTime();
			landingQueue.pop();
			return letLand;
		}
		else if(!takeoffQueue.empty()){
			takeoffAccepted++;
			moving = takeoffQueue.front();
			takeoffWaitedTime += timeNow - moving.getTime();
			takeoffQueue.pop();
			return letTakeoff;
		}
		else{
			idleUnit++;
			return idle;
		}
	}
	void sumup(int simulationTime){
		cout << "=============== SIMULATION RESULTS ===============" << endl;
		sleep(1);
		cout
			<< "Total simulation time:                   " << simulationTime << endl
			<< "Total flights required to land:          " << landingRequests << endl
			<< "Landing request accepted:                " << landingAccepted << endl
			<< "Landing request rejected:                " << landingRejected << endl
			<< "Total flights required to take off:      " << takeoffRequests << endl
			<< "Taking off request accepted:             " << takeoffAccepted << endl
			<< "Taking off request rejected:             " << takeoffRejected << endl
			<< "Flights still left in landing queue:     " << landingQueue.size() << endl
			<< "Flights still left in taking off queue:  " << takeoffQueue.size() << endl
			<< "Average waiting time in landing queue:   " << (float)landingWaitedTime / (float)landingAccepted << endl
			<< "Average waiting time in taking off queue:" << (float)takeoffWaitedTime / (float)takeoffAccepted << endl
			<< "Ratio for successfully landed flights:   " << percentage(landingAccepted, landingRequests) << endl
			<< "Ratio for successfully took off flights: " << percentage(landingAccepted, landingRequests) << endl
			<< "Ratio of runaway idle time:              " << percentage(idleUnit, simulationTime) << endl;
	}
};
void initilize(int &totalTime, int &queueLimit, float &arrivingRate, float &departureRate){
	cout << "\033[42mPlease enter how many time units you will simulate:\033[0m\n"
		 << flush;
	cin >> totalTime;
	cout << "How many flights can be waiting to land or takeoff?" << endl
		 << flush;
	cin >> queueLimit;
	cout << "What is the expected arriving flights per unit time?" << endl
		 << flush;
	cin >> arrivingRate;
	cout << "What is the expected departing flights per unit time?" << endl
		 << flush;
	cin >> departureRate;
}

int main(){
	float arrivingRate, departureRate;
	int totalTime, queueLimit;
	cout << "\033[2J\033[0;0H";
	cout << "Welcome to the \033[36mAIRPORT SIMULATOR\033[0m." << endl;
	sleep(1);
	initilize(totalTime, queueLimit, arrivingRate, departureRate);
	int currentTime;
	int planeID = 0;
	Runaway airport(queueLimit);
	for (currentTime = 0; currentTime < totalTime; currentTime++){
		cout << "----- Current excution time: " << currentTime << " -----" << endl;
		int comingPerUnit = possion(arrivingRate);
		for (int num = 0; num < comingPerUnit; num++, planeID++){
			Plane currentPlane(planeID, currentTime, toLand);
			if(airport.CanLand(currentPlane)==fail){
				currentPlane.reject(currentTime);
			}
		}
		int departingPerUnit = possion(departureRate);
		for (int num = 0; num < departingPerUnit; num++, planeID++){
			Plane currentPlane(planeID, currentTime, toTakeoff);
			if(airport.CanTakeoff(currentPlane)==fail){
				currentPlane.reject(currentTime);
			}
		}
		Plane movingPlane;
		switch (airport.Act(currentTime, movingPlane)){
		case letLand:
			movingPlane.land(currentTime);
			break;
		case letTakeoff:
			movingPlane.takeoff(currentTime);
			break;
		case idle:
			cout << "[AIRPORT MESSAGE]: Runaway is idle." << endl;
			break;
		}
	}
	airport.sumup(totalTime);
	return 0;
}