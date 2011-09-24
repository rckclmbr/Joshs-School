#!/bin/bash

# Josh Braegger
# Lab 2
# CS3230

help() {
    echo Welcome to smallcalc
    echo
    echo These are your options:
    echo enter an expression
    echo q, quit or exit to terminate
    echo variable=expression to set a variable to an expression
}

help

while [ 1 ]
do
    printf 'Enter an expression: '; read input

    case $input in
    "q"|"quit"|"exit") echo "Exiting..."; break;;
    "help")            help;              continue;;
    esac

    echo Expr: $input Answer: $((input))
done

