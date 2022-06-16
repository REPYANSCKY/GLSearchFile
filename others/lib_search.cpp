#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <filesystem>

#define MAX_THREADS 8

std::mutex mutex;
std::atomic<bool> fileIsFound = false;  //flag true if the file is find
std::filesystem::recursive_directory_iterator dir("/"), end; //iterator of the start dir & empty iterator (end)

void filesearch(const std::string& filename)
{
    std::filesystem::recursive_directory_iterator currentDir;  //iterator 

    while(dir != end)
    {
        mutex.lock();
        currentDir = dir;
      
        if (currentDir != end)
        {
                if (currentDir->path().stem() == filename && !fileIsFound)  //checks if current file is searched
                {
                    fileIsFound = true;
                    std::cout << "\nFile is found!\nPath > " << currentDir->path().string() << std::endl;   //Returns path to the file
                }
        }

        try
        {
            if (dir != end)
                ++dir;  //go to next file/directory
        }
        catch (...)
        {
            dir = currentDir;   //return previous dir
            dir.disable_recursion_pending();    //disables recursion to the currently referred subdirectory
        }
        mutex.unlock();

        if (fileIsFound)
        {
            break;
        } 
    }    
}

void multisearch(const std::string& filename)
{
    std::thread thArray[MAX_THREADS];   //array of threads

    for (auto i = 0; i < MAX_THREADS; ++i)  //initializ threads with the search function 
    {
        thArray[i] = std::thread(filesearch, filename);
    }

    for (auto i = 0; i < MAX_THREADS; ++i)  //wait while threads finish work
    {
        thArray[i].join();
    }

    if (!fileIsFound)
        std::cout << "\nFile is not Found!" << std::endl;
}
