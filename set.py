class SetOperations:
    def __init__(self):
        self.a = set()
        self.b = set()

    def add(self, list_name, new_elements):
        if list_name == 'a':
            self.a.update(new_elements)
        elif list_name == 'b':
            self.b.update(new_elements)

    def remove(self, list_name, element):
        if list_name == 'a':
            if element in self.a:
                self.a.remove(element)
                print(f"Element '{element}' removed from set 'a'.")
            else:
                print(f"Element '{element}' not found in set 'a'.")
        elif list_name == 'b':
            if element in self.b:
                self.b.remove(element)
                print(f"Element '{element}' removed from set 'b'.")
            else:
                print(f"Element '{element}' not found in set 'b'.")
        else:
            print("Invalid set name. Please use 'a' or 'b'.")

    def contains(self, list_name, element):
        if list_name == 'a':
            return element in self.a
        elif list_name == 'b':
            return element in self.b

    def size(self, list_name):
        if list_name == 'a':
            return len(self.a)
        elif list_name == 'b':
            return len(self.b)

    def iterator(self, list_name):
        if list_name == 'a':
            return iter(self.a)
        elif list_name == 'b':
            return iter(self.b)

    def intersection(self):
        result = set()
        for elem in self.a:
            if elem in self.b:
                result.add(elem)
        return result

    def union(self):
        result = set(self.a)
        for elem in self.b:
            if elem not in result:
                result.add(elem)
        return result

    def difference(self):
        result = set()
        for elem in self.a:
            if elem not in self.b:
                result.add(elem)
        return result

    def subset(self, list_name1, list_name2):
        if list_name1 == 'a' and list_name2 == 'b':
            return all(elem in self.b for elem in self.a)
        elif list_name1 == 'b' and list_name2 == 'a':
            return all(elem in self.a for elem in self.b)
        else:
            print("Invalid list names provided.")
            return False


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
        choice = int(input("Enter your choice: "))

        if choice == 1:
            list_name = input("Enter the list name (a or b): ")
            elements = input("Enter the elements to add (comma-separated): ").split(",")
            elements = {elem.strip() for elem in elements}
            set_operations.add(list_name, elements)
        elif choice == 2:
            list_name = input("Enter the list name (a or b): ")
            element = input("Enter the element to be removed: ").strip()
            set_operations.remove(list_name, element)
        elif choice == 3:
            list_name = input("Enter the list name (a or b): ")
            element = input("Enter the element to check: ").strip()
            print("Element exists:", set_operations.contains(list_name, element))
        elif choice == 4:
            list_name = input("Enter the list name (a or b): ")
            print("Size of set:", set_operations.size(list_name))
        elif choice == 5:
            list_name = input("Enter the list name (a or b): ")
            print("Elements in the set:")
            for elem in set_operations.iterator(list_name):
                print(elem)
        elif choice == 6:
            print("Intersection of sets:", set_operations.intersection())
        elif choice == 7:
            print("Union of sets:", set_operations.union())
        elif choice == 8:
            print("Difference of sets (a - b):", set_operations.difference())
        elif choice == 9:
            list_name1 = input("Enter the first list name (a or b): ")
            list_name2 = input("Enter the second list name (a or b): ")
            is_subset = set_operations.subset(list_name1, list_name2)
            print(f"Is {list_name1} a subset of {list_name2}:", is_subset)
        elif choice == 10:
            print("Exiting the program. Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()
