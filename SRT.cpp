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
  vector<vector<int>> time_p(t.len + 3);

  for (auto p : t.processes)
  {
    time_p[p.arrival].push_back(p.idx);
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
      for (auto id : time_p[time])
      {
        ready_run.push(t.processes[id]);
      }
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
      for (auto id : time_p[time])
      {
        ready_run.push(t.processes[id]);
      }
    }
  }
  return t;
}