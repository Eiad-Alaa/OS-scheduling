#include <bits/stdc++.h>
using namespace std;

#include "SPN.cpp"

struct Shortest
{
  bool operator()(const process &a, const process &b)
  {
    return (a.rem > b.rem || (a.rem == b.rem && a.arrival > b.arrival));
  }
};

task srt(task t)
{
  int time = -1;
  map<int, int> arrival_time;         // key: time, value: process idx
  for (int i = 0; i < t.p_count; i++) // save arrival time for each process
  {
    arrival_time[t.processes[i].arrival] = i;
  }

  priority_queue<process, vector<process>, Shortest> ready_run;

  while (time <= t.len)
  {
    if (!ready_run.empty())
    {
      process temp = ready_run.top();
      ready_run.pop();
      temp.rem--;
      temp.status[time] = '*';
      time++;
      if (check_arrival(time, arrival_time))
        ready_run.push(t.processes[arrival_time[time]]);
      if (temp.rem == 0)
      {
        temp.finish = time;
        t.processes[temp.idx] = temp;
      }
      else
        ready_run.push(temp);
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