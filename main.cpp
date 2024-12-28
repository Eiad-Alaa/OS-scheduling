#include <bits/stdc++.h>
using namespace std;

#include "./Algorithms/AGING.cpp"

int main()
{
  task t;
  string in;
  getline(cin, t.type);
  getline(cin, t.policy);
  getline(cin, in);
  t.len = stoi(in);
  getline(cin, in);
  t.p_count = stoi(in);
  for (int i = 0; i < t.p_count; i++)
  {
    getline(cin, in);
    process temp = init_process(split(in, ','), i);
    temp.status.resize(t.len);                        // reserve timeline for process
    t.processes.push_back(temp);
  }

  vector<string> policies = split(t.policy, ',');

  for (auto pol : policies)
  {
    task temp = t;
    temp.policy = pol;
    switch (pol[0])
    {
    case '1':
      temp = fcfs(temp);
      break;
    case '2':
      temp = rr(temp);
      break;
    case '3':
      temp = spn(temp);
      break;
    case '4':
      temp = srt(temp);
      break;
    case '5':
      temp = hrrn(temp);
      break;
    case '6':
    case '7':
      temp = fb(temp);
      break;
    case '8':
      temp = aging(temp);
      break;
    }
    if (temp.type == "stats")
      print_stats(temp);
    else
      print_trace(temp);
  }
  return 0;
}
