# SpectralOS

SpectralOS is a minimal, interactive spectrophotometer analysis suite with a C-based command-line shell and a Python backend for scientific data processing and visualization.

## Features

- **Interactive CLI Shell (C):**
  - `load` — Select a CSV dataset via file dialog or path.
  - Menu navigation with W/S and Enter after loading a file.
  - `analyze` — Run Python backend to process the loaded file.
  - `results` — View formatted analysis results.
  - `plot` — Generate and view spectrum plot.
  - `exit` — Graceful shutdown with a thank-you message.

- **Python Backend:**
  - Converts Transmittance to Absorbance if needed.
  - Computes average absorbance, peak wavelength, and concentration (Beer–Lambert law).
  - Outputs:
    - `processed.csv` (cleaned dataset)
    - `results.txt` (summary report)
    - `plot.png` (spectrum visualization)

- **Data Files:**
  - Place sample CSVs in the `data/` directory.

- **Output Files:**
  - All results are saved in `python_backend/output/`.

---

## Folder Structure

```
spectrophotometer/
├── c_frontend/                # (Optional) C helper files
├── data/                      # Sample CSV datasets
├── docs/                      # Documentation
├── python_backend/
│   ├── analysis.py            # Main analysis script
│   ├── plotting.py            # Plotting script
│   ├── output/                # Output files (results.txt, processed.csv, plot.png)
│   └── spectral_os_cli.py     # (Optional) Python CLI version
├── file_dialog.py             # Python file dialog helper for C shell
├── Makefile                   # Build instructions
├── requirements.txt           # Python dependencies
├── spectralos.c               # Main C shell source
├── spectralos_menu.exe        # Compiled CLI executable
└── README.md                  # This file
```

---

## Usage

### 1. Build the CLI

```sh
gcc -o spectralos_menu spectralos.c
```

### 2. Run SpectralOS

```sh
./spectralos_menu
```

### 3. Commands

- `load` — Open file dialog to select a CSV, or `load <file>` to specify path.
- Use W/S and Enter to navigate the menu after loading.
- `analyze` — Process the loaded file.
- `results` — Show formatted results.
- `plot` — Generate and view spectrum plot.
- `exit` — Quit the application.

---

## Makefile Example

```makefile
CC=gcc
CFLAGS=-Wall -O2

all: spectralos_menu

spectralos_menu: spectralos.c
	$(CC) $(CFLAGS) -o spectralos_menu spectralos.c

clean:
	del spectralos_menu.exe
```

- Run `make` to build.
- Run `make clean` to remove the executable.

---

## Python Requirements

Install dependencies with:

```sh
pip install -r requirements.txt
```

Contents of `requirements.txt`:
```
pandas
numpy
matplotlib
```

---

## How It Works

1. **Startup:**  
   Launches with a welcome message and prompt.

2. **Loading Data:**  
   Use `load` to select a CSV file. After loading, a menu appears for further actions.

3. **Analysis:**  
   The C shell calls the Python backend, which processes the CSV and writes results to `python_backend/output/`.

4. **Results & Plot:**  
   View results in the CLI or generate a plot, which opens automatically.

5. **Exit:**  
   Clean shutdown with a thank-you message.

---

## Notes

- All output files are saved in `python_backend/output/`.
- The C shell uses a Python helper (`file_dialog.py`) for file selection.
- The project is cross-platform but tested primarily on Windows.

---
