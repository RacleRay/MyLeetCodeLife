use data_structure::Stack;

fn move_n_2_tower(n: i32, from: &mut Stack<i32>, to: &mut Stack<i32>, mid: &mut Stack<i32>) {
    if n >= 1 {
        move_n_2_tower(n - 1, from, mid, to);
        to.push(from.pop().unwrap());
        move_n_2_tower(n - 1, mid, to, from);
    }
}

fn main() {
    let mut from = Stack::new();
    from.push(4);
    from.push(3);
    from.push(2);
    from.push(1);
    let mut to = Stack::new();
    let mut mid = Stack::new();

    println!("from {:?}", from);
    println!("to {:?}", to);
    println!("mid {:?}", mid);

    move_n_2_tower(from.size() as i32, &mut from, &mut to, &mut mid);

    println!("--- after move_n_2_tower ---");
    println!("from {:?}", from);
    println!("to {:?}", to);
    println!("mid {:?}", mid);
}
