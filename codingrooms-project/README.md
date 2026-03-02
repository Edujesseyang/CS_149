# Assignment 2
-- by Jesse Yang


### Usage:
- Compile:
    - Use  `gcc shell.c -o shell` to build the shell executable file
    - Use `gcc countnames.c -o countnames` to build the countnames file
- Run shell:
    - Use `./shell` to run shell
    - Use `./countnames filename.txt filename1.txt ...` to count the names in those files.

### Test:
- Test case 1:
    countname for single file
    command: `./countnames test/names.txt`
    It will test the building, basic counting, ouput, file creation, and warnings. 
    Result: new file `636.out` and `636.err` were created, each contains the correct output

- test case 2:
    countnames for multiple files
    command: `./countnames test/names.txt test/names1.txt test/names2.txt`
    It will test the multiple filenames as parameters.
    Result: 6 new files have been created, each of them contains the corretct output.

- Test case 3:
    countnames with all text files
    command: `./countnames ......` all files names
    Result: each new file contains the correct output.

### Lessons Learned:
I have learned the basic idea of how to coding a shell like program. how to use common system call functions such as fork(), wait(), exec(), fprintf(), etc. And also practiced my coding skills, such as syntax, algorithm, and knowledge in C language.

### Reference:
- Abhinav Kulshreshtha. (2012, February 15). fork() in C program. Stack Overflow. https://stackoverflow.com/questions/9299673/fork-in-c-programC 
- Tutorial. (n.d.). Www.w3schools.com. https://www.w3schools.com/c/index.php
- in. (2011, June 2). working of fork in c language. Stack Overflow. https://stackoverflow.com/questions/6210638/working-of-fork-in-c-language
- CodeVault. (2020, April 25). The fork() function in C. YouTube. https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

### Acknowlegements:
- Debug tool: ChatGTP, Germini
