#include <bits/stdc++.h>
using namespace std;

#include "SRT.cpp"

int htime = -1;

double hrrn_ratio(process p)
{
  double wait = htime - (double)p.arrival;
  double ratio = (wait / p.service) + 1;
  return ratio;
}

struct Ratio
{
  bool operator()(const process &a, const process &b)
  {
    int cmp = dcmp(hrrn_ratio(a), hrrn_ratio(b));
    // cout<<htime<<" --> "<<a.name<<" "<<hrrn_ratio(a)<<"---"<<b.name<<" "<<hrrn_ratio(b)<<"\n";
    return (cmp==1?true:(cmp==-1?false:a.arrival > b.arrival));
  }
};

task hrrn(task t)
{
  map<int, int> arrival_time;         // key: time, value: process idx
  for (int i = 0; i < t.p_count; i++) // save arrival time for each process
  {
    arrival_time[t.processes[i].arrival] = i;
  }

  deque<process> ready_run;

  while (htime <= t.len)
  {
    if (!ready_run.empty())
    {
      sort(ready_run.begin(), ready_run.end(), Ratio());
      process temp = ready_run[0];
      ready_run.pop_front();
      while (temp.rem != 0)
      {
        temp.rem--;
        temp.status[htime] = '*';
        htime++;
        if (check_arrival(htime, arrival_time))
          ready_run.push_back(t.processes[arrival_time[htime]]);
      }
      temp.finish = htime;
      t.processes[temp.idx] = temp;
    }
    else
    {
      htime++;
      if (check_arrival(htime, arrival_time))
        ready_run.push_back(t.processes[arrival_time[htime]]);
    }
  }
  return t;
}