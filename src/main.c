#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Gene{
    int id;
    int value;
    int power;
    struct Gene *next;
}Gene;

typedef struct Chromosome{
    int id;
    Gene *head_gene;
    int fitness;
    struct Chromosome *next;
}Chromosome;

void print_all_genes(Gene * gene){
    while(gene != NULL){
        printf("%d:",gene->value);
        gene = gene->next;
    }
    printf("\b ");
    //printf("\n");
}  // prints all genes in one chromosome

void print_all_chromosomes(Chromosome * chromosome){
    while(chromosome != NULL){
        print_all_genes(chromosome->head_gene);
        printf("-> %d",chromosome->fitness);

        chromosome = chromosome->next;
        printf("\n");
    }


} // print all chromosomes with their genes

void swap(struct Chromosome *a, struct Chromosome *b)
{
    int temp = a->fitness;
    Gene * temp_ = a->head_gene;
    a->fitness = b->fitness;
    a->head_gene = b->head_gene;
    b->fitness = temp;
    b->head_gene = temp_;
} // swaps two chromosomes

void bubbleSort(struct Chromosome *start)
{
    int swapped, i;
    struct Chromosome *ptr1;
    struct Chromosome *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->fitness > ptr1->next->fitness)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}   // sorts all chromosomes

void add_gene(int value, Gene ** head, int power) {
    if ((*head) == NULL){
        (*head) = (Gene*)malloc(sizeof(Gene));
        (*head)->next = NULL;
        (*head)->value = value;
        (*head)->power = power;
    }

    else{
        Gene (*temp) = (*head);
        while ((temp)->next != NULL){
            temp = temp->next;
        }
        temp->next = (Gene*)malloc(sizeof(Gene));
        temp->next->value = value;
        temp->next->power = power;
        temp->next->next = NULL;
    }

}   // adds gene at the end

void add_chromosome(Gene ** gene , int fitness,Chromosome ** root) {
    if ((*root) == NULL){
        (*root) = (Chromosome*)malloc(sizeof(Chromosome));
        (*root)->next=NULL;
        (*root)->fitness = fitness;
        (*root)->head_gene = *gene;
    } else{
        Chromosome (*temp) = (*root);
        while ((temp)->next != NULL){
            temp = temp->next;
        }
        temp->next = (Chromosome*)malloc(sizeof(Chromosome));
        temp->next->fitness = fitness;
        temp->next->head_gene = *gene;
    }
}   // adds chromosomes at the end

int pow(int x, int power){
    int i, sonuc = 1; 
    for (i = 0; i < power; i++)
        sonuc = sonuc * x; 

    return sonuc;
}   // calculates genes power for fitness calculation

int compute_fitness(Chromosome * root){
    Chromosome * iter;
    iter = root;
    int fitness = 0;
    Gene * head = iter->head_gene;
    while (head != NULL){
      
        fitness = fitness + (head->value * head->power);
        head = head->next;
    }
    return fitness;
}   // calculates all fitness values of whole chromosomes

Chromosome * selection(Chromosome * root, int index){
    Chromosome * target_chromosome;
    Chromosome * iter_chromosome;
    iter_chromosome = root;
    for (int i = 0; i < index-1; i++) {
        iter_chromosome = iter_chromosome->next;
    }
    target_chromosome = iter_chromosome;
    return target_chromosome;
} // selects chromosome for other functions

void mutate(Chromosome * root, int index){
    Chromosome * iter;
    iter = root;
    Gene * head = iter->head_gene;
    for (int i = 0; i < index-1; i++) {
        head = head->next;
    }
    if (head->value == 1){
        head->value = 0;
    } else if (head->value == 0){
        head->value = 1;
    }

} // mutate function

void best_chromosome_update(Chromosome *root_of_chromosome,Chromosome * best_chromosome,int PROB_SIZE){
    int i;



    for(i=0;i<PROB_SIZE;i++){

    }
}

void xover(Gene ** first_gene, Gene ** second_gene, int start, int finish){
    Gene (*iter_first) = (*first_gene);
    Gene (*iter_second) = (*second_gene);
    int temp = 0;
    for (int i = 0; i < start-1; i++) {
        iter_first = iter_first->next;
        iter_second = iter_second->next;
        
    }
    for (start; start<= finish ; start++) {
        temp = iter_first->value;
        iter_first->value = iter_second->value;
        iter_second->value = temp;
        
        iter_first = iter_first->next;
        iter_second = iter_second->next;
        //(*first_gene) = (*first_gene)->next;
        //(*second_gene) = (*second_gene)->next;
    }
} // xover function


int main(int argc, char *argv[]) {

    // open files and getting ready for accessing
    // initializing my supportive variables

    FILE *population_text = fopen("population","r+");
    FILE *mutate_text = fopen("mutate","r");
    FILE *xover_text = fopen("xover","r");
    FILE *selection_text = fopen("selection","r");
    int PROBLEM_SIZE = atoi(argv[1]);
    int POP_SIZE = atoi(argv[2]);
    int MAX_GEN = atoi(argv[3]);
    printf("GENERATION: 0\n");
    char c;int text_i = 0;int text_j = 0;
    while ( (c=fgetc(population_text)) != EOF)
    {
        text_i++;
    }
    char* content = (char*)malloc(text_i * sizeof(char) + 1);
    char* buf = (char*)malloc(text_i * sizeof(char) + 1);
    rewind(population_text);
    for(text_j = 0;text_j < text_i;text_j++)
    {
        content[text_j] = fgetc(population_text);
    }

    char c2;text_i=0;text_j=0;
    while (( c2=fgetc(mutate_text)) != EOF)
    {
        text_i++;
    }
    char* content_mutate = (char*)malloc(text_i * sizeof(char)+1);
    char* buf_mutate = (char*)malloc(text_i * sizeof(char)+1);
    rewind(mutate_text);
    for(text_j=0;text_j<text_i;text_j++){
        content_mutate[text_j]=fgetc(mutate_text);
    }

    char c3;text_i=0;text_j=0;
    while (( c3=fgetc(selection_text)) != EOF)
    {
        text_i++;
    }
    char* content_selection = (char*)malloc(text_i * sizeof(char)+1);
    char* buf_selection = (char*)malloc(text_i * sizeof(char)+1);
    rewind(selection_text);
    for(text_j=0;text_j<text_i;text_j++){
        content_selection[text_j]=fgetc(selection_text);
    }

    char c4;text_i=0;text_j=0;
    while (( c4=fgetc(xover_text)) != EOF)
    {
        text_i++;
    }
    char* content_xover = (char*)malloc(text_i * sizeof(char)+1);
    char* buf_xover = (char*)malloc(text_i * sizeof(char)+1);
    rewind(xover_text);
    for(text_j=0;text_j<text_i;text_j++){
        content_xover[text_j]=fgetc(xover_text);
    }
    char *line,*found,*string;
    char *word;
    char *selection_line,*xover_line,*mutate_line;
    int chromosome_counter = 0;
    Chromosome * root_of_chromosome = NULL;


    // reading population text and building my linked list structure (generation 0)

    for (line = strtok (content, "\n"); line != NULL; line = strtok (line+strlen(line)+1, "\n")){
        strncpy (buf, line, text_i);
        string = strdup(line);
        int sayi = 0;
        int fitness = 0;
        Gene * head_gene = NULL;
        while ((found = strsep(&string,":")) != NULL){  // genleri atayalim
            int found_ = atoi(found);       // 0 ya da 1
            int power = PROBLEM_SIZE - sayi - 1;
            fitness = fitness + (found_ * pow(2,power));
            //printf("pow = %d\n",pow(2,power));
            add_gene(found_,&head_gene,pow(2,power));
            sayi++;
        }
        add_chromosome(&head_gene,fitness,&root_of_chromosome);
        chromosome_counter++;
    }
    bubbleSort(root_of_chromosome);
    print_all_chromosomes(root_of_chromosome);
    Chromosome *best_chromosome = (Chromosome *) malloc(sizeof(Chromosome)); 
    best_chromosome->head_gene = (Gene *)malloc(sizeof(Gene));
    Gene *iterator_of_root = root_of_chromosome->head_gene;
    Gene *iterator_of_best = best_chromosome->head_gene;

    int m;
    for(m=0;m<PROBLEM_SIZE;m++){
        iterator_of_best->value = iterator_of_root->value;

        if(m != (PROBLEM_SIZE-1)){
            iterator_of_best->next = (Gene *) malloc(sizeof(Gene));
            iterator_of_best = iterator_of_best->next;
            iterator_of_root = iterator_of_root->next;
        }

    }
    best_chromosome->fitness = root_of_chromosome->fitness;




//    Chromosome * best_chromosome = (Chromosome *) &root_of_chromosome;
//    best_chromosome->fitness = root_of_chromosome->fitness;
//    best_chromosome->head_gene = root_of_chromosome->head_gene;
    printf("Best chromosome found so far: ");
    print_all_genes(best_chromosome->head_gene);
    printf("-> %d\n",best_chromosome->fitness);


    // iterating operations MAX_GEN times

    int counter_of_generation = 1;
    for (counter_of_generation; counter_of_generation <= MAX_GEN; counter_of_generation++){
        printf("GENERATION: %d\n",counter_of_generation);
        selection_line = strsep(&content_selection,"\n");
        xover_line = strsep(&content_xover, "\n");
        mutate_line = strsep(&content_mutate,"\n");

        // reading 3 text files at the same time in here

        char* selector[POP_SIZE/2+1];
        int counter=0;
        char* some_int = strtok(selection_line," ");
        while (some_int !=NULL ){
            selector[counter] = some_int;
            counter++;
            some_int = strtok(NULL," ");
        }
        for (int j = 0; j < POP_SIZE/2; j++) {
            counter = 0;
            int first_chromo, second_chromo, xover_start, xover_end, mutate_index;
            char* splitter = strtok(selector[j],":");
            while (splitter != NULL){
                if (counter == 0){
                    first_chromo = atoi(splitter);
                } else if (counter == 1){
                    second_chromo = atoi(splitter);
                }
                counter++;
                splitter = strtok(NULL," ");
            }
            char* xover_splitter = strtok(xover_line,":");
            counter = 0;
            while (xover_splitter != NULL){
                if (counter==0){
                    xover_start = atoi(xover_splitter);
                } else if (counter ==1){
                    xover_end = atoi(xover_splitter);
                }
                counter++;
                xover_splitter = strtok(NULL,":");
            }
            mutate_index = atoi(mutate_line);

            // calling functions with parameters which i manipulated above there
            Chromosome * first_chromosome = selection(root_of_chromosome,first_chromo);
            Chromosome * second_chromosome = selection(root_of_chromosome,second_chromo);
            xover(&first_chromosome->head_gene, &second_chromosome->head_gene, xover_start, xover_end);
            mutate(first_chromosome,mutate_index);
            mutate(second_chromosome,mutate_index);
        }


        // calculating all chromosome fitness values
        Chromosome * iter = root_of_chromosome;
        for (int i = 0; i < POP_SIZE; i++) {
            iter->fitness = compute_fitness(iter);
            iter = iter->next;
        }

        // sorting chromosomes
        bubbleSort(root_of_chromosome);

        // checking the best chromosome found so far


        iterator_of_best = best_chromosome->head_gene;
        iterator_of_root = root_of_chromosome->head_gene;
        if(root_of_chromosome->fitness < best_chromosome->fitness){
            for(m=0;m<PROBLEM_SIZE;m++) {
                iterator_of_best->value = iterator_of_root->value;
                iterator_of_best = iterator_of_best->next;
                iterator_of_root = iterator_of_root->next;
            }
            best_chromosome->fitness  =root_of_chromosome->fitness;
        }

        // printing all generation
        print_all_chromosomes(root_of_chromosome);

        // printing best chromosome found so far
        printf("Best chromosome found so far: ");
        print_all_genes(best_chromosome->head_gene);
        printf("-> %d\n",best_chromosome->fitness);

    }


    fclose(population_text);
    fclose(mutate_text);
    fclose(xover_text);
    fclose(selection_text);
    return 0;
}