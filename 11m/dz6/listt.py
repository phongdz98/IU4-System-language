import json
from rich.console import Console
from rich.table import Table
from rich.prompt import Prompt, IntPrompt
from rich.panel import Panel
from rich import print as rprint
import os

class User:
    def __init__(self, name, phone, email="", address=""):
        self.name = name
        self.phone = phone
        self.email = email
        self.address = address
    
    def to_dict(self):
        return {
            "name": self.name,
            "phone": self.phone,
            "email": self.email,
            "address": self.address
        }
    
    @staticmethod
    def from_dict(data):
        return User(data["name"], data["phone"], data["email"], data["address"])

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class DanhSach:
    def __init__(self):
        self.head = None
        self.tail = None
        self.console = Console()
        self.load_data()

    def load_data(self):
        try:
            if os.path.exists("users.json"):
                with open("users.json", "r", encoding="utf-8") as f:
                    data = json.load(f)
                    for user_data in data:
                        user = User.from_dict(user_data)
                        self.add_tail(user)
        except Exception as e:
            self.console.print(f"[red]Error loading data: {e}[/red]")

    def save_data(self):
        try:
            data = []
            current = self.head
            while current:
                data.append(current.data.to_dict())
                current = current.next
            with open("users.json", "w", encoding="utf-8") as f:
                json.dump(data, f, indent=4, ensure_ascii=False)
            self.console.print("[green]Data saved successfully![/green]")
        except Exception as e:
            self.console.print(f"[red]Error saving data: {e}[/red]")

    def add_tail(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.save_data()

    def remove_user(self, name):
        if self.head is None:
            self.console.print("[yellow]List is empty[/yellow]")
            return

        current = self.head
        prev = None
        while current is not None and current.data.name != name:
            prev = current
            current = current.next

        if current is None:
            self.console.print("[yellow]User not found[/yellow]")
            return

        if prev is None:
            self.head = current.next
        else:
            prev.next = current.next

        if current == self.tail:
            self.tail = prev

        self.console.print(f"[green]Successfully removed user: {name}[/green]")
        self.save_data()

    def search_user(self, keyword):
        if self.head is None:
            self.console.print("[yellow]List is empty[/yellow]")
            return

        table = Table(title=f"Search Results for '{keyword}'")
        table.add_column("Name", style="cyan")
        table.add_column("Phone", style="magenta")
        table.add_column("Email", style="green")
        table.add_column("Address", style="yellow")

        current = self.head
        found = False
        while current:
            if (keyword.lower() in current.data.name.lower() or 
                keyword.lower() in current.data.phone.lower() or
                keyword.lower() in current.data.email.lower()):
                found = True
                table.add_row(
                    current.data.name,
                    current.data.phone,
                    current.data.email or "-",
                    current.data.address or "-"
                )
            current = current.next

        if found:
            self.console.print(table)
        else:
            self.console.print("[yellow]No matching users found[/yellow]")

    def edit_user(self, name):
        current = self.head
        while current and current.data.name != name:
            current = current.next

        if not current:
            self.console.print("[yellow]User not found[/yellow]")
            return

        self.console.print(Panel.fit("Edit User Information", style="cyan"))
        current.data.name = Prompt.ask("Name", default=current.data.name)
        current.data.phone = Prompt.ask("Phone", default=current.data.phone)
        current.data.email = Prompt.ask("Email", default=current.data.email)
        current.data.address = Prompt.ask("Address", default=current.data.address)
        self.save_data()
        self.console.print("[green]User information updated successfully![/green]")

    def print_list(self):
        if self.head is None:
            self.console.print("[yellow]List is empty[/yellow]")
            return

        table = Table(title="User List")
        table.add_column("Name", style="cyan")
        table.add_column("Phone", style="magenta")
        table.add_column("Email", style="green")
        table.add_column("Address", style="yellow")

        current = self.head
        while current:
            table.add_row(
                current.data.name,
                current.data.phone,
                current.data.email or "-",
                current.data.address or "-"
            )
            current = current.next

        self.console.print(table)

def display_menu():
    console = Console()
    menu = Table(title="User Management System", style="cyan")
    menu.add_column("Option", style="magenta")
    menu.add_column("Description", style="green")
    
    menu.add_row("1", "Add user")
    menu.add_row("2", "Remove user")
    menu.add_row("3", "Search user")
    menu.add_row("4", "Edit user")
    menu.add_row("5", "Print list")
    menu.add_row("6", "Exit")
    
    console.print(menu)

def main():
    console = Console()
    ds = DanhSach()

    while True:
        console.clear()
        display_menu()
        
        try:
            option = IntPrompt.ask("Enter your option", choices=["1", "2", "3", "4", "5", "6"])
            
            if option == 1:
                console.print(Panel.fit("Add New User", style="cyan"))
                name = Prompt.ask("Enter user name")
                phone = Prompt.ask("Enter user phone")
                email = Prompt.ask("Enter user email (optional)", default="")
                address = Prompt.ask("Enter user address (optional)", default="")
                user = User(name, phone, email, address)
                ds.add_tail(user)
                console.print("[green]User added successfully![/green]")
            
            elif option == 2:
                name = Prompt.ask("Enter user name to remove")
                ds.remove_user(name)
            
            elif option == 3:
                keyword = Prompt.ask("Enter search keyword")
                ds.search_user(keyword)
            
            elif option == 4:
                name = Prompt.ask("Enter user name to edit")
                ds.edit_user(name)
            
            elif option == 5:
                ds.print_list()
            
            elif option == 6:
                console.print("[yellow]Goodbye![/yellow]")
                break
            
            if option != 6:
                Prompt.ask("\nPress Enter to continue")
                
        except Exception as e:
            console.print(f"[red]Error: {e}[/red]")
            Prompt.ask("\nPress Enter to continue")

if __name__ == "__main__":
    main()