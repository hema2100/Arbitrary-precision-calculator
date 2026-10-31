# Arbitrary Precision Calculator (APC)

## Overview
The Arbitrary Precision Calculator (APC) is a command-line application developed in C to perform arithmetic operations on integers of very large size that exceed the range of built-in data types such as `int` and `long long`.

This project implements arithmetic operations using a **Doubly Linked List**, where each node stores a single decimal digit.

## Features
- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`x`)
- Division (`/`)
- Supports large integer operands
- Handles leading zeros
- Input validation and error handling
- Division by zero detection
- Dynamic memory allocation using linked lists

## Technologies Used
- Programming Language: C
- Data Structure: Doubly Linked List
- Compiler: GCC
- Build Tool: GNU Make

## Project Structure
APC/
│
├── main.c
├── apc.h
├── apc.c
├── addition.c
├── subtraction.c
├── multiplication.c
├── division.c
├── Makefile
└── README.md

## Compilation

Compile the project using GNU Make:

bash
make

This generates the executable:


apc.exe

Alternatively, compile manually using GCC:

bash
gcc -Wall -Wextra -std=c11 main.c apc.c addition.c subtraction.c multiplication.c division.c -o apc.exe


## Usage

bash
./apc.exe operand1 operator operand2


### Examples

bash
./apc.exe 123456789123456789 + 987654321987654321


Output:
1111111111111111110

bash
./apc.exe 987654321 - 123456789


Output:

864197532


```bash
./apc.exe 100000000
