#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class Task
{

public:
    string name;
    int arrival_time, burst_time, waiting_time, completion_time, turnaround_time, priority;

    Task()
    {
        name = " ";
        arrival_time = 0;
        burst_time = 0;
        waiting_time = 0;
        completion_time = 0;
        turnaround_time = 0;
        priority = 0;
    }

    Task(string n, int b_time, int a_time, int p)
    {
        name = n;
        arrival_time = a_time;
        burst_time = b_time;
        waiting_time = 0;
        completion_time = 0;
        turnaround_time = 0;
        priority = p;
    }
};

class Scheduling
{

public:
    Task *arr;
    int n;
    float sum_waiting = 0, sum_turnaround = 0;

    Scheduling()
    {
        get_inputs();
    }

    void selectionSort_FCFS(Task arr[], int n)
    {
        int i, j, min_idx;

        // One by one move boundary of
        // unsorted subarray
        for (i = 0; i < n - 1; i++)
        {

            // Find the minimum element in
            // unsorted array
            min_idx = i;
            for (j = i + 1; j < n; j++)
            {
                if (arr[j].arrival_time < arr[min_idx].arrival_time)
                    min_idx = j;
            }

            // Swap the found minimum element
            // with the first element
            if (min_idx != i)
                swap(arr[min_idx], arr[i]);
        }
    }

    void selectionSort_SJF(Task arr[], int n)
    {
        int i, j, min_idx;

        // One by one move boundary of
        // unsorted subarray
        for (i = 0; i < n - 1; i++)
        {

            // Find the minimum element in
            // unsorted array
            min_idx = i;
            for (j = i + 1; j < n; j++)
            {
                if (arr[j].burst_time < arr[min_idx].burst_time)
                    min_idx = j;
            }

            // Swap the found minimum element
            // with the first element
            if (min_idx != i)
                swap(arr[min_idx], arr[i]);
        }
    }

    void selectionSort_priority(Task arr[], int n)
    {
        int i, j, min_idx;

        // One by one move boundary of
        // unsorted subarray
        for (i = 0; i < n - 1; i++)
        {

            // Find the minimum element in
            // unsorted array
            min_idx = i;
            for (j = i + 1; j < n; j++)
            {
                if (arr[j].priority > arr[min_idx].priority)
                    min_idx = j;
            }

            // Swap the found minimum element
            // with the first element
            if (min_idx != i)
                swap(arr[min_idx], arr[i]);
        }
    }

    void get_inputs()
    {
        cout << "Enter number of tasks" << endl;
        cin >> n;
        arr = new Task[n];
        for (int i = 0; i < n; i++)
        {
            string name;
            int b_time;
            int a_time;
            int p;
            cout << "Enter name" << endl;
            cin >> name;
            cout << "Enter burst time" << endl;
            cin >> b_time;
            cout << "Enter arrival time" << endl;
            cin >> a_time;
            cout << "Enter priority time" << endl;
            cin >> p;
            Task t(name, b_time, a_time, p);
            arr[i] = t;
        }
    }

    void calculations(Task arr[])
    {
        for (int i = 0; i < n; i++)
        {

            if (i == 0)
            {
                arr[0].waiting_time = 0;
                arr[0].completion_time = arr[0].burst_time;
                arr[0].turnaround_time = arr[0].completion_time - arr[0].arrival_time;
                sum_waiting += arr[0].waiting_time;
                sum_turnaround += arr[0].turnaround_time;
                cout << arr[0].name << " waiting time " << arr[0].waiting_time << " completion time " << arr[0].completion_time << " turnaround time " << arr[0].turnaround_time << endl;
            }
            else
            {
                arr[i].completion_time = arr[i - 1].completion_time + arr[i].burst_time;
                arr[i].waiting_time = arr[i - 1].completion_time - arr[i].arrival_time;
                arr[i].turnaround_time = arr[i].completion_time - arr[i].arrival_time;
                sum_waiting += arr[i].waiting_time;
                sum_turnaround += arr[i].turnaround_time;
                cout << arr[i].name << " waiting time " << arr[i].waiting_time << " completion time " << arr[i].completion_time << " turnaround time " << arr[i].turnaround_time << endl;
            }
        }
        cout << "Avg waiting time is " << sum_waiting / n << endl;
        cout << "Avg turnaround time is " << sum_turnaround / n << endl;
    }

    void FCFS()
    {
        selectionSort_FCFS(arr, n);
        cout << "\nFCFS\n"
             << endl;
        calculations(arr);
    }

    void priority()
    {
        selectionSort_SJF(arr, n);
        for (int i = 0; i < n; i++)
        {
            arr[i].arrival_time = 0;
        }
        cout << "\npriority\n"
             << endl;
        calculations(arr);
    }

    void RR()
    {
        selectionSort_FCFS(arr, n);
        queue<int> ready_state;
        int quantum_time = 3;
        int prev_current_time = 0;
        int current_time = 0;
        ready_state.push(0);
        while (!ready_state.empty())
        {
            int task = ready_state.front();
            ready_state.pop();
            if (arr[task].burst_time == quantum_time)
            {
                arr[task].burst_time = 0;
                prev_current_time = current_time;
                current_time += quantum_time;
            }

            else if (arr[task].burst_time > quantum_time)
            {
                arr[task].burst_time -= quantum_time;
                prev_current_time = current_time;
                current_time += quantum_time;
            }
            else
            {
                prev_current_time = current_time;
                current_time += arr[task].burst_time;
                arr[task].burst_time = 0;
            }

            // If some process has arrived when this process was executing,
            //  insert them into the queue.
            for (int i = 1; i < n; i++)
            {
                if (arr[i].burst_time > 0 && arr[i].arrival_time <= current_time && arr[i].arrival_time > current_time - quantum_time)
                {
                    ready_state.push(i);
                }
            }

            // If the current process has burst time remaining,
            // push the process into the queue again.
            if (0 < arr[task].burst_time)
            {
                ready_state.push(task);
            }
            else
            {
                arr[task].completion_time = current_time;
                arr[task].turnaround_time = arr[task].completion_time - arr[task].arrival_time;
                arr[task].waiting_time = prev_current_time - arr[task].arrival_time;
            }
        }
        int sumTurnaround = 0;
        int sumWaiting = 0;

        for (int i = 0; i < n; i++)
        {
            cout << arr[i].name << " waiting time " << arr[i].waiting_time << " completion time " << arr[i].completion_time << " turnaround time " << arr[i].turnaround_time << endl;
            sumTurnaround += arr[i].turnaround_time;
            sumWaiting += arr[i].waiting_time;
        }

        cout << "Avg waiting time is " << sumWaiting / n << endl;
        cout << "Avg turnaround time is " << sumTurnaround / n << endl;
    }

    void SJF()
    {
        int current_time = 0;
        int completed_task = 0;
        int min_burst_time = INT_MAX;
        int shortest_task_index = 0;
        while (completed_task != n)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i].arrival_time <= current_time && arr[i].burst_time < min_burst_time && arr[i].burst_time > 0)
                {
                    shortest_task_index = i;
                    min_burst_time = arr[i].burst_time;
                }
            }
            arr[shortest_task_index].burst_time--;
            min_burst_time = arr[shortest_task_index].burst_time;
            if (min_burst_time == 0)
            {
                min_burst_time = INT_MAX;
            }

            if (arr[shortest_task_index].burst_time == 0)
            {
                completed_task++;
                arr[shortest_task_index].completion_time = current_time + 1;
                arr[shortest_task_index].waiting_time = arr[shortest_task_index].completion_time - arr[shortest_task_index].arrival_time - 1;
                arr[shortest_task_index].turnaround_time = arr[shortest_task_index].completion_time - arr[shortest_task_index].arrival_time;
            }
            current_time++;
        }

        int sumTurnaround = 0;
        int sumWaiting = 0;

        for (int i = 0; i < n; i++)
        {
            cout << arr[i].name << " waiting time " << arr[i].waiting_time << " completion time " << arr[i].completion_time << " turnaround time " << arr[i].turnaround_time << endl;
            sumTurnaround += arr[i].turnaround_time;
            sumWaiting += arr[i].waiting_time;
        }

        cout << "Avg waiting time is " << sumWaiting / n << endl;
        cout << "Avg turnaround time is " << sumTurnaround / n << endl;
    }
};

int main()
{
    Scheduling s;
    // s.FCFS();
    // s.SJF();
    // s.priority();
    // s.RR();
    s.SJF();

    return 0;
}
