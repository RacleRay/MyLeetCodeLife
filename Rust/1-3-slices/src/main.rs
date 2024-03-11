fn main() {
    let my_string: String = String::from("hello world");
    println!("Begin with string : {my_string}. ");

    // first_word 中传入 `String` 的 slice
    let word = first_word(&my_string[..]);
    println!("first slice : {word}. ");

    // 字符串字面值就是 slice
    let my_string_literal: &str = "hello world";

    // first_word 中传入字符串字面值的 slice
    let word: &str = first_word(&my_string_literal[..]);
    println!("slice from literal slice : {word}. ");

    // 因为字符串字面值 **就是** 字符串 slice，
    // 这样写也可以，即不使用 slice 语法！
    let word: &str = first_word(my_string_literal);
    println!("slice from literal string : {word}. ");
}

fn first_word(s: &str) -> &str {  // s: &str 可同时接收 String 值和 &str 值
    // “字符串 slice” 的类型声明写作 &str
    let bytes: &[u8] = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}

// write a function to test rust slice
fn test_slice() {
    let s = String::from("hello world");
    let hello = &s[0..5];
    let world = &s[6..11];
    println!("hello: {hello}, world: {world}. ");
}


// write a function to generate a random number
fn test_rand() {
    use rand::Rng;
    let mut rng = rand::thread_rng();
    let random_number: u8 = rng.gen();
    println!("random number: {random_number}. ");
}

