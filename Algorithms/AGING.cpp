#include <bits/stdc++.h>
using namespace std;

#include "FB.cpp"

struct AGE
{
  bool operator()(const process &a, const process &b)
  {
    return a.priority > b.priority || (a.priority == b.priority && a.arrival < b.arrival);
  }
};

task aging(task t)
{
  vector<vector<int>> time_p(t.len + 3);
  int time = -1;
  for (auto p : t.processes)
  {
    time_p[p.arrival].push_back(p.idx);
  }

  deque<process> ready_run;

  while (time <= t.len)
  {
    if (!ready_run.empty())
    {
      sort(ready_run.begin(), ready_run.end(), AGE());

      process temp = ready_run[0];
      ready_run.pop_front();
      // cout << time << " ---> " << temp.name << ": " << temp.priority << "\n";
      temp.status[time] = '*';
      time++;
      temp.arrival = time;
      temp.priority = t.processes[temp.idx].priority;           //restore original priority
      for (auto id : time_p[time])
      {
        ready_run.push_back(t.processes[id]);
      }
      for(auto &p : ready_run)                                  // increment priority of all ready processes
      {
        p.priority++;
      }
      ready_run.push_back(temp);
    }
    else
    {
      time++;
      for (auto id : time_p[time])
      {
        ready_run.push_back(t.processes[id]);
      }
    }
  }
  for (auto p : ready_run)
  {
    t.processes[p.idx].status = p.status;
  }
  return t;
}
