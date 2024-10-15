use data_structure::Stack;

const BASESTR: [&str; 16] = [
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f",
];

fn num2str(num: i32, base: i32) -> String {
    if num < base {
        BASESTR[num as usize].to_string()
    } else {
        num2str(num / base, base) + BASESTR[(num % base) as usize]
    }
}

fn num2str_stack(mut num: i32, base: i32) -> String {
    let mut stack = Stack::new();

    while num > 0 {
        if num < base {
            stack.push(num);
        } else {
            stack.push(num % base);
        }
        num /= base;
    }

    let mut num_str = String::new();
    while !stack.is_empty() {
        num_str += BASESTR[stack.pop().unwrap() as usize];
    }

    num_str
}

fn main() {
    let num = 100;

    let sb = num2str(num, 2);
    let so = num2str(num, 8);
    let sh = num2str(num, 16);

    println!("num 100 to binary: {}", sb);
    println!("num 100 to octal: {}", so);
    println!("num 100 to hex: {}", sh);

    assert_eq!(sb, num2str_stack(num, 2));
    assert_eq!(so, num2str_stack(num, 8));
    assert_eq!(sh, num2str_stack(num, 16));
}
