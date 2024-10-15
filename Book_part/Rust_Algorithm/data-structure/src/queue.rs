#[derive(Debug)]
pub struct Queue<T> {
    capacity: usize,
    data: Vec<T>,
}

impl<T> Queue<T> {
    pub fn new(size: usize) -> Self {
        Queue {
            capacity: size,
            data: Vec::with_capacity(size),
        }
    }

    pub fn size(&self) -> usize {
        self.data.len()
    }

    pub fn is_empty(&self) -> bool {
        0 == Self::size(&self)
    }

    pub fn enqueue(&mut self, item: T) -> Result<(), String> {
        if Self::size(&self) == self.capacity {
            return Err("Queue is full".to_string());
        }

        self.data.insert(0, item);
        Ok(())
    }

    pub fn dequeue(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }

        self.data.pop()
    }
}
