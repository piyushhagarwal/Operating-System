struct Task{
    name : String,
    arrival_time : i32,
    burst_time : i32,
    waiting_time : i32,
    completion_time : i32,
    turnaround_time : i32
}

impl Task{
    fn new(name: String, arrival_time: i32, burst_time: i32) -> Self {
        Task {
            name,
            arrival_time,
            burst_time,
            waiting_time: 0,
            completion_time: 0,
            turnaround_time: 0,
        }
    }
}

fn FCFS(task_vector :&mut Vec<Task>){
    //sort on the basis of arrival time
    task_vector.sort_by_key(|task| task.arrival_time);

    let mut current_time = 0;
    for task in task_vector.iter_mut(){
        task.completion_time = current_time + task.burst_time;
        task.waiting_time = current_time - task.arrival_time;
        task.turnaround_time = task.completion_time - task.arrival_time;
        current_time = task.completion_time;
    }

    for task in task_vector.iter(){
        println!("name-{} burst time-{} arrival time-{} waiting time-{} completion time-{} turn around time-{}",task.name,task.burst_time,task.arrival_time,task.waiting_time,task.completion_time,task.turnaround_time);
    }
}

fn RR(task_vector :&mut Vec<Task>){
    //sort on the basis of arrival time
    task_vector.sort_by_key(|task| task.arrival_time);

    
}

fn main() {
    let task1 = Task::new("Task1".to_string(), 5, 10);
    let task2 = Task::new("Task2".to_string(), 0, 4);
    let task3 = Task::new("Task3".to_string(), 4, 11);
    let mut task_vector = vec![task1,task2,task3];
    FCFS(&mut task_vector);
}
