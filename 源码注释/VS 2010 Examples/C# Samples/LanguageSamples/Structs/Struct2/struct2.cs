﻿// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// struct2.cs
using System;

class TheClass
{
    public int x;
}

struct TheStruct
{
    public int x;
}

class TestClass
{
    public static void structtaker(TheStruct s)
    {
        s.x = 5;
    }
    public static void classtaker(TheClass c)
    {
        c.x = 5;
    }
    public static void Main()
    {
        TheStruct a = new TheStruct();
        TheClass b = new TheClass();
        a.x = 1;
        b.x = 1;
        structtaker(a);
        classtaker(b);
        Console.WriteLine("a.x = {0}", a.x);
        Console.WriteLine("b.x = {0}", b.x);
    }
}

