#include <bits/stdc++.h>
using namespace std;

#include "RR.cpp"

struct Service
{
  bool operator()(const process &a, const process &b)
  {
    return (a.service > b.service || (a.service == b.service && a.arrival > b.arrival));
  }
};

task spn(task t)
{
  int time = -1;
  vector<vector<int>> time_p(t.len + 3);

  for (auto p : t.processes)
  {
    time_p[p.arrival].push_back(p.idx);
  }
  priority_queue<process, vector<process>, Service> ready_run;

  while (time <= t.len)
  {
    if (!ready_run.empty())
    {
      process temp = ready_run.top();
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