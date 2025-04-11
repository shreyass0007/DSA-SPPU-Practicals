import sys

# -------------------------------
# Data Model
# -------------------------------
class Expense:
    def __init__(self, id, date, description, category, amount):
        self.id = id
        self.date = date
        self.description = description
        self.category = category
        self.amount = amount

    def __str__(self):
        return (f"ID: {self.id} | Date: {self.date} | "
                f"Description: {self.description} | Category: {self.category} | "
                f"Amount: {self.amount}")

# -------------------------------
# Binary Search Tree Implementation
# -------------------------------
class BSTNode:
    def __init__(self, key, expense):
        self.key = key  # In our case, key is the expense amount.
        self.expenses = [expense]  # List to handle duplicate amounts.
        self.left = None
        self.right = None

class ExpenseBST:
    def __init__(self):
        self.root = None

    def insert(self, expense):
        if self.root is None:
            self.root = BSTNode(expense.amount, expense)
        else:
            self._insert(self.root, expense)

    def _insert(self, node, expense):
        if expense.amount < node.key:
            if node.left is None:
                node.left = BSTNode(expense.amount, expense)
            else:
                self._insert(node.left, expense)
        elif expense.amount > node.key:
            if node.right is None:
                node.right = BSTNode(expense.amount, expense)
            else:
                self._insert(node.right, expense)
        else:
            # Equal amounts: add to the same node list.
            node.expenses.append(expense)

    def inorder(self):
        """Return expenses sorted by amount (ascending) using in-order traversal."""
        result = []
        self._inorder(self.root, result)
        return result

    def _inorder(self, node, result):
        if node:
            self._inorder(node.left, result)
            result.extend(node.expenses)
            self._inorder(node.right, result)

    def search(self, amount):
        """Return a list of expenses that match the given amount."""
        return self._search(self.root, amount)

    def _search(self, node, amount):
        if node is None:
            return []
        if amount < node.key:
            return self._search(node.left, amount)
        elif amount > node.key:
            return self._search(node.right, amount)
        else:
            return node.expenses

# -------------------------------
# Max-Heap Implementation
# -------------------------------
class ExpenseMaxHeap:
    def __init__(self):
        self.heap = []

    def insert(self, expense):
        self.heap.append(expense)
        self._heapify_up(len(self.heap) - 1)

    def _heapify_up(self, index):
        parent = (index - 1) // 2
        if index > 0 and self.heap[index].amount > self.heap[parent].amount:
            self.heap[index], self.heap[parent] = self.heap[parent], self.heap[index]
            self._heapify_up(parent)

    def extract_max(self):
        if not self.heap:
            return None
        max_expense = self.heap[0]
        last_expense = self.heap.pop()
        if self.heap:
            self.heap[0] = last_expense
            self._heapify_down(0)
        return max_expense

    def _heapify_down(self, index):
        largest = index
        left = 2 * index + 1
        right = 2 * index + 2

        if left < len(self.heap) and self.heap[left].amount > self.heap[largest].amount:
            largest = left
        if right < len(self.heap) and self.heap[right].amount > self.heap[largest].amount:
            largest = right
        if largest != index:
            self.heap[index], self.heap[largest] = self.heap[largest], self.heap[index]
            self._heapify_down(largest)

    def peek_max(self):
        return self.heap[0] if self.heap else None

# -------------------------------
# Sorting Algorithm (Merge Sort)
# -------------------------------
def merge_sort_expenses(expenses):
    if len(expenses) <= 1:
        return expenses
    mid = len(expenses) // 2
    left = merge_sort_expenses(expenses[:mid])
    right = merge_sort_expenses(expenses[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i].amount <= right[j].amount:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

# -------------------------------
# Expense Tracker Class
# -------------------------------
class ExpenseTracker:
    def __init__(self):
        self.expenses = []  # Array to store expenses.
        self.bst = ExpenseBST()
        self.heap = ExpenseMaxHeap()
        self.next_id = 1

    def add_expense(self, date, description, category, amount):
        try:
            amount = float(amount)
        except ValueError:
            print("Invalid amount. Please enter a numeric value.")
            return
        expense = Expense(self.next_id, date, description, category, amount)
        self.expenses.append(expense)
        self.bst.insert(expense)
        self.heap.insert(expense)
        self.next_id += 1
        print("Expense added successfully.")

    def view_expenses(self):
        if not self.expenses:
            print("No expenses recorded.")
        else:
            print("\n--- All Expenses ---")
            for expense in self.expenses:
                print(expense)

    def sort_expenses(self):
        sorted_list = merge_sort_expenses(self.expenses)
        print("\n--- Expenses Sorted by Amount (Ascending) ---")
        for expense in sorted_list:
            print(expense)

    def analyze_expenses(self):
        if not self.expenses:
            print("No expenses to analyze.")
            return
        total = sum(exp.amount for exp in self.expenses)
        average = total / len(self.expenses)
        max_expense = self.heap.peek_max()
        sorted_expenses = self.bst.inorder()  # Inorder traversal gives sorted order.
        min_expense = sorted_expenses[0] if sorted_expenses else None

        print("\n--- Expense Analysis ---")
        print(f"Total Expenses: {total}")
        print(f"Average Expense: {average:.2f}")
        print("\nHighest Expense:")
        print(max_expense if max_expense else "N/A")
        print("\nLowest Expense:")
        print(min_expense if min_expense else "N/A")

    def search_expense_by_amount(self, amount):
        try:
            amount = float(amount)
        except ValueError:
            print("Invalid amount. Please enter a numeric value.")
            return
        results = self.bst.search(amount)
        print(f"\n--- Search Results for Amount: {amount} ---")
        if not results:
            print("No expense found with that amount.")
        else:
            for expense in results:
                print(expense)

# -------------------------------
# Main Program Loop
# -------------------------------
def main():
    tracker = ExpenseTracker()
    menu = """
Expense Tracker Menu:
1. Add Expense
2. View Expenses
3. Sort Expenses by Amount
4. Analyze Expenses
5. Search Expense by Amount
6. Exit
Choose an option (1-6): """
    
    while True:
        choice = input(menu)
        if choice == "1":
            date = input("Enter date (e.g., YYYY-MM-DD): ")
            description = input("Enter description: ")
            category = input("Enter category: ")
            amount = input("Enter amount: ")
            tracker.add_expense(date, description, category, amount)
        elif choice == "2":
            tracker.view_expenses()
        elif choice == "3":
            tracker.sort_expenses()
        elif choice == "4":
            tracker.analyze_expenses()
        elif choice == "5":
            amt = input("Enter the expense amount to search for: ")
            tracker.search_expense_by_amount(amt)
        elif choice == "6":
            print("Exiting Expense Tracker. Goodbye!")
            sys.exit(0)
        else:
            print("Invalid option. Please choose between 1 and 6.")

if __name__ == "__main__":
    main()
