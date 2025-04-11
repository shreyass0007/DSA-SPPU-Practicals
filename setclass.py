class SetOperations:
    def __init__(self):
        self.a = set()
        self.b = set()
    def add(self, list_name, new_elements):
        #Adds elements to the specified set
        if list_name == 'a':
            self.a.update(new_elements)
        elif list_name == 'b':
            self.b.update(new_elements)
    def remove(self, list_name, element):
        #Removes an element from the specified set (without error).
        if list_name == 'a':
            self.a.discard(element)  # Discard prevents KeyError
        elif list_name == 'b':
            self.b.discard(element)
    def contains(self, list_name, element):
        #Checks if an element exists in the specified set.
        return element in self.a if list_name == 'a' else element in self.b
    def size(self, list_name):
        #Returns the size of the specified set.
        return len(self.a) if list_name == 'a' else len(self.b)
    def iterator(self, list_name):
        #Returns an iterator for the specified set.
        return iter(self.a) if list_name == 'a' else iter(self.b)
    def intersection(self):
        #Manually finds the intersection of sets A and B.
        return {elem for elem in self.a if elem in self.b}
    def union(self):
        #Manually finds the union of sets A and B.
        result = set(self.a)
        for elem in self.b:
            if elem not in result:
                result.add(elem)
        return result
    def difference(self, list_name1, list_name2):
        #Finds the difference between two sets (A - B or B - A).
        set1 = self.a if list_name1 == 'a' else self.b
        set2 = self.a if list_name2 == 'a' else self.b
        return {elem for elem in set1 if elem not in set2}
    def subset(self, list_name1, list_name2):
        #Checks if one set is a subset of another.
        set1 = self.a if list_name1 == 'a' else self.b
        set2 = self.a if list_name2 == 'a' else self.b
        return all(elem in set2 for elem in set1)
def main():
    set_operations = SetOperations() 
    while True:
        print("\nMenu:")
        print("1. Add elements")
        print("2. Remove element")
        print("3. Check if element is in set")
        print("4. Get size of set")
        print("5. Iterate over set")
        print("6. Intersection of sets")
        print("7. Union of sets")
        print("8. Difference of sets")
        print("9. Check subset")
        print("10. Exit")
        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("Invalid input. Please enter a number.")
            continue
        if choice == 1:
            list_name = input("Enter the set name (a or b): ").strip().lower()
            elements = input("Enter elements to add (comma-separated): ").split( )
            set_operations.add(list_name, {elem.strip() for elem in elements})
        elif choice == 2:
            list_name = input("Enter the set name (a or b): ").strip().lower()
            element = input("Enter the element to be removed: ").strip()
            set_operations.remove(list_name, element)
        elif choice == 3:
            list_name = input("Enter the set name (a or b): ").strip().lower()
            element = input("Enter the element to check: ").strip()
            print("Element exists:", set_operations.contains(list_name, element))
        elif choice == 4:
            list_name = input("Enter the set name (a or b): ").strip().lower()
            print("Size of set:", set_operations.size(list_name))
        elif choice == 5:
            list_name = input("Enter the set name (a or b): ").strip().lower()
            print("Elements in the set:")
            for elem in set_operations.iterator(list_name):
                print(elem)
        elif choice == 6:
            print("Intersection of sets:", set_operations.intersection())
        elif choice == 7:
            print("Union of sets:", set_operations.union())
        elif choice == 8:
            list_name1 = input("Enter the first set name (a or b): ").strip().lower()
            list_name2 = input("Enter the second set name (a or b): ").strip().lower()
            print(f"Difference of {list_name1} - {list_name2}: {set_operations.difference(list_name1, list_name2)}")
        elif choice == 9:
            list_name1 = input("Enter the first set name (a or b): ").strip().lower()
            list_name2 = input("Enter the second set name (a or b): ").strip().lower()
            print(f"Is {list_name1} a subset of {list_name2}? {set_operations.subset(list_name1, list_name2)}")
        elif choice == 10:
            print("Exiting the program. Goodbye!")
            break
if __name__ == "__main__":
    main()
