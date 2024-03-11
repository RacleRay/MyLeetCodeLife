// 内存管理方法，正因此Rust不需要垃圾回收

// Rules：
// 1 Rust 中的每一个值都有一个被称为其 所有者（owner）的变量。
// 2 值在任一时刻有且只有一个所有者。
// 3 当所有者（变量）离开作用域，这个值将被丢弃。

fn main() {
    println!("Hello, world!");

    // move 而不是 shallow copy
    let s1 = String::from("Hello"); // heap上的数据
    let s2 = s1; // 此时s1将不再可用

    // clone
    let s1 = String::from("Hello");
    let s2 = s1.clone(); // deep copy

    // 而只在 stack 上的固定大小的数据
    // 比如
    //   所有整数类型，比如 u32。
    //   布尔类型，bool，它的值是 true 和 false。
    //   所有浮点数类型，比如 f64。
    //   字符类型，char。
    //   元组，当且仅当其包含的类型也都是 Copy 的时候。比如，(i32, i32) 是 Copy 的，但 (i32, String) 就不是。
    // 拷贝复制是很快的
    let v1 = 1;
    let v2 = v1;
    println!("{}, {}", v1, v2); // 成立

    // 函数调用中的变化
    let s = String::from("hello"); // s 进入作用域
    println!("s {s}");

    let ret: String = takes_ownership(s); // s 的值移动到函数里 ...
    println!("ret: {}", ret);
    // ... 所以到这里不再有效

    let x = 5;                      // x 进入作用域

    makes_copy(x);                  // x 应该移动函数里，
                                    // 但 i32 是 Copy 的，所以在后面可继续使用 x


    // 不可变引用, 可变引用
    let mut s = String::from("hello");

    let r1 = &s; // 没问题
    let r2 = &s; // 没问题
    println!("{}, {}", r1, r2);
    // 不可变引用 r1 和 r2 的作用域在 println! 最后一次使用之后结束
    // 所以可以使用可变引用

    let r3 = &mut s; // 不能同时用两个可变引用
    println!("{}", r3);
}


fn takes_ownership(s: String) -> String {
    println!("take_ownership");

    let some_string = String::from("hello"); // some_string 进入作用域.

    some_string                              // 返回 some_string 并移出给调用的函数
}

fn makes_copy(x: i32) {
    println!("makes_copy");
}

fn cal_len(s: &String) -> usize {  // 传入引用，那么 s 的所有权不会改变，上一层函数仍能使用。
    s.len()  // （默认）不允许修改引用的值
}

fn change(s: &mut String) {  // 传入引用，那么 s 的所有权不会改变，上一层函数仍能使用。
    s.push_str("！");  // （默认）不允许修改引用的值
}

// Rust直接会指出 孤儿指针(悬垂指针)的存在
// 错误示范：
// fn dangle() -> &String { // dangle 返回一个字符串的引用

//     let s = String::from("hello"); // s 是一个新字符串

//     &s // 返回字符串 s 的引用
// } // 这里 s 离开作用域并被丢弃。其内存被释放。
//   // 危险！

// 正确
fn no_dangle() -> String {
    let s = String::from("hello");

    s
}