#include <bits/stdc++.h>
using namespace std;

#include "FCFS.cpp"

task rr(task t)
{
  int time = -1;
  vector<string> policy_q = split(t.policy, '-'); // split 2-4 into "2", "4"
  int q = stoi(policy_q[1]);                      // get q
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
      int rest = q;
      while (temp.rem != 0 && rest != 0)
      {
        rest--;
        temp.rem--;
        temp.status[time] = '*';
        time++;
        for (auto id : time_p[time])
        {
          ready_run.push(t.processes[id]);
        }
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
      for (auto id : time_p[time])
      {
        ready_run.push(t.processes[id]);
      }
    }
  }
  return t;
}