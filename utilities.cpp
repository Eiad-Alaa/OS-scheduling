#include <bits/stdc++.h>
using namespace std;

string algo[8] = {"FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "Aging"};  // for printing purposes

typedef struct
{
  int idx;             // process index in task
  char name;
  int arrival;         // arrival time
  int service;         // total service time
  int finish;          // finish time
  int rem;             // remaining service time
  int priority;        // for aging algorithm
  vector<char> status; // process status ('.')ready, ('*')running
} process;

typedef struct
{
  string type;                  // trace or stats
  string policy;                // algorithm
  int len;                      // total time
  int p_count;                  // process count per task  
  vector<process> processes;    
} task;

int turnaround(process &p)
{
  return p.finish - p.arrival;
}

float norm_turn(process &p)
{
  float value = turnaround(p) / (float)p.service;
  return round(value * 100) / 100;
}


int dcmp(double a, double b)                      // comparing doubles avoiding floating error
{
  return fabs(a - b) <= 1e-9 ? 0 : a < b ? -1: 1;
}

vector<string> split(string s, char delimiter)    // split string into strings
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

process init_process(vector<string> line, int index)  // initialize a given process
{
  process temp;
  temp.idx = index;
  temp.name = line[0][0];
  temp.arrival = stoi(line[1]);
  temp.finish = INT_MAX;
  temp.service = stoi(line[2]);
  temp.rem = stoi(line[2]);
  temp.priority = stoi(line[2]);  //for aging algorithm input format
  return temp;
}

int first_nempty(vector<deque<process>> &stages)    // get the first non empty deque for feedback algorithm
{
  int idx = -1;
  for (int i = 0; i < stages.size(); i++)
  {
    if (!stages[i].empty())
    {
      idx = i;
      break;
    }
  }
  return idx;
}

void print_trace(task &t)
{
  int t_num = (t.policy[0] - '1');
  string algorithm = algo[t_num];
  if (t_num == 1)
  {
    vector<string> ret = split(t.policy, '-');
    algorithm += ret[1];
  }
  cout << left << setw(6) << algorithm;
  for (int i = 0; i <= t.len; ++i)
  {
    cout << (i % 10) << " ";
  }
  cout << endl;
  cout << string(t.len * 2 + 8, '-') << endl;
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
    cout << "| " << endl;
  }
  cout << string(t.len * 2 + 8, '-') << endl;
  cout << "\n";
}

void print_stats(task &t)
{
  int t_num = (t.policy[0] - '1');
  string algorithm = algo[t_num];
  if (t_num == 1)
  {
    vector<string> ret = split(t.policy, '-');
    algorithm += ret[1];
  }
  cout << algorithm << endl;
  cout << "Process    |";
  for (auto p : t.processes)
  {
    cout << "  " << p.name << "  |";
  }
  cout << "\n";

  cout << "Arrival    |";
  for (auto p : t.processes)
  {
    cout << setw(3) << right << p.arrival << "  |";
  }
  cout << "\n";

  cout << "Service    |";
  for (auto p : t.processes)
  {
    cout << setw(3) << right << p.service << "  |";
  }
  cout << " Mean|\n";

  cout << "Finish     |";
  for (auto p : t.processes)
  {
    cout << setw(3) << right << p.finish << "  |";
  }
  cout << "-----|\n";

  double mean_turnaround = 0;
  cout << "Turnaround |";
  for (auto p : t.processes)
  {
    cout << setw(3) << right << turnaround(p) << "  |";
    mean_turnaround += turnaround(p);
  }
  mean_turnaround /= t.p_count;
  cout << fixed << setprecision(2) << setw(5) << mean_turnaround << "|" << endl;

  double mean_norm = 0;
  cout << "NormTurn   |";
  for (auto p : t.processes)
  {
    cout << setw(5) << norm_turn(p) << "|";
    mean_norm += norm_turn(p);
  }
  mean_norm /= t.p_count;
  cout << fixed << setprecision(2) << setw(5) << mean_norm << "|" << endl;
  cout << "\n";
}