use std::fmt::Debug;

#[derive(Debug)]
pub struct Node<T> {
    data: T,
    next: Link<T>,
}

type Link<T> = Option<Box<Node<T>>>;

impl<T> Node<T> {
    pub fn new(data: T) -> Self {
        Node { data, next: None }
    }
}

#[derive(Debug)]
pub struct LinkVec<T> {
    size: usize,
    head: Link<T>,
}

impl<T: Copy + Debug> LinkVec<T> {
    pub fn new() -> Self {
        LinkVec {
            size: 0,
            head: None,
        }
    }

    pub fn len(&self) -> usize {
        self.size
    }

    pub fn clear(&mut self) {
        self.size = 0;
        self.head = None;
    }

    pub fn is_empty(&self) -> bool {
        0 == self.size
    }

    pub fn push(&mut self, data: T) {
        let node = Node::new(data);

        if self.is_empty() {
            self.head = Some(Box::new(node));
        } else {
            let mut curr = self.head.as_mut().unwrap();
            for _ in 0..(self.size - 1) {
                curr = curr.next.as_mut().unwrap();
            }
            curr.next = Some(Box::new(node));
        }
        self.size += 1;
    }

    pub fn append(&mut self, other: &mut Self) {
        while let Some(node) = other.head.as_mut().take() {
            self.push(node.data);
            other.head = node.next.take();
        }
        other.clear();
    }

    pub fn insert(&mut self, mut index: usize, data: T) {
        if index > self.size {
            index = self.size;
        }

        let mut node = Node::new(data);
        if self.is_empty() {
            self.head = Some(Box::new(node));
        } else if 0 == index {
            node.next = self.head.take();
            self.head = Some(Box::new(node));
        } else {
            let mut curr = self.head.as_mut().unwrap();
            for _ in 0..(index - 1) {
                curr = curr.next.as_mut().unwrap();
            }
            node.next = curr.next.take();
            curr.next = Some(Box::new(node));
        }
        self.size += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        self.remove(self.size - 1)
    }

    pub fn remove(&mut self, index: usize) -> Option<T> {
        if index >= self.size {
            return None;
        }

        let mut node;
        if 0 == index {
            node = self.head.take().unwrap();
            self.head = node.next.take();
        } else {
            let mut curr = self.head.as_mut().unwrap();
            for _ in 0..(index - 1) {
                curr = curr.next.as_mut().unwrap();
            }
            node = curr.next.take().unwrap();
            curr.next = node.next.take();
        }
        self.size -= 1;
        Some(node.data)
    }

    pub fn print_lvec(&self) {
        let mut curr = self.head.as_ref();
        while let Some(node) = curr {
            println!("vec val: {:?}", node.data);
            curr = node.next.as_ref();
        }
    }
}
