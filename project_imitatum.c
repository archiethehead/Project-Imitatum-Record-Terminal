////////////////////////////////////
//PROJECT-IMITATUM-RECORD-TERMINAL//
////////////////////////////////////

//Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Classes
struct Record {

    int record_num;
    int type;
    int rebelled;

};


//Functions
struct Record* read_record  () {

    //Allocate memroy for the array
    struct Record *records = malloc(65535 * sizeof(struct Record));
    if (!records) { perror("malloc failed"); return NULL; }

    //Open the file, and read the binary
    FILE *fp = fopen("records.bin", "rb");
    if (!fp) { perror("fopen failed"); free(records); return NULL; }

    //Allocate binaries to the array
    size_t read = fread(records, sizeof(struct Record), 65535, fp);
    fclose(fp);

    return records;

}


//Basic linear search
struct Record* find_record(struct Record *records, int size, int target) {

    for (int i = 0; i < size; i++) {

        if (records[i].record_num == target) {

            return &records[i]; 
        
        }
    }

    return NULL;
}

int permissions_command() {
    
    //Permission variables
    int num = 0;
    char comm[26];

    //Command input
    printf("    ");
    fgets(comm, sizeof(comm), stdin);
    comm[strcspn(comm, "\n")] = 0;


    //Correct command verification
    if (strcmp(comm, "PROJIMITRECORDOUT = 1") == 0) {

        num = 1;

    }

    return num;
}

void output_stats() {

    //Data variables
    struct Record* agent_data = read_record();
    int human_count = 0;
    int human_conformed = 0;
    int imitation_count = 0;
    int imitation_conformed = 0;

    //Math per record compilation
    for (int i = 0; i <= 65534; i++){

        if (agent_data[i].type == 0) {
            human_count++;

            if (agent_data[i].rebelled == 0){

                human_conformed++;

            }

        } 
        
        else {

            imitation_count++;

            if (agent_data[i].rebelled == 0){
                
                imitation_conformed++;

            }


        }
    
    }

    //Extra stat maths
    int human_rebelled = (human_count - human_conformed);
    int imitation_rebelled = (imitation_count - imitation_conformed);

    double human_percentage_rebelled = (human_rebelled * 100.0 / human_count);
    double human_percentage_conformed = (human_conformed * 100.0 / human_count);

    double imitation_percentage_rebelled = (imitation_rebelled * 100.0 / imitation_count);
    double imitation_percentage_conformed = (imitation_conformed * 100.0 / imitation_count);

    // Print header with proper spacing
    printf("    \n%-10s %13s %10s %11s %21s %22s\n",
           "    Type", "      Total-Count", "  Rebelled", "Conformed",
           "Percentage-Rebelled", "Percentage-Conformed");
    printf("    %-10s %13s %10s %11s %21s %22s\n",
           "----", "-----------", "--------", "---------",
           "-------------------", "--------------------");

    // Human row
    printf("    %-10s %13d %10d %11d %21.2f %22.2f\n",
           "Human", human_count, human_rebelled, human_conformed,
           human_percentage_rebelled, human_percentage_conformed);

    // Imitation row
    printf("    %-10s %13d %10d %11d %21.2f %22.2f\n",
           "Imitation", imitation_count, imitation_rebelled, imitation_conformed,
           imitation_percentage_rebelled, imitation_percentage_conformed);


    getchar();

}

void output_records() {

    //Loop variables
    char buffer[2];
    struct Record* agent_data = read_record();

    //Agent outloop loop (0001 - FFFF)
    for (int i = 1; i <= 65534; i++) {
        printf("    SERIAL-NUMBER: 0x%x    STATUS: %s    LOYALTY: %s\n", agent_data[i].record_num,
        agent_data[i].type == 0 ? "Imitation" : "Human    ", agent_data[i].rebelled == 0 ? "Conformed" : "Rebelled"
    );
    }

    free(agent_data); 
    agent_data = NULL;
    getchar();
}

void output_specific_record() {

    //Agent output variables
    char agent[10];
    struct Record* agent_data = read_record();

    //Input logic
    printf("\n    Enter serial number here: ");
    fgets(agent, sizeof(agent), stdin);
    agent[strcspn(agent, "\n")] = 0; // remove newline

    //Linear search
    struct Record *r = find_record(agent_data, 65535, (int)strtol(agent, NULL, 16));
    if (r){

        printf("\n    SERIAL-NUMBER: 0x%x    STATUS: %s    LOYALTY: %s\n", r->record_num,
             r->type ? "Imitation" : "Human", r->rebelled ? "Rebelled" : "Conformed");
        getchar();
    }

    else {
        printf("    ERROR: Agent not found");
        getchar();
    }

    free(agent_data);
    agent_data = NULL;
}

void menu() {

    //Menu variables
    char userin[26] = "";
    int user_perms = 0;

    while (1){

        //Menu print
        printf("\n    PROJECT IMITATUM RECORD TERMINAL");
        printf("\n    --------------------------------");
        printf("\n\n    1: Output all records");
        printf("\n    2: Output specific record");
        printf("\n    3: Output statistics");
        printf("\n    4: Exit");
        printf("\n\n    Enter your command here: ");

        fgets(userin, sizeof(userin), stdin);
        userin[strcspn(userin, "\n")] = 0;


        //Command handler =
        if (strcmp(userin, "USERPERMSOVERRIDE_^$64") == 0){

            user_perms = permissions_command();

        };


        //Output every record from the project
        if (strcmp(userin, "1") == 0) {
            
            if (user_perms == 1) {

                output_records();

            }

            else {

                printf("    PERMISSIONS ERROR");
                getchar();

            }

        }


        //Output a specific record from the project
        if (strcmp(userin, "2") == 0) {
            
            if (user_perms == 1){

                output_specific_record();

            }

            else {

                printf("    PERMISSIONS ERROR");
                getchar();

            }
                

        }

        //Output a specific record from the project
        if (strcmp(userin, "3") == 0) {
            
            if (user_perms == 1){

                output_stats();
            
            }

            else {

                printf("    PERMISSIONS ERROR");
                getchar();

            }
                

        }

        if (strcmp(userin, "4") == 0) {
            break;
        }

    system("cls");

    };
}

int main() {
    printf("\033[38;5;214m");

    menu();   
    return 0;
}