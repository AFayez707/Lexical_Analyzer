//
// Created by MacPro on 11/14/17.
//

#include "regex.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

void regex::GetRegExp()
{
    //cout << "Please input Regular Expression:" << endl;
    //cin >> exp;
    // for (int i=0; exp[i]!='\0'; i++)
    // {
    //	if (exp[i] == '$')
    //	{
    //		cout << "\nsymbol '$'has been forbidden£¡" << endl;
    //		getch();
    //		exit(1);
    //	}
    //}
    // string filename;
    cout << "PLEASE INPUT THE TEST FILE NAME:" << endl;
    cin >> filename;

    ifstream fin(filename.c_str());

    const int LINE_LENGTH = 1000;

    fin.getline(exp,LINE_LENGTH);

    // cout << "Regular Expression is :" << exp << endl;
}

void regex::InsertCatNode()
{
    int i = 0, j, len = strlen(exp);
    while (exp[i+1] != '\0')
    {
        if (((exp[i] != '(' && exp[i] != '.' && exp[i] != '|')
             || exp[i] == ')'
             || exp[i] == '*'
             || exp[i] == '+')
            && (exp[i+1] != ')' && exp[i+1] != '.' && exp[i+1] != '|' && exp[i+1] != '*' && exp[i+1] != '+'))
        {
            for (j=len; j>i+1; j--)
            {
                exp[j] = exp[j-1];
            }
            exp[i+1] = '.';
            len++;
            exp[len] = '\0';
            i++;
        }
        i++;
    }
    //cout << "\nadd the and operation to RE:\n"
    //	 << exp << "\n";
}

// define the precedence of operations
int regex::Precedence(char symbol)
{
    int priority;
    switch (symbol)
    {
        case '|': priority = 1; break;
        case '.': priority = 2; break;
        case '*': priority = 3; break;
        case '+': priority = 4; break;
        default:  priority = 0; break;
    }
    return priority;
}

// transfer the RE to postfix
void regex::RegExpToPost()
{
    int i = 0, j = 0;
    char ch, cl;
    strcpy(post, "\0");
    LinkedStack<char> *ls = new LinkedStack<char>();
    ls->makeEmpty();
    ls->Push('#');
    ch = exp[i];
    while (ch != '\0')
    {
        if (ch == '(')
        {
            ls->Push(ch);
            ch = exp[++i];
        }
        else if (ch == ')')
        {
            while (ls->getTop() != '(')
            {
                post[j++] = ls->Pop();
            }
            ls->Pop();
            ch = exp[++i];
        }
        else if ((ch == '|') || (ch == '*') || (ch == '.') || (ch == '+'))
        {
            cl = ls->getTop();
            while (Precedence(cl) >= Precedence(ch))
            {
                post[j++] = cl;
                ls->Pop();
                cl = ls->getTop();
            }
            ls->Push(ch);
            ch = exp[++i];
        }
        else
        {
            post[j++] = ch;
            ch = exp[++i];
        }
    }
    ch = ls->Pop();
    while ((ch == '|') || (ch == '*') || (ch == '.') || (ch == '+'))
    {
        post[j++] = ch;
        ch = ls->Pop();
    }
    post[j] = '\0';
    ls->makeEmpty();
}