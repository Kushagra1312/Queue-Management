#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <string>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <climits>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iomanip>
using namespace std;
struct People
{
    string name; // Person Name
    int bt;      // Burst Time
    int art;     // Arrival Time
};
/////////////For Week Days of  A Normal Person////////////////
void findWaitingTime(vector<People> proc, int n, int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
    {
        rt[i] = proc[i].bt;
    }
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= t) &&
                (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false)
        {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0)
        {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time -
                           proc[shortest].bt -
                           proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
void findTurnAroundTime(vector<People> proc, int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}
void findavgTime(vector<People> proc, int n)   
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(proc, n, wt);
    cout << endl;
    findTurnAroundTime(proc, n, wt, tat);
    cout << "\nPeople "
         << " Waiting time "
         << " Total Time Needed\n";
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << proc[i].name << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage total time = "
         << (float)total_tat / (float)n;
}
///////////// END FOR NORMAL PERSON //////////////////////////

/////////////For Week Days of A Elderly Person////////////////
struct Elderly
{
    string name;  // Person Name
    int bt;       // Burst time required for the task
    int priority; // Priority of this person based on age
};
bool comparison(Elderly a, Elderly b)
{
    return (a.priority > b.priority);
}
void findWaitingTime_priority(vector<Elderly> proc, int n, int wt[])
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = proc[i - 1].bt + wt[i - 1];
}
void findTurnAroundTime_priority(vector<Elderly> proc, int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}
void findavgTime_priority(vector<Elderly> proc, int n)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime_priority(proc, n, wt);
    findTurnAroundTime_priority(proc, n, wt, tat);
    cout << "\nName  "
         << " Waiting time  "
         << " Total Time Needed \n";
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << proc[i].name << "\t \t" << wt[i]
             << "\t \t" << tat[i] << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage total  time = "
         << (float)total_tat / (float)n;
}

void priorityScheduling_priority(vector<Elderly> proc, int n)
{
    sort(proc.begin(), proc.end(), comparison);
    cout << "Order in which people are served \n";
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            cout << proc[i].name;
        }
        cout << proc[i].name << " ,";
    }
    cout << "\n";
    findavgTime_priority(proc, n);
}
//////////////////// END FOR ELDERLY /////////////////////

/////////////////// Creating a map of various services provided by bank with time quantum ////////////////////
map<string, int> Activity()
{
    map<string, int> activities;
    activities["Cash_Withdrawal"] = 1;
    activities["Acc_Opening"] = 10;
    activities["Loan"] = 8;
    activities["Insurance"] = 6;
    activities["Deposit"] = 2;
    return activities;
}
/////////////////// Creating a map of the various services provided by bank ////////////////
map<int, string> make_choice_map()
{
    map<int, string> choices;
    choices[1] = "Cash_Withdrawal";
    choices[2] = "Acc_Opening";
    choices[3] = "Loan";
    choices[4] = "Insurance";
    choices[5] = "Deposit";
    return choices;
}
int main()
{
    int num_of_people;
    map<string, int> activities = Activity();
    cout << "Enter the Number of people \n ";
    cin >> num_of_people;
    map<int, string> choices = make_choice_map();
    vector<People> person;
    vector<Elderly> elderly;
    bool check_if_elderly_present = false;
    cout << "******************************* THE FOLLOWING SERVICES ARE OFFERED BY THE BANK ******************************** \n";
    cout << "1. Cash_Withdrawal \n";
    cout << "2. Acc_Opening \n";
    cout << "3. Loan \n";
    cout << "4. Insurance \n";
    cout << "5. Deposit \n";
    cout << "***************************************************************************************************************  \n";
    cout << "\n";
    for (int i = 0; i < num_of_people; i++)
    {
        string temp_name;
        int temp_art;
        cout << "Enter Your name :\n";
        cin >> temp_name;
        int temp_age;
        cout << "Enter Your Age: \n";
        cin >> temp_age;
        if (temp_age >= 60)
        {
            check_if_elderly_present = true;
            cout << "Enter Your Purpose of Visiting (Input the Serial Number as mentioned at the starting): \n";
            int serial_no;
            cin >> serial_no;
            string acti = choices[serial_no];
            elderly.push_back({temp_name, activities[acti], temp_age});
        }
        else
        {
            cout << "Enter Your Arrival Time :\n";
            cin >> temp_art;
            cout << "Enter Your Purpose of Visiting (Input the Serial Number as mentioned at the starting): \n";
            int serial_no;
            cin >> serial_no;
            string acti = choices[serial_no];
            person.push_back({temp_name, activities[acti], temp_art});
        }
        cout << "***************************************************************************************************************  \n";
    }
    if (check_if_elderly_present)
    {
        cout << "The execution of queue for the elderly \n";
        priorityScheduling_priority(elderly, elderly.size());
        cout << "\n";
    }
    if (check_if_elderly_present == false)
    {
        cout << "There were No elderly present \n";
    }
    cout << "\n";
    cout << "The execution of queue for normal person \n";
    findavgTime(person, person.size());
    cout << "\n";
    return 0;
    }