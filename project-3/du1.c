#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define success 0
#define failure 1

#define ERROR_MESSAGE_MAX_SIZE  256

int isDirectory(const char* directory);
int printDirectoryStats(const char* directory);
int printFileInfo(const char* file);
void printDirectoryError(const char* directory);

char* globalErrorMessage = NULL;

int main(int argc, char* argv[]) {

  const char* directory = argc > 1 ? argv[1] : ".";
  
  if (argc == 1){
    if (printDirectoryStats(directory) != success) {
      printDirectoryError(directory);
      return failure;
    }
  }
  
  else{ 
    if (isDirectory(directory) == success) { 
      chdir(directory); 
      if (printDirectoryStats(directory) != success) {
        printDirectoryError(directory);
        return failure;
      }
    }
    else
      if (printFileInfo(directory) != success){
        printf("Error, file stats could not be printed");
        return failure;
        }
  }
 
  return success;
}

void printDirectoryError(const char* directory) { 
  char buffer[ERROR_MESSAGE_MAX_SIZE];
  snprintf(buffer, sizeof(buffer)-1, "Directory: '%s' has error %s\n", directory, globalErrorMessage);
  perror(buffer);
}

int printDirectoryStats(const char* directory) 
{
  DIR* current = opendir(directory);
  if (current == NULL) {
    globalErrorMessage = "Unable to open the selected directory";
    return failure;
  }
  
  struct dirent* directoryEntry;
  while ((directoryEntry = readdir(current)) != NULL) {
    if(directoryEntry->d_type & DT_DIR){
      if (strcmp (directoryEntry->d_name, "..") != 0 && 
          strcmp (directoryEntry->d_name, ".") != 0){
           printDirectoryStats(directoryEntry->d_name); 
	   }
    }
 
    struct stat entryDetails;
    if (stat(directoryEntry->d_name, &entryDetails) != success) {
      globalErrorMessage = "Failed to obtain stats information";
      return failure;
    }

    printf("Directory: %s - Entry: %15s - %10lld b \n", directory, directoryEntry->d_name, (long long)entryDetails.st_size);
  }

  return success;
}

int isDirectory(const char* directory)
{
  DIR* current = opendir(directory); 
  if (current == NULL) {
    return failure;
  }
  return success;
}

int printFileInfo (const char* file)
{
  struct stat entryDetails;
  if (stat(file, &entryDetails) != success) {
  globalErrorMessage = "Failed to obtain stats information";
  return failure;
  }
  printf("Entry: %s - %lld b \n", file, (long long)entryDetails.st_size);
  return success;
}
