class HashTable:
    def __init__(self):
        self.m = int(input("Enter size of hash table: "))
        self.hashTable = [None] * self.m
        self.ele_count = 0
        print("Initial Hash Table:", self.hashTable)# Initial Hash Table: [None, None, None, None, None, None, None, None, None, None]
    
    def hashFunction(self, key): #calculating hash value
        return key % self.m

    def isFull(self):
        return self.ele_count == self.m
    
    def linearProbe(self, key, data):
        index = self.hashFunction(key)
        comparisons = 0
        
        while self.hashTable[index] is not None:
            index = (index + 1) % self.m  # Wrap around
            comparisons += 1
        
        self.hashTable[index] = (key, data)
        self.ele_count += 1
        print(f"Data inserted at index {index}")
        print("Updated Hash Table:", self.hashTable)
        print("Number of comparisons:", comparisons)
    
    def quadraticProbe(self, key, data):
        index = self.hashFunction(key)
        i = 0
        comparisons = 0
        
        while self.hashTable[(index + i * i) % self.m] is not None:
            i += 1
            comparisons += 1
            if i >= self.m:  # Prevent infinite loop
                print("Table is full, cannot insert")
                return
        
        new_index = (index + i * i) % self.m
        self.hashTable[new_index] = (key, data)
        self.ele_count += 1
        print(f"Data inserted at index {new_index}")
        print("Updated Hash Table:", self.hashTable)
        print("Number of comparisons:", comparisons)
    
    def searchLinear(self, key):
        index = self.hashFunction(key)
        
        for _ in range(self.m):  # Prevent infinite loops
            if self.hashTable[index] is None:
                return None
            if self.hashTable[index][0] == key:
                return index
            index = (index + 1) % self.m  # Linear probing wrap-around
        return None
    
    def searchQuadratic(self, key):
        index = self.hashFunction(key)
        i = 0
        
        for _ in range(self.m):  # Prevent infinite loops
            new_index = (index + i * i) % self.m
            if self.hashTable[new_index] is None:
                return None
            if self.hashTable[new_index][0] == key:
                return new_index
            i += 1
        return None
    
    def insertViaLinear(self, key, data):
        if self.isFull():
            print("Table is full")
            return
        
        index = self.hashFunction(key)
        if self.hashTable[index] is None:
            self.hashTable[index] = (key, data)
            self.ele_count += 1
            print(f"Data inserted at index {index}")
        else:
            print("Collision occurred, applying linear probing...")
            self.linearProbe(key, data)
    
    def insertViaQuadratic(self, key, data):
        if self.isFull():
            print("Table is full")
            return
        
        index = self.hashFunction(key)
        if self.hashTable[index] is None:
            self.hashTable[index] = (key, data)
            self.ele_count += 1
            print(f"Data inserted at index {index}")
        else:
            print("Collision occurred, applying quadratic probing...")
            self.quadraticProbe(key, data)


def menu():
    obj = HashTable()
    
    while True:
        print("\n************************")
        print("1. Linear Probing")
        print("2. Quadratic Probing")
        print("3. Exit")
        print("************************")
        choice = int(input("Enter choice: "))
        
        if choice == 1:
            while True:
                print("\n1. Insert")
                print("2. Search")
                print("3. Back")
                ch2 = int(input("Enter choice: "))
                
                if ch2 == 1:
                    key = int(input("Enter key (phone number): "))
                    data = input("Enter name: ")
                    obj.insertViaLinear(key, data)
                elif ch2 == 2:
                    key = int(input("Enter key to search: "))
                    index = obj.searchLinear(key)
                    if index is None:
                        print("Key not found")
                    else:
                        print(f"Key found at index {index}")
                elif ch2 == 3:
                    break
                else:
                    print("Invalid choice")
        
        elif choice == 2:
            while True:
                print("\n1. Insert")
                print("2. Search")
                print("3. Back")
                ch2 = int(input("Enter choice: "))
                
                if ch2 == 1:
                    key = int(input("Enter key (phone number): "))
                    data = input("Enter name: ")
                    obj.insertViaQuadratic(key, data)
                elif ch2 == 2:
                    key = int(input("Enter key to search: "))
                    index = obj.searchQuadratic(key)
                    if index is None:
                        print("Key not found")
                    else:
                        print(f"Key found at index {index}")
                elif ch2 == 3:
                    break
                else:
                    print("Invalid choice")
        
        elif choice == 3:
            print("Exiting...")
            break
        else:
            print("Invalid choice")

menu()
