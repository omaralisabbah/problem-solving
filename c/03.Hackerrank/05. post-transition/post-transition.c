/*
 * HackerRank Challenge: Post Transition
 *
 * Author: [omaralisabbah]
 *
 * Description:
 * This program models a country with towns, post offices, and packages.
 * Each package has an ID and weight. Each post office has a weight range
 * and stores packages. Each town has a name and multiple post offices.
 *
 * The program supports queries to:
 *   1. Print all packages in a given town.
 *   2. Transfer acceptable packages from one town's post office to another.
 *   3. Find the town with the most packages.
 *
 * Input format:
 *   - Number of towns
 *   - For each town: name, number of offices, then office details
 *   - For each office: number of packages, min weight, max weight, then packages
 *   - Number of queries
 *   - Each query: type and parameters
 *
 * Output format:
 *   - Depends on query type (print packages, transfer, or report town with most packages).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6   // Maximum length for town names and package IDs

/* -------------------- STRUCT DEFINITIONS -------------------- */

// Package structure: represents a single package with ID and weight
struct package {
    char* id;
    int weight;
};
typedef struct package package;

// Post office structure: represents a post office with weight limits and packages
struct post_office {
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};
typedef struct post_office post_office;

// Town structure: represents a town with a name and multiple post offices
struct town {
    char* name;
    post_office* offices;
    int offices_count;
};
typedef struct town town;

/* -------------------- FUNCTION IMPLEMENTATIONS -------------------- */

/*
 * Function: print_all_packages
 * ----------------------------
 * Prints all packages in a town in the required format.
 *
 * Parameters:
 *   t - town struct
 *
 * Output:
 *   Town name followed by each office index and its packages.
 */
void print_all_packages(town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\n\t\t%s", t.offices[i].packages[j].id);
        }
        printf("\n");
    }
}

/*
 * Function: send_all_acceptable_packages
 * --------------------------------------
 * Transfers packages from one office to another if they fit within
 * the target office's weight constraints.
 *
 * Parameters:
 *   source - pointer to source town
 *   source_office_index - index of source office
 *   target - pointer to target town
 *   target_office_index - index of target office
 *
 * Behavior:
 *   - Packages within target office's weight range are moved.
 *   - Remaining packages stay in source office.
 */
void send_all_acceptable_packages(town* source, int source_office_index,
                                  town* target, int target_office_index) {
    post_office* src = &source->offices[source_office_index];
    post_office* dst = &target->offices[target_office_index];
    
    // Temporary array for packages that remain in source
    package* new_src_packages = malloc(sizeof(package) * src->packages_count);
    int new_src_count = 0;
    
    for (int i = 0; i < src->packages_count; i++) {
        package p = src->packages[i];
        if (p.weight >= dst->min_weight && p.weight <= dst->max_weight) {
            // Acceptable package: move to target office
            dst->packages = realloc(dst->packages, sizeof(package) * (dst->packages_count + 1));
            dst->packages[dst->packages_count++] = p;
        } else {
            // Not acceptable: keep in source
            new_src_packages[new_src_count++] = p;
        }
    }
    
    // Replace source packages with remaining ones
    free(src->packages);
    src->packages = new_src_packages;
    src->packages_count = new_src_count;
}

/*
 * Function: town_with_most_packages
 * ---------------------------------
 * Finds the town with the largest total number of packages.
 *
 * Parameters:
 *   towns - array of towns
 *   towns_count - number of towns
 *
 * Returns:
 *   Town struct with the most packages.
 */
town town_with_most_packages(town* towns, int towns_count) {
    int max_count = -1;
    town result = towns[0];
    for (int i = 0; i < towns_count; i++) {
        int total = 0;
        for (int j = 0; j < towns[i].offices_count; j++) {
            total += towns[i].offices[j].packages_count;
        }
        if (total > max_count) {
            max_count = total;
            result = towns[i];
        }
    }
    return result;
}

/*
 * Function: find_town
 * -------------------
 * Finds a town by name.
 *
 * Parameters:
 *   towns - array of towns
 *   towns_count - number of towns
 *   name - name of town to find
 *
 * Returns:
 *   Pointer to the town struct.
 */
town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return &towns[0]; // guaranteed to exist
}

/* -------------------- MAIN FUNCTION -------------------- */

int main() {
    int towns_count;
    scanf("%d", &towns_count);
    town* towns = malloc(sizeof(town) * towns_count);

    // Read town data
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);

        // Read office data
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count,
                  &towns[i].offices[j].min_weight,
                  &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);

            // Read package data
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }

    // Process queries
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
        case 1: // Print all packages in a town
            scanf("%s", town_name);
            town* t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
            break;
        case 2: // Transfer acceptable packages
            scanf("%s", town_name);
            town* source = find_town(towns, towns_count, town_name);
            int source_index;
            scanf("%d", &source_index);
            scanf("%s", town_name);
            town* target = find_town(towns, towns_count, town_name);
            int target_index;
            scanf("%d", &target_index);
            send_all_acceptable_packages(source, source_index, target, target_index);
            break;
        case 3: // Find town with most packages
            printf("Town with the most number of packages is %s\n",
                   town_with_most_packages(towns, towns_count).name);
            break;
        }
    }
    return 0;
}
