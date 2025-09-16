
import pandas as pd
import matplotlib.pyplot as plt
import os

def analyze_and_plot(input_file, output_dir):
    data = pd.read_csv(input_file)

    # Save processed data
    processed_path = os.path.join(output_dir, "processed.csv")
    data.to_csv(processed_path, index=False)

    # Calculate basic stats
    stats = {
        "min_absorbance": data["Absorbance"].min(),
        "max_absorbance": data["Absorbance"].max(),
        "mean_absorbance": data["Absorbance"].mean(),
        "min_wavelength": data["Wavelength"].min(),
        "max_wavelength": data["Wavelength"].max(),
    }
    results_path = os.path.join(output_dir, "results.txt")
    with open(results_path, "w") as f:
        for k, v in stats.items():
            f.write(f"{k}: {v}\n")

    # Plot and save spectrum
    plt.figure(figsize=(8,5))
    plt.plot(data["Wavelength"], data["Absorbance"], label="Absorbance")
    plt.xlabel("Wavelength (nm)")
    plt.ylabel("Absorbance")
    plt.title("Spectral Data")
    plt.grid(True)
    plt.legend()
    spectrum_path = os.path.join(output_dir, "spectrum.png")
    plt.savefig(spectrum_path)
    plt.close()

if __name__ == "__main__":
    analyze_and_plot("../data/spectrum.csv", "output")
