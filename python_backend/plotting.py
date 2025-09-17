import matplotlib.pyplot as plt
import pandas as pd
import os

def generate_plot():
    try:
        # Read the processed data
        processed_path = os.path.join(os.path.dirname(__file__), "output", "processed.csv")
        if not os.path.exists(processed_path):
            print("[ERROR] No processed data found. Run analysis first.")
            return 1
            
        df = pd.read_csv(processed_path)
        
        # Create the plot
        plt.figure(figsize=(12, 8))
        plt.plot(df["Wavelength"], df["Absorbance"], 'b-', linewidth=2, label='Absorbance Spectrum')
        plt.xlabel('Wavelength (nm)', fontsize=12)
        plt.ylabel('Absorbance', fontsize=12)
        plt.title('Spectrophotometer Analysis - Absorbance vs Wavelength', fontsize=14, fontweight='bold')
        plt.grid(True, alpha=0.3)
        plt.legend(fontsize=11)
        
        # Add some styling
        plt.tight_layout()
        
        # Save the plot
        output_path = os.path.join(os.path.dirname(__file__), "output", "plot.png")
        plt.savefig(output_path, dpi=300, bbox_inches='tight')
        plt.close()
        
        print(f"[OK] Plot saved to {output_path}")
        return 0
    except Exception as e:
        print(f"[ERROR] Failed to generate plot: {e}")
        return 1

if __name__ == "__main__":
    exit(generate_plot())
