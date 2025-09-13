
import sys
import pandas as pd
import numpy as np
import math
import os
import tkinter as tk
from tkinter import filedialog

def read_data(file_path):
    df = pd.read_csv(file_path)
    return df

def convert_to_absorbance(df):
    if "Transmittance" in df.columns:
        T = df["Transmittance"]
        if T.max() > 1:
            T = T / 100.0
        df["Absorbance"] = -np.log10(T)
    return df

def beer_lambert_concentration(df, epsilon=100, path_length=1.0):
    avg_A = df["Absorbance"].mean()
    conc = avg_A / (epsilon * path_length)
    return conc, avg_A

def find_peak(df):
    peak_idx = df["Absorbance"].idxmax()
    return df.loc[peak_idx, "Wavelength"], df.loc[peak_idx, "Absorbance"]

def save_results(file_path, peak_wl, peak_A, avg_A, conc, out_dir=None):
    if out_dir is None:
        out_dir = os.path.join(os.path.dirname(__file__), "output")
    os.makedirs(out_dir, exist_ok=True)
    results_path = os.path.join(out_dir, "results.txt")
    with open(results_path, "w") as f:
        f.write("Results Summary\n")
        f.write("----------------\n")
        f.write(f"File analyzed: {file_path}\n")
        f.write(f"Peak: {peak_wl:.2f} nm (Absorbance = {peak_A:.3f})\n")
        f.write(f"Average Absorbance: {avg_A:.3f}\n")
        f.write(f"Estimated Concentration: {conc:.5f} M\n")
    print(f"[OK] Results summary saved to {results_path}")


def browse_file():
    root = tk.Tk()
    root.withdraw()
    file_path = filedialog.askopenfilename(
        title="Select CSV file",
        filetypes=[("CSV files", "*.csv"), ("All files", "*.*")]
    )
    return file_path

def main():
    if len(sys.argv) < 2:
        print("No file provided as argument. Please select a CSV file.")
        file_path = browse_file()
        if not file_path:
            print("No file selected. Exiting.")
            sys.exit(1)
    else:
        file_path = sys.argv[1]

    df = read_data(file_path)
    df = convert_to_absorbance(df)

    conc, avg_A = beer_lambert_concentration(df)
    peak_wl, peak_A = find_peak(df)

    out_dir = os.path.join(os.path.dirname(__file__), "output")
    os.makedirs(out_dir, exist_ok=True)
    df.to_csv(os.path.join(out_dir, "processed.csv"), index=False)
    save_results(file_path, peak_wl, peak_A, avg_A, conc, out_dir=out_dir)

    print("[OK] Analysis complete. Results saved to python_backend/output/")

if __name__ == "__main__":
    main()

