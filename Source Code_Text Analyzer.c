#include <stdio.h>
#include <string.h>
#include <conio.h> //use to hold the screen as we printing the data of file
#include <stdbool.h> //for using true and false
#include <ctype.h> //for using function isspace()
#define MAX_BUFFER 1000
#include <stdlib.h>

void main()
{
    int i;
    FILE *file;
    char filename[100];
    file=fopen("code.txt","w"); //creating a new file and writing data in it
    if(file==NULL)
    printf("unable to open the file");
    printf("enter a string: ");
    gets(filename);
    fputs(filename,file);
    fclose(file);
    //getch();

//void main()
//{
    int ch;
    int no_of_lines=0;
    printf("functions to be carried out in file are:-\n");
    printf("1:read all content from file\n");
    printf("2:count characters and words\n");
    printf("3:count occurrence of given word\n");
    printf("4:convert data to uppercase\n");
    printf("5:convert data to lowercase\n");
    printf("6:remove punctuation from data\n");
    printf("7:count total lines in file\n");
    printf("8:read specific line from file\n");
    printf("9:copy data of fine to another file\n");
    printf("10:error handling\n");
    printf("11:sentiment analysis\n\n");

    printf("enter your choice: ");
    scanf("%d",&ch);
    printf("\n");

    switch(ch)
    {
        case 1:
        {
            read();
            break;
        }
        case 2:
        {
            count_characters_words();
            break;
        }
        case 3:
        {
            count_occurrence();
            break;
        }
        case 4 :
        {
            uppercase();
            break;
        }
        case 5:
        {   lowercase();
            break;
        }
        case 6:
        {
            removepunctuation();
            break;
        }
        case 7:
        {
            no_of_lines=count_lines();
            printf("No of Lines in File:%d",no_of_lines);
            break;
        }
        case 8:
        {
            read_specific_line();
            break;
        }
        case 9:
        {
            copy_data();
            break;
        }
        case 10:
        {
            f_error();
            break;
        }
        case 11:
        {
            analyze_sentiment();
            break;
        }
    }
return 0;
}


///reading from a file
void read()
{
    char filename;
    FILE *file;

    file=fopen("code.txt", "r"); //opening file in read mode
    if (file==NULL)
        {
            printf("unable to open the file");}
            while(1)
            {
                filename=fgetc(file);
                if(filename==EOF)
        //EOF (end of file) is a macro/a special symbol (ASCII value 26) denotes the termination of data in a file
                break;
                printf("%c",filename);
            }
    fclose(file);
    getch();
return 0;
}


///count words and characters in file
void count_characters_words()
{
    FILE *file=fopen("code.txt","r");

    if(file==NULL)
        printf("unable to open file");

    int c; //store character as we'll read one by one
    int count_words=0;
    int count_characters=0;
    bool whitespace=true;

    while(true)
    {
        c=fgetc(file);
        if(feof(file))
        break;
        else if(ferror(file))
        {
            printf("error reading the file");
        }
        if(!isspace(c) && c!='\n')
        {
            count_characters++;
        }


    if(whitespace && !isspace(c)) //isspace() return true if character is whitespace character
    {
        count_words++;
        whitespace=false;
    }
    else if(!whitespace && isspace(c))
       whitespace=true;
}
fclose(file);
printf("analysis completed.\n");
printf("the results  are:-\n");
printf("count of characters:%d\n",count_characters);
printf("count of words:%d\n",count_words);
}


///count occurrence of specific word
#define MAX_WORD_SIZE 100
int count_occurrence()
{
    char buffer[MAX_WORD_SIZE];
    int count = 0;
    FILE *file;
    char word[100];

    // Get the word from the user
    printf("Enter the word to count: ");
    scanf("%s", word);

    // Open the file for reading
    file = fopen("code.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return 1; // Return an error code
    }
    // Loop through the file until the end is reached
    while (fscanf(file, "%s", buffer) == 1) {
        // Compare the read word with the target word
        if (strcmp(buffer, word) == 0) {
            count++;
        }
    }

    // Display the result
    printf("The word '%s' appears %d times in the file.\n", word,count);

    // Close the file
    fclose(file);

    return 0;
}


///convert file data to uppercase
int uppercase()
{
    FILE *file;
    char fileName[100];
    char buffer[MAX_BUFFER];

    // Get the file name
    printf("Enter the name of the file: ");
    scanf("%s", fileName);

    // Open the file
    file = fopen(fileName, "r+");

    // Check if the file exists
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    // Read the content from the file into a buffer
    while (fgets(buffer, MAX_BUFFER, file) != NULL) {
        // Use strupr to convert the buffer to uppercase
        char *ptr = buffer;
        while (*ptr) {
            *ptr = (char)toupper(*ptr);
            ptr++;
        }

        // Move the file pointer back to the beginning of the current line
        fseek(file, -strlen(buffer), SEEK_CUR);

        // Write the modified buffer back to the file
        fputs(buffer, file);
    }

    // Close the file
    fclose(file);

    printf("File content converted to uppercase in-place.\n");

    // Display the changes made in the file
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error: Unable to open the file for reading.\n");
        return 1;
    }

    printf("\nContent of %s after conversion:\n", fileName);

    while (fgets(buffer, MAX_BUFFER, file) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}


///convert file data to lowercase
int lowercase()
{
    FILE *file;
    char fileName[100];
    char buffer[MAX_BUFFER];

    // Get the file name
    printf("Enter the name of the file: ");
    scanf("%s", fileName);

    // Open the file
    file = fopen(fileName, "r+");

    // Check if the file exists
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    // Read the content from the file into a buffer
    while (fgets(buffer, MAX_BUFFER, file) != NULL) {
        // Convert the buffer to lowercase
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = (char)tolower(buffer[i]);
        }

        // Move the file pointer back to the beginning of the current line
        fseek(file, -strlen(buffer), SEEK_CUR);

        // Write the modified buffer back to the file
        fputs(buffer, file);
    }

    // Close the file
    fclose(file);

    printf("File content converted to lowercase in-place.\n");

    // Display the changes made in the file
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error: Unable to open the file for reading.\n");
        return 1;
    }

    printf("\nContent of %s after conversion:\n", fileName);

    while (fgets(buffer, MAX_BUFFER, file) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}


///remove punctuations from file data
int removepunctuation()
{
    FILE *fp = fopen("code.txt", "r"); // open the input file
    if (fp == NULL) // check if the file exists
    {
        printf("File not found.\n");
        return 1;
    }

    char ch; // to store each character from the file
    char buffer[1000]; // to store the original text
    char result[1000]; // to store the text without punctuation
    int i = 0; // to keep track of the index in the buffer and result arrays

    while ((ch = fgetc(fp)) != EOF) // read each character until the end of file
    {
        buffer[i] = ch; // store the character in the buffer
        if (!ispunct(ch)) // check if the character is not a punctuation
        {
            result[i] = ch; // store the character in the result
        }
        else // if the character is a punctuation
        {
            result[i] = ' '; // replace it with a space in the result
        }
        i++; // increment the index
    }

    buffer[i] = '\0'; // add a null terminator to the buffer
    result[i] = '\0'; // add a null terminator to the result

    fclose(fp); // close the file

    printf("Original text:\n%s\n", buffer); // print the original text
    printf("Text without punctuation:\n%s\n", result); // print the text without punctuation

    return 0;
}


///count total lines in file
#define max_line 200
int count_lines()
{
    FILE *file;
    char filename[100];

    file=fopen("code.txt","r");
    if(file==NULL)
        printf("error opening file");

    int current_line=1;
    char c;
    do{
        c=fgetc(file); //read character by character
        if(c=='\n')    //increments when \n is found
        {
            current_line++;
        }

        }
    while(c!=EOF);
    fclose(file);
    return current_line;
}


///read a specific line from a file
#define max_line 200
int read_specific_line()
{
    FILE *file;
    char filename[100];
    char buffer[max_line];

    int read_line=0;

    printf("enter line no. to be read: ");
    scanf("%d",&read_line);

    file=fopen("code.txt","r");
    if(file==NULL)
        printf("error opening file");

    bool keep_reading=true; //keep a track of whether we should continue reading file or not
    int current_line=1;
    int lines_in_file=0;
    lines_in_file=count_lines();
    if (read_line>lines_in_file)
    {
        printf("entered line no. to be read is greater than no. of lines in file ");
    }
    else
    {
    do{
        fgets(buffer,max_line,file);

        if(current_line==read_line) //if line is found
        {
            keep_reading=false;
            printf("required line: %s",buffer);
        }
    current_line++;}
    while(keep_reading);
    }
    fclose(file);
}


///copy data of file to another file
int copy_data()
{
    FILE *file,*copy;

    file=fopen("code.txt","r");
    copy=fopen("copy.txt","w");

    if(file==NULL||copy==NULL)
       {
           printf("error opening file");
           return 1;
       }
    char c; //store each character of file
    while((c=fgetc(file))!=EOF)
    {
        fputc(c,copy);
    }
fclose(file);
fclose(copy);
return 0;
}


///error handling
void f_error()
{
    FILE *fp;
    int c;

    fp = fopen("code.txt","r");
    if(fp == NULL)
        {
            printf("Error in opening file");
            return(-1);
        }
        printf("data of file: ");
        while(1)
            {
            c = fgetc(fp);
        if( feof(fp) )
            { break ;}
        printf("%c", c);
        }
    printf("\n");
    printf("no error found");
    fclose(fp);
    return(0);
}


///sentiment anaysis
#define MAX_LINE_SIZE 100

// Function to perform basic sentiment analysis
int analyze_sentiment() {
    // Simple positive and negative word lists
    const char *positiveWords[] = {"good", "happy", "excellent", "positive"};
    const char *negativeWords[] = {"bad", "sad", "poor", "negative"};

    FILE *file;
    char token;
    char line[MAX_LINE_SIZE];

    // Open the file for reading
    file = fopen("code.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line
        char *token = strtok(line, " \t\n");

        // Analyze the sentiment of each token and display the result
        while (token != NULL) {
            int sentiment = analyze_sentiment(token);
            printf("Token: %s, Sentiment: %d\n", token, sentiment);
            token = strtok(NULL, " \t\n");
        }
    }

    // Check if the token is in the positive or negative word lists
    for (int i = 0; i < sizeof(positiveWords) / sizeof(positiveWords[0]); i++) {
        if (strstr(token, positiveWords[i]) != NULL) {
            return 1; // Positive sentiment
        }
    }

    for (int i = 0; i < sizeof(negativeWords) / sizeof(negativeWords[0]); i++) {
        if (strstr(token, negativeWords[i]) != NULL) {
            return -1; // Negative sentiment
        }
    }

    return 0; // Neutral sentiment

    // Close the file
    fclose(file);

    return 0;}

