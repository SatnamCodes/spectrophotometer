#include "utils.h"
#include <stdio.h>

int main() {
    int wavelength[100];
    float absorbance[100];
    int len;

    // Collect spectral data
    len = collect_data(wavelength, absorbance);

    // Save the data to CSV file
    const char *csv_path = "../data/spectrum.csv";
    FILE *test = fopen(csv_path, "w");
    if (!test) {
        perror("Error opening ../data/spectrum.csv");
        printf("Current working directory: ");
        system("cd");
        return 1;
    }
    fclose(test);
    save_data_csv(csv_path, wavelength, absorbance, len);

    printf("Data collection complete. Saved to %s\n", csv_path);

    // Call the Python analysis script
    printf("Running Python analysis...\n");
    int py_status = system("python ../python_backend/analysis.py ../data/spectrum.csv");
    if (py_status != 0) {
        printf("Python analysis failed.\n");
        return 1;
    }

    // Print the results from results.txt
    FILE *results = fopen("../python_backend/output/results.txt", "r");
    if (results) {
        char line[256];
        printf("\n--- Analysis Results ---\n");
        while (fgets(line, sizeof(line), results)) {
            printf("%s", line);
        }
        fclose(results);
    } else {
        printf("Could not open results.txt for reading.\n");
    }

    return 0;
}
