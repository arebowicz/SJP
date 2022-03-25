# Welcome to my first project repository called SJP
_SJP -- in Polish -- acronym from Polish Language Dictionary_

## Short description

My program processes list of all Polish words included in one .TXT file (available under a free license) from the webpage: https://sjp.pl/slownik/growy/ All the loaded data is stored in computer's memory as a tree structure. User can save the whole tree in one .TXT file as a series of ones and zeros. User can also check if some word is stored in dictionary. In future versions, I plan to add some new features. Stay tuned!

## More info

- The dictionary was downloaded from sjp.pl on 03.20.2022.
- Due to GitHub upload limits, I decided to reduce its content to 500.000 words (but you can easily process full dictionary on your own).
- File "dict-03-20-2022" structure: word -> new line character -> word -> ... -> new line character -> EOF character. 
- File "01.txt" structure: long series of 0/1 (in one line!) and then EOF character. 
- A word is a sequence of letters: a/ą/b/c/... More: https://en.wikipedia.org/wiki/Polish_alphabet 
- There are 35 letters used in Polish dictionary. 
- I assume that the data in .TXT files are stored acording to these strictly defined rules above.
- Valgrind reports no memory leaks (tested several times on different data sets).
- Size of "dict-03-20-2022.txt": 6.1 MB
- Size of "01.txt": 29.6 MB
- As mentioned, user can check if some word is stored in dictionary.
- Also, I assume that user operates that small program properly -- focusing on validating if entered commands are correct wasn't my purpose. I thought that that validating is just useless waste of my time. For example: empty commands are not supported.

## To compile

Just run command:
```gcc -Wall SJP.c menu.c treeStructure.c readAndWrite.c -o SJP```

**Suggestions and comments are welcome :)**
