import tkinter as tk
from tkinter import ttk, messagebox
import json
from listt import User, Node, DanhSach
import os
from tkinter import font as tkfont

class UserManagementGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("User Management System")
        self.root.geometry("1000x700")
        
        # Set theme
        style = ttk.Style()
        style.theme_use('clam')
        
        # Configure colors
        style.configure("Treeview",
                      background="#f0f0f0",
                      foreground="black",
                      rowheight=25,
                      fieldbackground="#f0f0f0")
        style.configure("Treeview.Heading",
                      background="#4a90e2",
                      foreground="white",
                      relief="flat",
                      font=('Arial', 10, 'bold'))
        style.map("Treeview.Heading",
                background=[('active', '#2171cd')])
        
        # Configure button style
        style.configure("Action.TButton",
                      padding=10,
                      font=('Arial', 10),
                      background="#4a90e2",
                      foreground="white")
        style.map("Action.TButton",
                background=[('active', '#2171cd')],
                foreground=[('active', 'white')])
        
        # Initialize data
        self.ds = DanhSach()
        
        # Create main frame with padding and background
        self.main_frame = ttk.Frame(self.root, padding="20")
        self.main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        self.main_frame.grid_rowconfigure(0, weight=1)
        self.main_frame.grid_columnconfigure(0, weight=1)
        
        # Initialize status variable
        self.status_var = tk.StringVar()
        
        # Add title
        title_font = tkfont.Font(family="Arial", size=16, weight="bold")
        title_label = ttk.Label(self.main_frame, 
                              text="User Management System",
                              font=title_font)
        title_label.grid(row=0, column=0, pady=(0, 20))
        
        # Create and configure treeview
        self.create_treeview()
        
        # Create buttons frame
        self.create_buttons()
        
        # Add status bar
        status_bar = ttk.Label(self.main_frame, 
                             textvariable=self.status_var,
                             font=('Arial', 9),
                             foreground='#666666')
        status_bar.grid(row=3, column=0, pady=(5, 0), sticky='e')
        
        # Load initial data
        self.refresh_treeview()
        
    def create_treeview(self):
        # Create Treeview Frame with padding
        tree_frame = ttk.Frame(self.main_frame)
        tree_frame.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 20))
        tree_frame.grid_rowconfigure(0, weight=1)
        tree_frame.grid_columnconfigure(0, weight=1)
        
        # Create Treeview with adjusted columns
        columns = ("Name", "Phone", "Email", "Address")
        self.tree = ttk.Treeview(tree_frame, columns=columns, show="headings", style="Treeview")
        
        # Set column headings and widths
        column_widths = {
            "Name": 200,
            "Phone": 150,
            "Email": 250,
            "Address": 300
        }
        
        for col, width in column_widths.items():
            self.tree.heading(col, text=col)
            self.tree.column(col, width=width, minwidth=100)
        
        # Add scrollbars
        y_scrollbar = ttk.Scrollbar(tree_frame, orient=tk.VERTICAL, command=self.tree.yview)
        x_scrollbar = ttk.Scrollbar(tree_frame, orient=tk.HORIZONTAL, command=self.tree.xview)
        self.tree.configure(yscrollcommand=y_scrollbar.set, xscrollcommand=x_scrollbar.set)
        
        # Grid treeview and scrollbars
        self.tree.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        y_scrollbar.grid(row=0, column=1, sticky=(tk.N, tk.S))
        x_scrollbar.grid(row=1, column=0, sticky=(tk.W, tk.E))
        
        # Bind selection event
        self.tree.bind('<<TreeviewSelect>>', self.on_select)
        
    def create_buttons(self):
        # Buttons Frame
        btn_frame = ttk.Frame(self.main_frame)
        btn_frame.grid(row=2, column=0, pady=10)
        
        # Create buttons with improved style
        buttons = [
            ("Add User", self.show_add_dialog, "➕"),
            ("Edit User", self.show_edit_dialog, "✏️"),
            ("Remove User", self.remove_user, "🗑️"),
            ("Search", self.show_search_dialog, "🔍"),
            ("Refresh", self.refresh_treeview, "🔄")
        ]
        
        for i, (text, command, icon) in enumerate(buttons):
            btn = ttk.Button(btn_frame, 
                           text=f"{icon} {text}", 
                           command=command,
                           style="Action.TButton")
            btn.grid(row=0, column=i, padx=5)
        
    def on_select(self, event):
        selected = self.tree.selection()
        if selected:
            self.status_var.set("Selected user: " + self.tree.item(selected[0])["values"][0])
        else:
            self.status_var.set("")
            
    def update_status(self):
        count = len(self.tree.get_children())
        self.status_var.set(f"Total users: {count}")
        
    def refresh_treeview(self):
        for item in self.tree.get_children():
            self.tree.delete(item)
            
        current = self.ds.head
        while current:
            self.tree.insert("", tk.END, values=(
                current.data.name,
                current.data.phone,
                current.data.email or "-",
                current.data.address or "-"
            ))
            current = current.next
        
        self.update_status()

    def show_add_dialog(self):
        dialog = UserDialog(self.root, "Add User")
        if dialog.result:
            user = User(
                dialog.result["name"],
                dialog.result["phone"],
                dialog.result["email"],
                dialog.result["address"]
            )
            self.ds.add_tail(user)
            self.refresh_treeview()
            
    def show_edit_dialog(self):
        selected = self.tree.selection()
        if not selected:
            messagebox.showwarning("Warning", "Please select a user to edit")
            return
            
        values = self.tree.item(selected[0])["values"]
        dialog = UserDialog(self.root, "Edit User", {
            "name": values[0],
            "phone": values[1],
            "email": values[2] if values[2] != "-" else "",
            "address": values[3] if values[3] != "-" else ""
        })
        
        if dialog.result:
            self.ds.edit_user(values[0])  # This will update the user in the linked list
            self.refresh_treeview()
            
    def remove_user(self):
        selected = self.tree.selection()
        if not selected:
            messagebox.showwarning("Warning", "Please select a user to remove")
            return
            
        name = self.tree.item(selected[0])["values"][0]
        if messagebox.askyesno("Confirm", f"Are you sure you want to remove {name}?"):
            self.ds.remove_user(name)
            self.refresh_treeview()
            
    def show_search_dialog(self):
        keyword = tk.simpledialog.askstring("Search", "Enter search keyword:")
        if keyword:
            # Clear existing items
            for item in self.tree.get_children():
                self.tree.delete(item)
                
            # Search and display results
            current = self.ds.head
            while current:
                if (keyword.lower() in current.data.name.lower() or 
                    keyword.lower() in current.data.phone.lower() or
                    keyword.lower() in current.data.email.lower()):
                    self.tree.insert("", tk.END, values=(
                        current.data.name,
                        current.data.phone,
                        current.data.email or "-",
                        current.data.address or "-"
                    ))
                current = current.next

class UserDialog:
    def __init__(self, parent, title, initial_values=None):
        self.result = None
        
        # Create dialog window
        self.dialog = tk.Toplevel(parent)
        self.dialog.title(title)
        self.dialog.geometry("500x400")
        self.dialog.transient(parent)
        self.dialog.grab_set()
        
        # Add padding frame
        main_frame = ttk.Frame(self.dialog, padding="20")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Title
        title_font = tkfont.Font(family="Arial", size=14, weight="bold")
        title_label = ttk.Label(main_frame, text=title, font=title_font)
        title_label.grid(row=0, column=0, columnspan=2, pady=(0, 20))
        
        # Create form fields with better layout
        fields = [
            ("Name:", "name_var", True),
            ("Phone:", "phone_var", True),
            ("Email:", "email_var", False),
            ("Address:", "address_var", False)
        ]
        
        for i, (label_text, var_name, required) in enumerate(fields, start=1):
            # Label
            label = ttk.Label(main_frame, 
                            text=label_text + (" *" if required else ""),
                            font=('Arial', 10))
            label.grid(row=i, column=0, padx=(0, 10), pady=10, sticky='e')
            
            # Entry with variable
            setattr(self, var_name, tk.StringVar(
                value=initial_values[var_name.split('_')[0]] if initial_values else ""))
            entry = ttk.Entry(main_frame, 
                            textvariable=getattr(self, var_name),
                            width=40,
                            font=('Arial', 10))
            entry.grid(row=i, column=1, pady=10, sticky='w')
        
        # Buttons with improved style
        btn_frame = ttk.Frame(main_frame)
        btn_frame.grid(row=5, column=0, columnspan=2, pady=30)
        
        style = ttk.Style()
        style.configure("Save.TButton", 
                       padding=10,
                       font=('Arial', 10, 'bold'))
        
        ttk.Button(btn_frame, 
                   text="Save",
                   command=self.ok_clicked,
                   style="Save.TButton").grid(row=0, column=0, padx=5)
        ttk.Button(btn_frame,
                   text="Cancel",
                   command=self.dialog.destroy,
                   style="Save.TButton").grid(row=0, column=1, padx=5)
        
        # Center the dialog
        self.dialog.update_idletasks()
        width = self.dialog.winfo_width()
        height = self.dialog.winfo_height()
        x = (self.dialog.winfo_screenwidth() // 2) - (width // 2)
        y = (self.dialog.winfo_screenheight() // 2) - (height // 2)
        self.dialog.geometry(f"{width}x{height}+{x}+{y}")
        
        self.dialog.wait_window()
        
    def ok_clicked(self):
        name = self.name_var.get().strip()
        phone = self.phone_var.get().strip()
        
        if not name or not phone:
            messagebox.showwarning("Warning", 
                                 "Name and Phone are required fields!",
                                 parent=self.dialog)
            return
            
        self.result = {
            "name": name,
            "phone": phone,
            "email": self.email_var.get().strip(),
            "address": self.address_var.get().strip()
        }
        self.dialog.destroy()

def main():
    root = tk.Tk()
    root.configure(bg='white')  # Set background color
    
    # Set window icon (if you have one)
    # root.iconbitmap('path_to_icon.ico')
    
    app = UserManagementGUI(root)
    root.mainloop()

if __name__ == "__main__":
    main() 