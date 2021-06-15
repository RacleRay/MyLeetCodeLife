use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    let secret_number = rand::thread_rng().gen_range(1..11);

    println!("猜一个数，0到10直接的：");

    loop{
        println!("输入：");
        let mut guess=String::new();
        io::stdin().read_line(&mut guess).expect("未输入有效数字");

        let guess: u32=match guess.trim().parse(){
            Ok(num) => num,
            Err(_)=>continue,
        };

        println!("你的输入是, {}", guess);

        match guess.cmp(&secret_number){
            Ordering::Less=>println!("过小"),
            Ordering::Greater=>println!("过大"),
            Ordering::Equal=>{
                println!("猜对了");
                break;
            }
        }
    }

}