#include <bits/stdc++.h>
using namespace std;

#include "FCFS.cpp"

task rr(task t)
{
  int time = -1;
  map<int, int> arrival_time;                     // key: time, value: process idx
  vector<string> policy_q = split(t.policy, '-'); // split 2-4 into "2", "4"
  int q = stoi(policy_q[1]);                      // get q

  for (int i = 0; i < t.p_count; i++) // save arrival time for each process
  {
    arrival_time[t.processes[i].arrival] = i;
  }

  queue<process> ready_run;

  while (time <= t.len)
  {
    if (!ready_run.empty())
    {
      process temp = ready_run.front();
      ready_run.pop();
      int rest = q;
      while (temp.rem != 0 && rest != 0)
      {
        rest--;
        temp.rem--;
        temp.status[time] = '*';
        time++;
        if (check_arrival(time, arrival_time))
          ready_run.push(t.processes[arrival_time[time]]);
      }
      if (temp.rem == 0)
      {
        temp.finish = time;
        t.processes[temp.idx] = temp;
      }
      else
      {
        ready_run.push(temp);
      }
    }
    else
    {
      time++;
      if (check_arrival(time, arrival_time))
        ready_run.push(t.processes[arrival_time[time]]);
    }
  }
  return t;
}