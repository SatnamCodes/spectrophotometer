#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int collect_data(int *wavelength, float *absorbance) {
    // Simulate collecting data from 400nm to 499nm
    for (int i = 0; i < 100; ++i) {
        wavelength[i] = 400 + i; 
        absorbance[i] = ((float) rand() / RAND_MAX); // Random absorbance between 0 and 1
    }
    return 100;  // Number of samples collected
}

void save_data_csv(const char *filename, int *wavelength, float *absorbance, int len) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    fprintf(file, "Wavelength,Absorbance\n");
    for (int i = 0; i < len; ++i) {
        fprintf(file, "%d,%.3f\n", wavelength[i], absorbance[i]);
    }
    fclose(file);
}

