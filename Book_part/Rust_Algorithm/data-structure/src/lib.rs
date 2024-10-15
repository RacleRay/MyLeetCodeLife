pub mod linkvec;
pub mod linkstack;
pub mod deque;
pub mod linklist;
pub mod queue;
pub mod stack;
pub use stack::Stack;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_stack() {
        let mut s = Stack::new();

        s.push(1);
        s.push(2);
        s.push(3);

        assert_eq!(s.peek(), Some(&3));
        assert_eq!(s.is_empty(), false);
        assert_eq!(s.size(), 3);
        assert_eq!(s.pop(), Some(3));
        assert_eq!(s.pop(), Some(2));
        assert_eq!(s.size(), 1);
        assert_eq!(s.pop(), Some(1));
        assert_eq!(s.pop(), None);
        assert_eq!(s.size(), 0);
        assert_eq!(s.is_empty(), true);
    }

    #[test]
    fn test_linklist() {
        let mut list = linklist::List::new();
        list.push(1);
        list.push(2);
        list.push(3);
        assert_eq!(list.pop(), Some(3));
        assert_eq!(list.pop(), Some(2));
        assert_eq!(list.pop(), Some(1));

        list.push(4);
        list.push(5);

        assert_eq!(list.peek(), Some(&5));
        assert_eq!(list.peek_mut(), Some(&mut 5));

        let mut iter = list.iter();
        assert_eq!(iter.next(), Some(&5));
        assert_eq!(iter.next(), Some(&4));
        assert_eq!(iter.next(), None);

        let mut iter = list.iter_mut();
        assert_eq!(iter.next(), Some(&mut 5));
        assert_eq!(iter.next(), Some(&mut 4));
        assert_eq!(iter.next(), None);

        let mut iter = list.into_iter();
        assert_eq!(iter.next(), Some(5));
        assert_eq!(iter.next(), Some(4));
        assert_eq!(iter.next(), None);
    }
}
