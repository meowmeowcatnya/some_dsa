struct ArrayList<T> {
    size: usize,
    tail: usize, 
    data: *mut T,
}

impl<T: Default + Copy> ArrayList<T> {
    fn new() -> Self {
        return Self {
            size: 10,
            tail: 0,
            data: unsafe{ std::alloc::alloc(std::alloc::Layout::array::<T>(10).unwrap()).cast()}
    }
}
    
    fn get(&self, index: usize) -> T {
        if index < self.tail {
            unsafe {
                return *self.data.add(index)
            }
        } else {
            panic!("Index out of bounds. Size is {}, but tried accessing at index {index}", self.tail);
        }
    }

    fn set(&mut self, index:usize, element: T) -> () {
        if index < self.tail {
            unsafe {
                *self.data.add(index) = element;
            }
            if index == self.tail {self.tail += 1}
        } else {
            panic!("Index out of bounds. Size is {}, but tried accessing at index {index}", self.tail);
        }
    }

    fn length(&self) -> usize {
        return self.tail;
    }

    fn push(&mut self, element: T) -> () {
        if self.tail < self.size {
            unsafe {
                *self.data.add(self.tail) = element;
            }
            self.tail += 1;
        } else {
                let new_data: *mut T = unsafe{std::alloc::alloc(std::alloc::Layout::array::<T>(2*self.tail).unwrap()).cast()};
                for i in 0..self.tail {
                    unsafe{
                        *new_data.add(i) = *self.data.add(i);
                    }
                }
                unsafe{
                    *new_data.add(self.tail) = element;
                }
                self.size = 2*self.tail;
                self.tail += 1;
                self.data = new_data;
        }
    }

    fn pop(&mut self) -> T {
        let element = unsafe {*self.data.add(self.tail-1)};
        self.tail -= 1;
        if self.tail < self.size / 4 {
            let new_data: *mut T  = unsafe{std::alloc::alloc(std::alloc::Layout::array::<T>(self.size / 2).unwrap()).cast()};
            for i in 0..=self.tail {
                unsafe {
                    *new_data.add(i) = *self.data.add(i);
                }
            }
            self.size = self.size / 2;
            self.data = new_data;
        }
        return element
    }
}


fn main() {
    let mut array_list: ArrayList<i32> =ArrayList::new();
    for i in 1..15 {
        array_list.push(i);
    }
    array_list.set(8, 30);
    let popped = array_list.pop();
    println!("popped element is: {popped}");
    let length = array_list.length();
    println!("length is {length}");
    println!("Index 5 is {}", array_list.get(5));
    
}


