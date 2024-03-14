// Add the 'futures' crate as a dependency
use async_std::task::{block_on, sleep, spawn};
use std::time::Duration;
use std::future::Future;



async fn func1() -> String {
    for i in 1..3 {
        println!("func 1 {}", i);
        sleep(Duration::from_millis(1000)).await;
    }
    String::from("func 1 return.")
}


fn func2() -> impl Future<Output = String> {
    async {
        let func_ret = func1().await;
        func_ret + "func 2 return."
    }
}

fn func3() -> impl Future<Output = String> {
    let ret = |x : String| async move {
        let func_ret = func2().await;
        func_ret + &*x
    };
    ret(String::from("func 3 return."))
}


#[async_std::test]
async fn run_async() {
    println!("Hello, world!");

    let res = block_on(func3());
    println!("{}", res);
}