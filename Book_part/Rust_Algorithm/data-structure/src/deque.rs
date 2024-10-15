#[derive(Debug)]
pub struct Deque<T> {
    data: Vec<T>,
    capacity: usize,
}

impl<T> Deque<T> {
    pub fn new(size: usize) -> Self {
        Deque {
            data: Vec::with_capacity(size),
            capacity: size,
        }
    }

    pub fn add_front(&mut self, item: T) -> Result<(), String> {
        if Self::is_full(&self) {
            return Err("Deque is full".to_string());
        }

        self.data.insert(0, item);
        Ok(())
    }

    pub fn add_rear(&mut self, item: T) -> Result<(), String> {
        if Self::is_full(&self) {
            return Err("Deque is full".to_string());
        }

        self.data.push(item);
        Ok(())
    }

    pub fn remove_front(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }

        Some(self.data.remove(0))
    }

    pub fn remove_rear(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }

        self.data.pop()
    }

    pub fn size(&self) -> usize {
        self.data.len()
    }

    pub fn is_empty(&self) -> bool {
        0 == Self::size(&self)
    }

    pub fn is_full(&self) -> bool {
        self.capacity == Self::size(&self)
    }
}
