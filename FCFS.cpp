#include <bits/stdc++.h>
using namespace std;
#include "utilities.cpp"


// comparator based on arrival time
struct Arrival {
    bool operator()(const process& a, const process& b) {
        return a.arrival > b.arrival;
    }
};

map<int,int>arrival_time;                   // key: time, value: process idx

bool check_arrival(task t, int time)
{
     return (arrival_time.find(time) != arrival_time.end());
}

task fcfs(task t)
{
  int time = 0;
  
  for(int i = 0;i < t.p_count; i++)           // save arrival time for each process
  {
    arrival_time[t.processes[i].arrival] = i;
  }

  priority_queue<process, vector<process>, Arrival> ready_run;

  while(time <= t.len)
  {
    if(check_arrival(t,time))
      ready_run.push(t.processes[arrival_time[time]]);
    if(!ready_run.empty())
    {
      process temp = ready_run.top();
      ready_run.pop();
      while(temp.rem!=0){
        temp.rem--;
        temp.status[time] = '*';
        time++;
        if(check_arrival(t,time))
          ready_run.push(t.processes[arrival_time[time]]);
      }
      temp.finish = time;
      t.processes[temp.idx] = temp;
    }
    else time++;
  }
  return t;
}