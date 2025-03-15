class User:
    def __init__(self, name, phone):
        self.name = name
        self.phone = phone

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class DanhSach:
    def __init__(self):
        self.head = None
        self.tail = None

    def add_tail(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node

    def remove_user(self, name):
        if self.head is None:
            print("List is empty")
            return

        current = self.head
        prev = None
        while current is not None and current.data.name != name:
            prev = current
            current = current.next

        if current is None:
            print("User not found")
            return

        if prev is None:
            self.head = current.next
        else:
            prev.next = current.next

        if current == self.tail:
            self.tail = prev

    def print_list(self):
        current = self.head
        while current is not None:
            print(f"{current.data.name} - {current.data.phone}")
            current = current.next

def main():
    ds = DanhSach()

    while True:
        print("\nMenu:")
        print("1. Add user")
        print("2. Remove user")
        print("3. Print list")
        print("4. Exit")
        option = int(input("Enter your option: "))

        if option == 1:
            name = input("Enter user name: ")
            phone = input("Enter user phone: ")
            user = User(name, phone)
            ds.add_tail(user)
        elif option == 2:
            name = input("Enter user name: ")
            ds.remove_user(name)
        elif option == 3:
            ds.print_list()
        elif option == 4:
            break
        else:
            print("Invalid option")

if __name__ == "__main__":
    main()