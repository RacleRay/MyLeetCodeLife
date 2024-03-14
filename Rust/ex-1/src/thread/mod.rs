use std::thread;

pub fn run_thread() {
    let handle = thread::spawn(|| {
        for i in 1..5 {
            println!("hi number {} from the spawned thread!", i);
            thread::sleep(std::time::Duration::from_millis(1));
        }
    });

    for i in 1..10 {
        println!("hi number {} from the main thread!", i);
        thread::sleep(std::time::Duration::from_millis(1));
    }

    handle.join().unwrap_or_default();
}