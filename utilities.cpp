#include <bits/stdc++.h>
using namespace std;

string algo[8] = {"FCFS", "RR", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "Aging"};

typedef struct
{
  int idx; // process index in task
  char name;
  int arrival;         // arrival time
  int service;         // total service time
  int finish;          // finish time
  int rem;             // remaining service time
  vector<char> status; // process status ('.')ready, ('*')running
} process;

typedef struct
{
  string type;
  string policy;
  int len;
  int p_count;
  vector<process> processes;
} task;

void print_trace(task t)
{
  cout << algo[(t.policy[0] - '1')] << "  ";
  for (int i = 0; i <= t.len; ++i)
  {
    cout << (i % 10) << " ";
  }
  cout << endl;
  cout << string(t.len * 2 + 5, '-') << endl;
  for (const auto &p : t.processes)
  {
    cout << p.name << "     ";
    for (int i = 0; i < t.len; i++)
    {
      cout << "|";
      if (i >= p.arrival && i < p.finish)
        (p.status[i] == '*') ? cout << '*' : cout << '.';
      else
        cout << ' ';
    }
    cout << "|" << endl;
  }
  cout << string(t.len * 2 + 5, '-') << endl;
}

void print_stats(task t)
{
}

int turnaround(process p)
{
  return p.finish - p.arrival;
}

float norm_turn(process p)
{
  float value = turnaround(p) / (float)p.service;
  return round(value * 100) / 100;
}

vector<string> split(const string &s, char delimiter)
{
  vector<string> tokens;
  stringstream ss(s);
  string token;
  while (getline(ss, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

process init_process(vector<string> line, int index)
{
  // for(int i = 0;i<line.size();i++)cout<<line[i]<<"---";
  process temp;
  temp.idx = index;
  temp.name = line[0][0];
  temp.arrival = stoi(line[1]);
  temp.finish = -1;
  temp.service = stoi(line[2]);
  temp.rem = stoi(line[2]);
  return temp;
}