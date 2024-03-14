pub fn run_closure() {
    let add = |x: i32, y: i32| -> i32 { x + y };
    println!("5 + 4 = {}", add(5, 4));

    let v = 3;
    let add = |x: i32, y: i32| -> i32 { x + y + v };
    println!("5 + 4 = {}", add(5, 4));
}