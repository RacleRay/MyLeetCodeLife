pub fn add(left: usize, right: usize) -> usize {
    left + right
}


pub mod mfile {
    use std::{fs::OpenOptions, io::{Read, Write}};

    pub fn run_file() {
        let file = std::fs::File::open("data.txt");
        println!("{:?}", file);
    
        // println!("Hello, world!");
    
        let file = std::fs::File::create("data2.txt").expect("create failed");
        println!("{:?}", file);
    
        std::fs::remove_file("data2.txt").expect("remove failed");
        
        
        let mut file = OpenOptions::new()
            .append(true)
            .open("data.txt")
            .expect("open failed");
        file.write("hello again".as_bytes()).expect("write failed");
    
        file.write_all("\nhello again".as_bytes()).expect("write failed");
        file.write_all("hello again".as_bytes()).expect("write failed");
        println!("write success!");
    
    
        let mut file = std::fs::File::open("data.txt").unwrap();
        let mut contents = String::new();
        file.read_to_string(&mut contents).unwrap();
        println!("{}", contents);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
