=====================
# Burkard-Keller-Tree
=====================

* Compiled with a g++ Compiler in Ubuntu (Linux)

________________________

## Dependencies

This project requires _graphvis_ for displaying _dot files_. If it is not install use the following command.

```
sudo apt-get install graphviz
```

## Installation
------------

The bk tree project can be build using **make** in the command line. This compiles the programm and downloads all files necessary for the usage of the interactive mode.

Using **make clean** all compiled files are deleted.

## Usage
------------------

The project includes an interactive mode that uses the DeReWo word list (German Words) as the word base . This mode can be started with the following command:

```
make interactive
```

It is possible to read an own word list. This can be done by the following command:

```
bin/show-near-words <filename> <dotfilename>
```
The file to be read must contain a word in each line over which the tree is created.
The name of the dot file being created must be given as the second argument.

The mode is active until a space is given as input.


## Links
--------

Explanations of the bk tree:

* http://blog.notdot.net/2007/4/Damn-Cool-Algorithms-Part-1-BK-Trees
* https://www.joocom.de/blog/posts/coole-datenstrukturen-und-algorithmen-bk-baume/
* https://www.geeksforgeeks.org/bk-tree-introduction-implementation/

Explanations for the levenshtein distance:

* https://www.python-course.eu/levenshtein_distance.php
