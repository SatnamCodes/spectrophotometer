import tkinter as tk
from tkinter import filedialog
import sys

def main():
    root = tk.Tk()
    root.withdraw()
    file_path = filedialog.askopenfilename(
        title="Select CSV file",
        filetypes=[("CSV files", "*.csv"), ("All files", "*.*")]
    )
    if file_path:
        print(file_path)
    else:
        print("")

if __name__ == "__main__":
    main()
