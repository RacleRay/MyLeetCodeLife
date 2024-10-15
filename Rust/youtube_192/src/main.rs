use std::borrow::Cow;

fn return_slice_or_vec<'cow>(input: &'cow [i32]) -> Cow<'cow, [i32]> {
    match input.len() {
        0..=5 => Cow::Owned(input.to_vec()),
        _ => Cow::Borrowed(input),
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_return_slice_or_vec() {
        assert_eq!(
            return_slice_or_vec(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]),
            Cow::<'_, [i32]>::Owned(vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
        );
        assert_eq!(
            return_slice_or_vec(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]),
            Cow::Borrowed(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11])
        );
        assert_eq!(
            return_slice_or_vec(&[1, 2, 3]),
            Cow::<'_, Vec<i32>>::Owned(vec![1, 2, 3])
        );
    }
}
