#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b)) // define for square


typedef struct {
    int height;    
    int width;     
    int *matrix;  
} Image;

void help(){ // just help
    printf("Usage:\n");
    printf("  ./figsearch --help\n");
    printf("  ./figsearch test FILE\n");
    printf("  ./figsearch hline FILE\n");
    printf("  ./figsearch vline FILE\n");
    printf("  ./figsearch square FILE\n");
    printf("Available commands:\n");
    printf("  --help      Shows this help message.\n");
    printf("  test        Checks if the bitmap is valid.\n");
    printf("  hline       Finds the longest horizontal line.\n");
    printf("  vline       Finds the longest vertical line.\n");
    printf("  square      Finds the largest square.\n");
    return;
}
void test_soubor(FILE* file,int cheak,Image *image){

    if(fscanf(file,"%d %d",&image->height, &image->width)!=2){//Reading height and width
        printf("Dont exsist height or width\n");
        fclose(file);
        if (cheak) {
            fprintf(stderr, "Invalid\n");
        }
        exit(EXIT_FAILURE);
    }

    image->matrix = (int *)malloc((image->height) * (image->width) * sizeof(int));//Giving memory for matrix 
    if (image->matrix == NULL) {
        printf("Error: Memory allocation failed for array.\n");
        fclose(file);
        if (cheak) {
            fprintf(stderr, "Invalid\n");
        }
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < (image->height) * (image->width); i++) {//Reading matrix in .txt
        if (fscanf(file, "%d", &((image->matrix)[i])) != 1) {
            printf("Error reading matrix data\n");
            free(image->matrix);
            fclose(file);
            if (cheak) {
            fprintf(stderr, "Invalid\n");
        }
            exit(EXIT_FAILURE);
        }

        if ((image->matrix)[i] != 0 && (image->matrix)[i] != 1) { // Cheaking for 0 or 1
            free(image->matrix);
            fclose(file);
            if (cheak) {
            fprintf(stderr, "Invalid\n");
        }
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
     if (cheak) {
        printf("Valid\n");
    }
    /*
    if(cheak){
        printf("Arrays is: \n");
        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                printf("%d ", (image->matrix)[i * (image->width) + j]);
            }
            printf("\n");
        }
    }*/

    return;
}
void hline_soubor(const Image *image){
    int max_length = 0, current_length = 0;
    int start_col = 0, end_col = 0;
    int row = 0;

    for(int i = 0; i <image->height;i++){// Iterate through each row of the matrix
        for (int j = 0; j < image->width; j++) {// Iterate through each column in the current row
            if (image->matrix[i * image->width + j] == 1) {//Cheaking if se currect pixel is black
                current_length++;
                if (current_length > max_length) {
                    max_length = current_length;
                    start_col = j - current_length + 1;
                    end_col = j;                      
                    row = i;  
                }
            }else{
                current_length = 0;//Reset the current line length if the line is interrupted
            }
        }
        current_length = 0;
    } 
    if (max_length > 0) {// If a line was found
        printf("%d %d %d %d\n",row, start_col, row, end_col);
    } else {
        fprintf(stderr, "Not found\n");// Print error if no line was found
    }        
}
void vline_soubor(const Image *image){
    int max_length = 0, current_length = 0;
    int start_row = 0, end_row = 0;
    int col = 0;
    for (int j = 0; j < image->width; j++) {// Loop through all columns
        for (int i = 0; i < image->height; i++) {// Loop through all rows in the current column
            if (image->matrix[i * image->width + j] == 1) {// Here we cheak currect pixel is black
                current_length++;// Increase the current line length
                if (current_length > max_length) {
                    max_length = current_length;
                    start_row = i - current_length + 1;
                    end_row = i;
                    col = j;
                }
            } else {
                current_length = 0;// Reset current length if the line is interrupted
            }
        }
        current_length = 0;
    }

    if (max_length > 0) {// If a line was found
        printf("%d %d %d %d\n",start_row, col, end_row, col);
    } else {
        fprintf(stderr, "Not found\n");// Print error if no line was found
    }
}
void square_soubor(const Image *image){
    int max_length = -1, current_length = 0;
    int top_left_x = -1, top_left_y = -1;
    for(int pos_x = 0; pos_x < image->height; pos_x++){
        for(int pos_y = 0; pos_y < image->width; pos_y++){
            if(image->matrix[pos_x * image->width + pos_y] == 1){
                current_length = 0;
                for(int i = 1; i < image->height - pos_x; i++){
                    if (image->matrix[(pos_x + i) * image->width + pos_y] == 0){
                        break;
                    }
                    current_length++; // equals max(i) - 1, so x[pos_x + current_length] would show angle of square
                }
                // We got bottom edge (for this column) of square in current_length

                current_length = min(current_length, image->width - pos_y - 1); // current_length can't be bigger than distance to right edge
                                                                                // otherwise out of bounds

                // Cheching if top row is full of black tiles
                for(int j = 1; j <= current_length; j++){
                    if (image->matrix[pos_x * image->width + pos_y + j] == 0){
                        current_length = j - 1; // if top tile in top row is white, square can't be bigger than distance to this tile
                        break;
                    }
                }
                
                for(; current_length > 0; current_length--){
                    // let's check if we can find square with decreasing length
                    int flag_smaller_square = 0;

                    // check bottom row
                    // j won't go out of bounds, because current_length is declared as number less then distance to bottom and 
                    // cut to the min between distance to right and amount of black tiles in column
                    for (int j = 0; j <= current_length; j++){
                        if (image->matrix[(pos_x + current_length) * image->width + pos_y + j] == 0){
                            flag_smaller_square = 1;
                            break;
                        }
                    }
                    if (flag_smaller_square){
                        continue; // decrease current_length and try again
                    }
                    // check right column
                    for (int i = 0; i <= current_length; i++){
                        if (image->matrix[(pos_x + i) * image->width + pos_y + current_length] == 0){
                            flag_smaller_square = 1;
                            break;
                        }
                    }
                    if (flag_smaller_square){
                        continue; // decrease current_length and try again
                    }

                    // if we are here, we found square
                    if (current_length > max_length){
                        max_length = current_length;
                        top_left_x = pos_x;
                        top_left_y = pos_y;
                    }

                }
            }
        }
    }
    if (max_length == -1){
        fprintf(stderr, "Not found\n");
    } else {
        printf("%d %d %d %d\n",top_left_x, top_left_y, top_left_x + max_length, top_left_y + max_length);
    }
    return;
}

int main(int argc, char * argv[]){
    FILE* file;
    int cheak;
    Image image = {0, 0, NULL};
    
    if(argc <= 1) { // argument count check
                 fprintf(stderr, "Command line has no additional arguments\n");
                 return 0;
         } else if(argc > 3){
                 fprintf(stderr, "Too many arguments\n");
                 return 0;
         }

    if(argc == 2 && !strcmp(argv[1], "--help")){help();return 0;} //argument --help
    if(argc == 2){fprintf(stderr, "Unkhnow arguments1\n");return 0;}

    if(argc == 3 ){

        file = fopen(argv[2], "r");
        if (file == NULL) {
        fprintf(stderr, "The file is not opened.Or not exsist\n");
        return 0;
        }
            
        if(!strcmp(argv[1],"test")){ //argument test
                test_soubor(file, cheak = 1, &image);
            }else if(!strcmp(argv[1],"hline")){ //argument hline
                test_soubor(file, cheak = 0, &image);
                hline_soubor(&image);
            }else if(!strcmp(argv[1],"vline")){ //argument vline
                test_soubor(file, cheak = 0, &image);
                vline_soubor(&image);
            }else if(!strcmp(argv[1],"square")){ //argument square
                test_soubor(file, cheak = 0, &image);
                square_soubor(&image);
            }else {
                fprintf(stderr, "Unkhnow arguments1\n");
                fclose(file);
                return 0;
            }
    }

    if(image.matrix != NULL){//here we clear memory in matrix
        free(image.matrix);
    }
    return 0;
}