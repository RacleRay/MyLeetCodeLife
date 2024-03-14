pub fn add(left: usize, right: usize) -> usize {
    left + right
}


pub mod miter {
    pub fn run_iter() {
        for i in 0..10 {
            println!("{}", i);
        }

        let v = vec![1, 2, 3];
        let mut it = v.iter();
        while let Some(x) = it.next() {
            println!("{}", x);
        }

        let mut it = v.into_iter();
        while let Some(x) = it.next() {
            println!("{}", x);
        }

        let mut v_m = vec![1, 2, 3];
        let mut it = v_m.iter_mut();
        while let Some(x) = it.next() {
            println!("{}", x);
        }
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
