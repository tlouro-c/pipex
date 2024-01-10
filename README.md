# Pipex - 42 School Project

## Table of Contents
- [Description](#description)
- [Usage](#usage)
- [Installation](#installation)
- [Example](#example)
- [Bonus Features](#bonus-features)
- [Author](#author)

## Description
Pipex is a project at 42 School that involves creating a simplified version of the shell command 'pipe' by using processes and pipes in C programming. The goal is to execute two commands, and the output of the first command should serve as the input for the second command.

## Usage
```bash
./pipex file1 cmd1 cmd2 file2
```
_file1:_ Input file, whose content will be used as the input for the first command.

_cmd1:_ The first shell command.

_cmd2:_ The second shell command.

_file2:_ Output file, where the final result will be stored.

## Bonus Features

#### Multiple Pipes
You can chain multiple commands using pipes:

```bash
./pipex file1 cmd1 | cmd2 | cmd3 ... | cmdN file2
```
#### Here Documents
You can use here documents to provide input to the first command:
```bash
./pipex here_doc DELIMITER cmd1 cmd2 file2
```

## Installation

Clone the repository:
```bash
git clone https://github.com/your-username/pipex.git
```
Compile the Pipex program:
```bash
cd pipex
make
```
## Example

```bash
./pipex infile "ls -l" "grep .c" outfile
```
This example will list all files in the current directory, filter the output to display only the lines containing ".c", and the final result will be stored in outfile.

## Author

tlouro-c

Contact: tomascorreia.lc@gmail.com
