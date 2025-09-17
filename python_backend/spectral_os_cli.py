import os
import sys
import time
import tkinter as tk
from tkinter import filedialog
import subprocess
import math

def spectral_os_cli():
    print("\n====================")
    print("   Spectral OS CLI  ")
    print("====================\n")
    instruction = input("Enter instruction (e.g., 'analyze csv'): ").strip().lower()
    if 'csv' not in instruction:
        print("Only CSV analysis is supported in this demo.")
        return

    # File dialog for CSV selection
    root = tk.Tk()
    root.withdraw()
    print("Please select a CSV file...")
    csv_path = filedialog.askopenfilename(
        title="Select CSV file",
        filetypes=[("CSV files", "*.csv"), ("All files", "*.*")]
    )
    if not csv_path:
        print("No file selected. Exiting.")
        return
    print(f"Selected: {csv_path}")

    # Sine wave animation
    print("\nAnalyzing... Enjoy the sine wave animation!\n")
    for t in range(40):
        y = int(10 + 8 * math.sin(t * 0.2))
        print(" " * y + "*")
        time.sleep(0.05)
    print()

    # Call analysis.py
    py_path = os.path.join(os.path.dirname(__file__), 'analysis.py')
    out_dir = os.path.join(os.path.dirname(__file__), 'output')
    try:
        subprocess.run([sys.executable, py_path, csv_path], check=True)
    except Exception as e:
        print(f"Analysis failed: {e}")
        return

    # Display results
    results_path = os.path.join(out_dir, 'results.txt')
    if os.path.exists(results_path):
        print("\n--- Analysis Results ---\n")
        with open(results_path, 'r') as f:
            print(f.read())
    else:
        print("No results found.")

if __name__ == "__main__":
    spectral_os_cli()
