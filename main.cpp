#include <bits/stdc++.h>
using namespace std;


#include "FCFS.cpp"


int main(int argc, char const *argv[])
{
  task t;
  string in;
  getline(cin,t.type);
  getline(cin, t.policy);
  getline(cin, in);
  t.len = stoi(in);
  getline(cin, in);
  t.p_count = stoi(in);
  for(int i = 0;i<t.p_count;i++){
    getline(cin, in);
    process temp = init_process(split(in, ','),i);
    temp.status.resize(t.len);                      //reserve timeline for process
    t.processes.push_back(temp);
  }
  

  switch(t.policy[0]) {
    case '1':
      t = fcfs(t);
      break;
    case '2':
      //t = rr(t)
      break;
    case '3':
      //t = spn(t)
      break;
    case '4':
      //t = srt(t)
      break;
    case '5':
      //t = hrrn(t)
      break;
    case '6':
      //t = fb1(t)
      break;
    case '7':
      //t = fb2i(t)
      break;
    case '8':
      //t = aging(t)
      break;
  }

  print_trace(t);

  return 0;
}
