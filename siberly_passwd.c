/*Usage: ./siberly_passwd -n <number> -w <words> -f </path/to/dir.txt> */
/*
*This code is used to automatically generate the blasting required ...
*More information or help:https://github.com/Siberly
*If you want to join us,Please contact:
*2637192651@qq.com
*siberrrrr@outlook.com/siberlysily@outlook.com
*siberlysily@gmail.com
*The program must be compiled before it can be executed, and the C environment must be available
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#define MAX_SIZE 100

void generate_combinations(const char *word, int length, FILE *fp, char *result, int position) {
    if (position == length) {
        result[position] = '\0';
        fprintf(fp, "%s\n", result); 
        return;
    }

    size_t word_length = strlen(word); 
    size_t i; 
    for (i = 0; i < word_length; i++) {
        result[position] = word[i]; 
        generate_combinations(word, length, fp, result, position + 1); 
    }
}

void generate_dictionary(int n, const char *word, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    char result[MAX_SIZE];
    size_t total_combinations = 0;
    int length;
    for (length = 1; length <= n; length++) {
        total_combinations += (size_t)pow(strlen(word), length);
    }

    size_t completed_combinations = 0;
    for (length = 1; length <= n; length++) {
        generate_combinations(word, length, fp, result, 0);
        completed_combinations += (size_t)pow(strlen(word), length); 

       
        printf("\rProgress: [%-50s] %.2f%%", 
               "##############################################################################" + (50 - (50 * completed_combinations / total_combinations)),
               (completed_combinations * 100.0) / total_combinations);
        fflush(stdout); 
    }

    fclose(fp);
    printf("\nwords contained:%d/t%s",n,word);
    printf("\nThe total number of combinations is:%d",total_combinations);
    printf("\nDictionary generated in '%s'.", filename);
    printf("\nThe Permissions:chmod 774 %s",filename);
    printf("\nUsage: .siberly_passwd -n <number> -w <word> -f </path/to/dir.txt>");
}

int main(int argc, char *argv[]) {
    if (argc != 7 || strcmp(argv[1], "-n") != 0 || strcmp(argv[3], "-w") != 0 || strcmp(argv[5], "-f") != 0) {
        printf("Invalid arguments. Please use: ./bootword.exe -n <number> -w <word> -f </path/to/dir.txt>\n");
        return 1;
    }

    int n = atoi(argv[2]);
    if(n <= 0 || n > MAX_SIZE) { 
        printf("Please provide a valid positive number for <number> and it should be less than or equal to %d.\n", MAX_SIZE);
        return 1;
    }
    
    const char *word = argv[4];
    const char *filename = argv[6];

    generate_dictionary(n, word, filename);

    return 0;
}
