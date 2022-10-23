#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct options{
    int E;
    int v;
    int e;
    int n;
    int T;
    int b;
    int t;
    int s;
};

void init(struct options *cat);
int parser(struct options *cats, char *str);
int processing(struct options *cats, char *file, int request, int *edit);
int counting(struct options *cats);
void optionN(struct options *cats, int BlankLine, int edit, int *request);
void optionE(struct options *cats, int *BlankLine, int *edit, int *num_BlankLine);
void optionB(struct options *cats, int BlankLine, int edit, int *request);
void optionT(struct options *cats, char group);
void PostProcessing(struct options *cats, char group, int *edit, int countCats);

int main(int argc, char **argv) {
    int error = 0;
    struct options cats;
    init(&cats);
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (parser(&cats, argv[i])) {
                error = 1;
                break;
            }
        }
    }
    if (!error) {
        int request = 1, edit = 1;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-')
                request = processing(&cats, argv[i], request, &edit);
        }
    }
    return 0;
}

void init(struct options *cat) {
    cat->e = 0;
    cat->E = 0;
    cat->v = 0;
    cat->n = 0;
    cat->t = 0;
    cat->T = 0;
    cat->s = 0;
    cat->b = 0;
}

void optionN(struct options *cats, int BlankLine, int edit, int *request) {
    if (BlankLine == 0 && cats->n == 1) {
        if (edit) {
            printf("%6d\t", *request);
            *request += 1;
        }
    }
}

void optionE(struct options *cats, int *BlankLine, int *edit, int *num_BlankLine) {
    if (cats->e || cats->E)
        printf("$");
    if (*BlankLine == 0)
        *num_BlankLine += 1;
    printf("\n");
    *BlankLine = 0;
    *edit = 1;
}

void optionB(struct options *cats, int BlankLine, int edit, int *request) {
    if (BlankLine == 0 && cats->b == 1) {
        if (edit) {
            printf("%6d\t", *request);
            *request += 1;
        }
    }
}

void optionT(struct options *cats, char group) {
    if (group == '\t') {
        if (cats->t || cats->T) {
            printf("^I");
        } else {
            printf("%c", group);
        }
    } else if (((group < 32 && group >= 0) || group == 127) && cats->v) {
        printf("^%c", group + 64);
    } else {
        printf("%c", group);
    }
}

void PostProcessing(struct options *cats, char group, int *edit, int countCats) {
    if (group != '\n') {
       *edit = 0;
        if ((cats->b || cats->n) && countCats == 1) {
            printf("\n");
            *edit = 1;
        }
    } else {
        *edit = 1;
    }
}

int processing(struct options *cats, char *file, int request, int *edit) {
    if (cats->b)
        cats->n = 0;
    if (cats->t || cats->e)
        cats->v = 1;
    char group;
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("cat: can't open '%s': No such file or directory\n", file);
    } else {
        int BlankLine = 0, num_BlankLine = 0, countCats = counting(cats);
        while (fscanf(fp, "%c", &group) != -1) {
            if (group == '\n' && (BlankLine == 0 && num_BlankLine != 0 && cats->s == 1))
                continue;
            optionN(cats, BlankLine, *edit, &request);
            if (group == '\n') {
            optionE(cats, &BlankLine, edit, &num_BlankLine);
            } else {
                num_BlankLine = 0;
                optionB(cats, BlankLine, *edit, &request);
                optionT(cats, group);
                BlankLine++;
            }
        }
        PostProcessing(cats, group, edit, countCats);
        fclose(fp);
    }
    return request;
}

int counting(struct options *cats) {
    int count = 0;
    count = cats->e + cats->E + cats->v + cats->n + cats->t + cats->T + cats->s + cats->b;
    return count;
}

int pointer_options(struct options *cats, char c) {
    int error = 0;
    switch (c) {
        case 'e':
            cats->e = 1;
            break;
        case 'E':
            cats->E = 1;
            break;
        case 'n':
            cats->n = 1;
            break;
        case 't':
            cats->t = 1;
            break;
        case 'T':
            cats->T = 1;
            break;
        case 's':
            cats->s = 1;
            break;
        case 'b':
            cats->b = 1;
            break;
        case 'v':
            cats->v = 1;
            break;
        default:
            printf("cat: invalid option -- '%c'\n", c);
            printf("Try 'cat --help' for more information.\n");
            error = 1;
    }
    return error;
}

int parser(struct options *cats, char *str) {
    int error = 0;
    str++;
    while (*str != '\0') {
        if (pointer_options(cats, *str)) {
            error = 1;
            break;
        }
        str++;
    }
    return error;
}
