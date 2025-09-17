#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #define SLEEP(ms) Sleep(ms)
    #ifndef MAX_PATH_LOCAL
        #define MAX_PATH_LOCAL 256
    #endif
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms)*1000)
    #define MAX_PATH_LOCAL 256
#endif

void typewriter_print(const char* text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        SLEEP(delay_ms);
    }
}

void show_startup_animation() {
    printf("\n=== Welcome to SpectralOS ===\n");
    printf("Advanced Spectrophotometer Analysis Suite\n\n");
    
    printf("Booting SpectralOS...\n");
    char progress_chars[] = "##########";
    for (int i = 0; i <= 10; i++) {
        printf("\r[");
        for (int j = 0; j < i; j++) printf("#");
        for (int j = i; j < 10; j++) printf(".");
        printf("] %d%%", i * 10);
        fflush(stdout);
        SLEEP(200);
    }
    printf("  Ready.\n\n");
}

void show_analysis_animation() {
    const char* steps[] = {
        "Cleaning data",
        "Computing absorbance", 
        "Finding peak wavelength",
        "Estimating concentration",
        "Done!"
    };
    
    printf("Running analysis...\n");
    for (int step = 0; step < 5; step++) {
        printf("\r[");
        for (int i = 0; i < (step + 1) * 2; i++) printf("#");
        for (int i = (step + 1) * 2; i < 10; i++) printf(" ");
        printf("] %s", steps[step]);
        fflush(stdout);
        SLEEP(800);
    }
    printf("\n");
}

void print_formatted_results(const char* filepath) {
    FILE *f = fopen(filepath, "r");
    if (!f) {
        printf("No results found.\n");
        return;
    }
    
    printf("SpectralOS Analysis Report\n");
    printf("--------------------------\n");
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
    
    printf("--------------------------\n");
    printf("Status: SUCCESS\n\n");
}

void show_exit_animation() {
    typewriter_print("Shutting down SpectralOS...\n", 50);
    typewriter_print("Thank you for exploring the spectrum 🌈\n", 50);
    typewriter_print("Goodbye!\n", 50);
}

void print_help() {
    printf("Commands:\n");
    printf("  help           Show this help message\n");
    printf("  load <file>    Load a dataset CSV file\n");
    printf("  analyze        Run Python analysis on loaded file\n");
    printf("  results        Show analysis results\n");
    printf("  plot           Generate spectrum plot (if available)\n");
    printf("  exit           Quit SpectralOS\n");
}

void show_file_options_menu(const char* loaded_file) {
    int choice = 0;
    int key;
    
    while (1) {
        // Clear screen and show menu
        system("cls");
        printf("\n=== File Options Menu ===\n");
        printf("File: %s\n\n", loaded_file);
        
        // Menu options
        const char* options[] = {
            "Analyze Data",
            "Show Results", 
            "Generate Plot",
            "Load New File",
            "Back to Main Menu"
        };
        
        for (int i = 0; i < 5; i++) {
            if (i == choice) {
                printf("> %s\n", options[i]);
            } else {
                printf("  %s\n", options[i]);
            }
        }
        
        printf("\nUse W/S keys to navigate, Enter to select: ");
        fflush(stdout);
        
        #ifdef _WIN32
            key = _getch();
        #else
            key = getchar();
        #endif
        
        if (key == 'w' || key == 'W' || key == 72) { // Up arrow or W
            choice = (choice - 1 + 5) % 5;
        } else if (key == 's' || key == 'S' || key == 80) { // Down arrow or S
            choice = (choice + 1) % 5;
        } else if (key == '\n' || key == '\r' || key == 13) { // Enter
            // Execute selected option
            char py_cmd[512];
            int ret;
            
            switch (choice) {
                case 0: // Analyze
                    system("cls");
                    printf("\nAnalyzing data...\n");
                    // show_analysis_animation();
                    snprintf(py_cmd, sizeof(py_cmd), "C:/Users/satna/AppData/Local/Programs/Python/Python313/python.exe python_backend/analysis.py \"%s\"", loaded_file);
                    ret = system(py_cmd);
                    if (ret == 0) {
                        printf("Analysis complete!\n");
                    } else {
                        printf("Analysis failed.\n");
                    }
                    printf("Press any key to continue...");
                    #ifdef _WIN32
                        _getch();
                    #else
                        getchar();
                    #endif
                    break;
                    
                case 1: // Results
                    system("cls");
                    print_formatted_results("python_backend/output/results.txt");
                    printf("Press any key to continue...");
                    #ifdef _WIN32
                        _getch();
                    #else
                        getchar();
                    #endif
                    break;
                    
                case 2: // Plot
                    system("cls");
                    printf("Generating spectrum plot...\n");
                    ret = system("C:/Users/satna/AppData/Local/Programs/Python/Python313/python.exe python_backend/plotting.py");
                    if (ret == 0) {
                        printf("Spectrum saved and opened!\n");
                        system("start python_backend/output/plot.png");
                    } else {
                        printf("Plot generation failed.\n");
                    }
                    printf("Press any key to continue...");
                    #ifdef _WIN32
                        _getch();
                    #else
                        getchar();
                    #endif
                    break;
                    
                case 3: // Load new file
                    return; // Go back to load command
                    
                case 4: // Back to main
                    system("cls");
                    return;
            }
        }
    }
}

int main() {
    char cmd[64], arg[MAX_PATH_LOCAL], loaded_file[MAX_PATH_LOCAL] = "";
    
    show_startup_animation();
    printf("Type 'help' for commands.\n");
    while (1) {
        printf("SpectralOS> ");
        fflush(stdout);
        if (scanf("%63s", cmd) != 1) break;

        if (strcmp(cmd, "help") == 0) {
            print_help();
        } else if (strcmp(cmd, "load") == 0) {
            int c = getchar();
            // Check if user typed 'load' only (no argument)
            if (c == '\n' || c == EOF) {
                // Open file dialog using Python
                printf("Opening file dialog...\n");
                FILE *fp = _popen("C:/Users/satna/AppData/Local/Programs/Python/Python313/python.exe file_dialog.py", "r");
                if (fp) {
                    if (fgets(arg, MAX_PATH_LOCAL, fp)) {
                        // Remove trailing newline
                        size_t len = strlen(arg);
                        if (len > 0 && arg[len-1] == '\n') arg[len-1] = '\0';
                        if (strlen(arg) > 0) {
                            strncpy(loaded_file, arg, MAX_PATH_LOCAL);
                            printf("Loaded file: %s\n", loaded_file);
                        } else {
                            printf("No file selected.\n");
                        }
                    }
                    _pclose(fp);
                } else {
                    printf("Could not open file dialog.\n");
                }
                
                // Show menu options after loading
                if (strlen(loaded_file) > 0) {
                    show_file_options_menu(loaded_file);
                }
            } else {
                // User provided a file path as argument
                // Read the rest of the line
                char temp[MAX_PATH_LOCAL];
                if (fgets(temp, MAX_PATH_LOCAL, stdin)) {
                    // Remove leading/trailing whitespace and newline
                    char *start = temp;
                    while (*start == ' ' || *start == '\t') start++;
                    char *end = start + strlen(start) - 1;
                    while (end > start && (*end == '\n' || *end == '\r' || *end == ' ')) *end-- = '\0';
                    
                    if (strlen(start) > 0) {
                        strncpy(loaded_file, start, MAX_PATH_LOCAL);
                        printf("Loaded file: %s\n", loaded_file);
                        // Show menu options after loading
                        show_file_options_menu(loaded_file);
                    } else {
                        printf("Usage: load <file>\n");
                    }
                } else {
                    printf("Usage: load <file>\n");
                }
            }
        } else if (strcmp(cmd, "analyze") == 0) {
            if (strlen(loaded_file) == 0) {
                printf("No file loaded. Use 'load <file>' first.\n");
            } else {
                // show_analysis_animation();
                char py_cmd[512];
                snprintf(py_cmd, sizeof(py_cmd), "C:/Users/satna/AppData/Local/Programs/Python/Python313/python.exe python_backend/analysis.py \"%s\"", loaded_file);
                int ret = system(py_cmd);
                if (ret == 0) {
                    printf("Analysis complete!\n");
                } else {
                    printf("Analysis failed.\n");
                }
            }
        } else if (strcmp(cmd, "results") == 0) {
            print_formatted_results("python_backend/output/results.txt");
        } else if (strcmp(cmd, "plot") == 0) {
            printf("Generating spectrum plot...\n");
            int ret = system("C:/Users/satna/AppData/Local/Programs/Python/Python313/python.exe python_backend/plotting.py");
            if (ret == 0) {
                printf("Spectrum saved to output/plot.png\n");
                // Open the plot image
                system("start python_backend/output/plot.png");
            } else {
                printf("Plot generation failed.\n");
            }
        } else if (strcmp(cmd, "exit") == 0) {
            show_exit_animation();
            break;
        } else {
            printf("Unknown command. Type 'help' for a list of commands.\n");
        }
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return 0;
}
