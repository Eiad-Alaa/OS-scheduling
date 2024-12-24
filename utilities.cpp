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


int turnaround(process &p)
{
  return p.finish - p.arrival;
}

float norm_turn(process &p)
{
  float value = turnaround(p) / (float)p.service;
  return round(value * 100) / 100;
}


int dcmp(double a, double b)
{
    return fabs(a - b) <= 1e-9 ? 0 : a < b ? -1: 1;
}

vector<string> split(string s, char delimiter)
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

void print_trace(task &t)
{
  cout << left<< setw(6) << algo[(t.policy[0] - '1')];
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
    cout << "|" << endl;
  }
  cout << string(t.len * 2 + 8, '-') << endl;
  cout<<"\n\n";
}

void print_stats(task &t)
{
    cout << algo[(t.policy[0] - '1')] << endl;
    cout << "Process    |";
    for (auto p : t.processes) {
        cout << "  " << p.name << "  |";
    }
    cout << "\n";


    cout << "Arrival    |";
    for (auto p : t.processes) {
        cout << setw(3) << p.arrival << "  |";
    }
    cout << "\n";

        cout << "Service    |";
    for (auto p : t.processes) {
        cout << setw(3) << p.service << "  |";
    }
    cout << " Mean|\n";

        cout << "Finish     |";
    for (auto p : t.processes) {
        cout << setw(3) << p.finish << "  |";
    }
    cout << "-----|\n";

    double mean_turnaround = 0;
    cout << "Turnaround |";
    for (auto p : t.processes) {
        cout << setw(3) << turnaround(p) << "  |";
        mean_turnaround+=turnaround(p);
    }
    mean_turnaround/=t.p_count;
    cout << fixed << setprecision(2) << setw(5) << mean_turnaround << "|" << endl;

    double mean_norm = 0;
    cout << "NormTurn   |";
    for (auto p : t.processes) {
        cout << setw(5) << norm_turn(p) << "|";
        mean_norm+=norm_turn(p);
    }
    mean_norm/=t.p_count;
    cout << fixed << setprecision(2) << setw(5) << mean_norm << "|" << endl;
    cout<<"\n\n";
}


void print_task(task &t) {
    cout << "Type: " << t.type << endl;
    cout << "Policy: " << t.policy << endl;
    cout << "Timeline Length: " << t.len << endl;
    cout << "Process Count: " << t.p_count << endl;

    cout << "Processes:\n";
    cout << "-----------------------------------------------\n";
    cout << "Idx | Name | Arrival | Service | Finish | Rem\n";
    cout << "-----------------------------------------------\n";
    for (auto p : t.processes) {
        cout << setw(3) << p.idx << " | "
             << setw(4) << p.name << " | "
             << setw(7) << p.arrival << " | "
             << setw(7) << p.service << " | "
             << setw(6) << p.finish << " | "
             << setw(3) << p.rem << "\n";
    }
    cout << "-----------------------------------------------\n";
}