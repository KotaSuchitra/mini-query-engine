#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5

// --- Table Definition ---
struct Student {
    char name[20];
    int age;
    char city[20];
};

// --- Sample Data ---
struct Student students[MAX_STUDENTS] = {
    {"suchi", 22, "Chennai"},
    {"sabari", 20, "Ongole"},
    {"deepthi", 22, "AP"},
    {"janu", 10, "Bangalore"},
    {"sravani", 29, "Bapatla"}
};

int table_size = 5;
int current_index = 0;     // For table scan iterator
struct Student *current_row = NULL; // For filter iterator

void table_scan_open();
struct Student *table_scan_next();
void table_scan_close();

void filter_open();
struct Student *filter_next();
void filter_close();

void projection_open();
void projection_next();
void projection_close();

// --- TABLE SCAN ---
void table_scan_open() {
    current_index = 0;
    printf("TableScan: opened table.\n");
}

struct Student* table_scan_next() {
    if (current_index >= table_size)
        return NULL;
    return &students[current_index++];
}

void table_scan_close() {
    current_index = 0;
    printf("TableScan: closed table.\n");
}

// --- FILTER OPERATOR ---
void filter_open() {
    printf("Filter: opened (city = 'AP').\n");
    table_scan_open();
}

struct Student* filter_next() {
    while ((current_row = table_scan_next()) != NULL) {
        if (strcmp(current_row->city, "Chennai") == 0) {
            return current_row;  // Return only matching rows
        }
    }
    return NULL; // No more matches
}

void filter_close() {
    printf("Filter: closed.\n");
    table_scan_close();
}

// --- PROJECTION OPERATOR ---
void projection_open() {
    printf("Projection: opened (name, age).\n");
    filter_open();
}

void projection_next() {
    struct Student *row;
    while ((row = filter_next()) != NULL) {
        printf("Result -> Name: %s, age: %d\n", row->name, row->age);
    }
}

void projection_close() {
    printf("Projection: closed (name, age).\n");
    filter_close();
}

// --- MAIN EXECUTION PIPELINE ---
int main() {
    projection_open();
    projection_next();
    projection_close();
    return 0;
}
