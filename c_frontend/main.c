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
    return 0;
}
