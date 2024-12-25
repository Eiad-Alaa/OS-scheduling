#include <bits/stdc++.h>
using namespace std;

#include "HRRN.cpp"

task fb(task t)
{
  bool fb1 = false;
  if(t.policy[0]=='6')fb1 = 1;
  int time = -1;
  vector<vector<int>> time_p(t.len + 3);

  for (auto p : t.processes)
  {
    time_p[p.arrival].push_back(p.idx);
  }

  vector<deque<process>> ready_run(t.len+2);

  while (time <= t.len)
  {
    int queue_id = first_nempty(ready_run);
    if (queue_id != -1)
    {
      process temp = ready_run[queue_id].front();
      ready_run[queue_id].pop_front();

      int rest = fb1?1:(1 << queue_id);
      
      while (temp.rem != 0 && rest != 0)
      {
        rest--;
        temp.rem--;
        temp.status[time] = '*';
        time++;
        for (auto id : time_p[time])
        {
          ready_run[0].push_back(t.processes[id]);
        }
        if (rest > 1 && !ready_run[0].empty())        
            break;
      }
      if (temp.rem == 0)
      {
        temp.finish = time;
        t.processes[temp.idx] = temp;
      }
      else if (rest == 0)
      {
        if (first_nempty(ready_run) != -1)
          ready_run[queue_id + 1].push_back(temp);
        else
          ready_run[queue_id].push_back(temp);
      }
      else
      {
        ready_run[queue_id].push_front(temp);
      }
    }
    else
    {
      time++;
      for (auto id : time_p[time])
      {
        ready_run[0].push_back(t.processes[id]);
      }
    }
  }
  return t;
}