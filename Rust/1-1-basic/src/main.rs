fn main() {
    println!("Hello, world!");


    // 变量默认不可变
    // 加上 mut 变为可变变量
    let mut x = 5;
    println!("Value is {}", x);
    x = 10;
    println!("Value is {}", x);


    // 常量定义使用 const
    // 不能作为函数结果
    const MAX_VALUE: u32 = 100_000_000;


    // 变量的重复定义，视为 隐藏 shadowing
    // 可以变换类型
    let spaces = "   ";
    let spaces = spaces.len();
    // 但是 mut 的变量，不能变换类型
    // let mut spaces="   ";
    // spaces=spaces.len();  // BUG


    // ################################################
    // 元组 数组
    let x: (i32, f32, u8, bool) = (100, 3.14, 6, false);
    let a: [u8; 5] = [1, 2, 3, 4, 5];

    let first_v = x.0;
    let first_a = a[0];

    // for
    for ele in a.iter() {
        println!("array value is {}", ele);
    }
    println!("");

    for num in (1..5).rev() {
        println!("For range {}", num);
    }
    println!("");


    // function
    let x = plus_one(5);
    println!("The value of x is: {}", x);
}


fn plus_one(x: u8) -> u8 {
    let mut cc = 0;
    let test_v = loop{
        cc += 1;
        if  cc == 3 {
            break cc - 1;
        }
        else if cc < 3{
            println!("Looping...")
        }
    };
    // 没有分号
    x + test_v
}
