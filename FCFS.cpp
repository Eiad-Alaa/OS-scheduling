#include <bits/stdc++.h>
using namespace std;
#include "utilities.cpp"

task fcfs(task t)
{
  int time = -1;
  vector<vector<int>> time_p(t.len + 3);

  for (auto p : t.processes)
  {
    time_p[p.arrival].push_back(p.idx);
  }

  queue<process> ready_run;

  while (time <= t.len)
  {
    if (!ready_run.empty())
    {
      process temp = ready_run.front();
      ready_run.pop();
      while (temp.rem != 0)
      {
        temp.rem--;
        temp.status[time] = '*';
        time++;
        for (auto id : time_p[time])
        {
          ready_run.push(t.processes[id]);
        }
      }
      temp.finish = time;
      t.processes[temp.idx] = temp;
    }
    else
    {
      time++;
      for (auto id : time_p[time])
      {
        ready_run.push(t.processes[id]);
      }
    }
  }
  return t;
}