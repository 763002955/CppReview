# C++关键字——const与static

## const

**常类型**：指使用const说明的类型，无法被更新修改。

由于在定义以后就不能被修改，**所以定义时必须初始化**。const可以修饰变量、指针、引用、函数...

那么类中的成员变量如何初始化呢？只能通过**初始化列表**

```
在类A中，在构造函数中直接初始化常类型是错误的，不对常类型进行初始化也是错误的。所以需要用到初始化列表。
class A
{
    private:
        const int a;
        
    public:
        A()//error
        {
            a = 10;
        }
        A():a(10){};//right
        //OR
        A(int x):a(x){};//correct
}
```

**const对象默认是文件的局部变量**

```
//file1.cpp
int x;
//file2.cpp
extern int x;
++x;

//file1.cpp
extern const int x = 1;
//file2.cpp
extern const int x;//use x from file1.h
```

除非特别说明，在全局作用域声明的const变量是该文件的局部变量。此变量只存在于那个文件中，不能被其他文件访问。通过指定const变量为extern，就可以在整个程序中访问const对象。而非const变量默认为extern。

#### 常对象：

```
const A a;//常对象，只能调用常成员函数
A b;//普通对象，可以调用类的所有成员函数，更新常成员变量
```

例如：

```
class A
{
private:
    const int a;                // 常对象成员，只能在初始化列表赋值
	int x;
public:
    // 构造函数
    A() : a(0) { };
    A(int x) : a(x) { };        // 初始化列表
	int change(int y){x=y;};
    // const可用于对重载函数的区分
    int getValue(){cout<<a<<"普通成员函数"<<endl;};// 普通成员函数
    int getValue() const{cout<<a<<"常成员函数"<<endl;};// 常成员函数，不得修改类中的任何数据成员的值
};

int main()
{
	A b;// 普通对象，可以调用全部成员函数、更新常成员变量
    const A a(4);// 常对象，只能调用常成员函数
    a.change(1);//error
    b.change(1);//correct
    a.getValue();//输出：4常成员函数
    b.getValue();//输出：0普通成员函数
	return 0; 
} 
```

#### 指针与const

const修饰指针有三种情况："**左定值，右定向，const修饰不变量**"

|        const修饰        |        不可变量         |
| :---------------------: | :---------------------: |
|     指针指向的内容      |          内容           |
|          指针           |          指针           |
| 指针 and 指针指向的内容 | 指针 and 指针指向的内容 |

举例说明：

##### **指向常量的指针**：

const位于*号左边， 指针指向的内容为常量

```
const int x = 1;
const int* p = &x;
int const *p = &x;//两者一样
*p=2;//wrong
```

p本身并不是const，所以定义的时候不需要对p进行初始化，如果需要的话，允许给cptr重新赋值，让其指向另一个const对象。但不能通过cptr修改其所指对象的值。

```
const int x = 1;
const int y = 2;
const int* p = &x;
p = &y;//correct *p=2
```

而且我们将一个const对象的地址赋给一个普通的非const指针也会导致编译错误。

最令我头昏的是，**可以将非const对象的地址赋给const对象的指针！！！！！**

```
int x = 1;
const int* p = &x;
(*p)++;//wrong
int *p1 = &x;
x++;//correct
(*p1)++;///correct
cout<<(*P);//此时*p=3
```

**const指针指向的值是可以修改的，我们只是无法通过p指针来修改x的值**

##### 常指针

const位于*号右边，则const修饰的是指针p，即p指向的内存地址/指针本身不能改变，但指针指向的内容不是常量

```
int x = 1;
int* const p = &x;
*p = 2;//correct
int y = 1;
p = &y;//wrong 即使x = y
p++;//wrong
(*p)++;//correct
```

##### 指向常量的常指针

上述两种情况的综合

```
const int x = 1;
const int* const p = &x;//p与p指向的内容都不可改变
```

#### const引用





#### 函数与const

##### 类中的const成员函数

类中，不会修改数据成员的函数都应该被声明为const类型。使用const的成员函数称为，常成员函数。**只有常成员函数才能操作常量/常对象，没有使用const关键字的成员函数不能操作常对象**。

```
class A
{
private:
	int x;
public:
    void print();
	int func1() const;
};
int A::func1() const
{
	++x;//wrong
	print();//wrong 调用非const成员函数
}
```

const还可以实现**函数重载**，例如常对象那部分中写的函数，部分如下：

```
int getValue(){cout<<a<<"普通成员函数"<<endl;};             // 普通成员函数
    int getValue() const{cout<<a<<"常成员函数"<<endl;};       // 常成员函数，不得修改类中的任何数据成员的值

```

const对象默认调用的是const成员函数。

##### const修饰函数返回值

很少用到，它的含义和const修饰变量、指针基本一样。

```
const int func1();//无意义 

//调用的时候用 const int* p = func2();
//把func2()看成一个变量即可,指针指向的内容不可变
const int* func2();

//调用时 int* const p = func3();
int* const func3();
```

。。。。。。。

。。。。。。。



##### const修饰函数参数

```
void f(const int x)
//一般这种情况不需要 const 修饰，因为函数会自动产生临时变量复制实参值。

void f(const char* x)
//x指针指向的内容为常量

void f(char* const x)
//防止指针被意外篡改

void f(const TYPE& x)
//引用的参数在函数内为常量，不可变
//自定义类型的参数传递，需要临时对象复制参数，对于临时对象的构造，需要调用构造函数，比较浪费时间，因此我们采取 const 外加引用传递的方法。
```



## static

#### 面向过程设计中的static（c语言中static）

##### 静态局部变量

在函数体内部修饰局部变量

```
void f()
{
	static int cnt = 1;//[1]
	cout<<cnt<<endl;
	cnt++;
}
void main()
{
	f();
	f();
	f();
}
```

通常在函数体内定义了一个变量，每当程序运行到该语句时都会给这个局部变量分配栈内存，程序退出函数体后，系统会回收栈内存，局部变量失效。上述代码可以做到两次调用f();时，对cnt的值进行保存。（**通常也可以用全局变量实现，但这样全局变量本身是不属于该函数的，不仅仅只受该函数的控制**）

> *补充：*
>
> *对于一个完整的程序，在内存中的分布情况如下：*　 
>
> 1. *栈区： 由编译器自动分配释放，像局部变量，函数参数，都是在栈区。会随着作用于退出而释放空间。*
> 2. *堆区：程序员分配并释放的区域，像malloc(c),new(c++)* 
> 3. *全局数据区(静态区)：全局变量和静态便令的存储是放在一块的，初始化的全局变量和静态变量在一块区域，未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。程序结束释放。*
> 4. *代码区*

静态局部变量就是在全局数据区保存。那么它是什么时候初始化的呢？

**在第一次调用f()，进入[1]时初始化，且只初始化一次，第二次调用f()时会直接跳过[1]。**

总结**静态局部变量的特点**如下：

1. 在全局数据区分配内存(局部变量在栈区分配内存)
2. 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化(局部变量每次函数调用都会被初始化);
3. 静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为0(局部变量不会被初始化);它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，也就是不能在函数体外面使用它(局部变量在栈区，在函数结束后立即释放内存);
4. 它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，也就是不能在函数体外面使用它(局部变量在栈区，在函数结束后立即释放内存);

##### 静态全局变量

定义在函数体外，修饰全局变量，该变量只在本文件可见

```
static int i = 1;//[1]
//int i;//[2]
int f()
{
	i++;
	return i;
}
```

那么上述代码中[1]和[2]有什么区别呢？

首先在本文件中无论怎么调用f()，他们都是没区别的。

但是若此时有两个文件file1.c file2.c

```
//file1.c
 
//static int n = 15;  //[1]
int n = 15;  //[2]
 
//file2.c
#include <stdio.h>
 
extern int n;
 
void f()
{
    n++;
    printf("after: %d\n",n);
}
 
 
void main()
{
    printf("before: %d\n",n);
    f();
}
```

在使用[2]，也就是非静态全局变量时，输出为

before：15 after：16

也就是说file2.c通过extern 使用了file1.c中的全局变量n

而在使用[1]时，file2.c文件编译时会出错，**由于static进行了文件隔离**，所以在

file2中无法访问到file1中定义的静态全局变量（当然 #include "a.c"可以)，同时，在file2中可以定义名为n的变量，与file1不冲突

总结**静态全局变量特点**如下：

1. **静态全局变量不能被其它文件所用**(全局变量可以);
2. 其它文件中可以定义相同名字的变量，不会发生冲突(自然了，因为static隔离了文件，其它文件使用相同的名字的变量，也跟它没关系了);

##### 静态函数

静态函数与静态全局变量类似

#### 面向对象的static关键字

##### 静态数据成员

在类内数据成员的声明前加上static，这种数据成员的生存期大于 class 的对象（实例）。静态数据成员是每个 class 有一份，普通数据成员是每个 instance(实例) 有一份，因此静态数据成员也叫做类变量，而普通数据成员也叫做实例变量。

```
#include<iostream>
 
 
using namespace std;
 
 
class Rectangle
{
private:
    int m_w,m_h;
    static int s_sum;//声明静态数据成员
    
public:
    Rectangle(int w,int h)
    {
        this->m_w = w;
        this->m_h = h;
        s_sum += (this->m_w * this->m_h);
    }
    void GetSum()
    {
        cout<<"sum = "<<s_sum<<endl;
    }
};
int Rectangle::s_sum = 0;  //初始化静态数据成员
int main()
{
    cout<<"sizeof(Rectangle)="<<sizeof(Rectangle)<<endl;
    Rectangle *rect1 = new Rectangle(3,4);
    rect1->GetSum();
    cout<<"sizeof(rect1)="<<sizeof(*rect1)<<endl;
    Rectangle rect2(2,3);
    rect2.GetSum();
    cout<<"sizeof(rect2)="<<sizeof(rect2)<<endl;
    return 0;
}
```

结果如下：

```
sizeof(rectangle)=8
sum=12
sizeof(Rect1)=8
sum=18
sizeof(Rect2)=8
```

从上面这段代码可以看出来两点：sizeof(Rectangle)=8bytes=sizeof(m_w)+sizeof(m_h)。也就是说 static 并不占用Rectangle的内存空间。static在全局数据区(静态区)分配内存；sum第一次为12，第二次为18，可知static只会初始化一次，与实例无关；

**总结如下：**

- 对于非静态数据成员，每个类对象(实例)都有自己的拷贝。而静态数据成员被当作是类的成员，由该类型的所有对象共享访问,对该类的多个对象来说，静态数据成员只分配一次内存。

- 静态数据成员存储在全局数据区。**静态数据成员定义时要分配空间，所以不能在类声明中定义。**所以使用int Rectangle::s_sum = 0; 在类外定义。（**类声明只声明一个类的尺寸和规则，并不进行实际的内存分配，所以在类声明中写成定义是错误的**）

  你每new一个Rectangle，并不会为static int s_sum的构建一份内存拷贝，它是不管你new了多少Rectangle的实例，因为它只与类Rectangle挂钩，而跟你每一个Rectangle的对象没关系。

**何时使用静态数据成员呢？**

静态数据成员主要用于各个对象有某种相同属性时，比如存款利息，每个实例的利息一样，应该将利息设为存款类的静态数据成员。一来可以**节省存储空间**，二来，当利息需要改变时，只需要改变一次，则所有对象的利息都会改变。

**使用静态数据成员相比于全局变量的优势？**

- 静态数据成员不会与其他全局名字冲突
- 可以实现信息隐藏，静态数据成员可以是private，但全局变量不可



##### 静态成员函数

同样是上述rectangle类的例子，若将getsum函数变为静态成员函数

```
class Rectangle
{
private:
    int m_w,m_h;
    static int s_sum;
    
public:
    Rectangle(int w,int h)
    {
        this->m_w = w;
        this->m_h = h;
        s_sum += (this->m_w * this->m_h);
    } 
    static void GetSum()  //这里加上static
    {
        cout<<"sum = "<<s_sum<<endl;
    } 
};
int Rectangle::s_sum = 0;  //初始化 不带static
int main()
{
    cout<<"sizeof(Rectangle)="<<sizeof(Rectangle)<<endl;
    Rectangle *rect1 = new Rectangle(3,4);
    rect1->GetSum();
    cout<<"sizeof(rect1)="<<sizeof(*rect1)<<endl;
    Rectangle rect2(2,3);
    rect2.GetSum();  //可以用对象名.函数名访问
    cout<<"sizeof(rect2)="<<sizeof(rect2)<<endl;
    Rectangle::GetSum();  //也可以可以用类名::函数名访问
    return 0;
}
```

可以看出，Getsum函数加上static后，作用于整个类，而不是单独的对象。所以可以用**对象名.函数名**访问，也可以用过**类名::函数名**访问。

同时也可以写成

```
class Rectangle
{
private:
    int m_w,m_h;
    static int s_sum;
    
public:
    Rectangle(int w,int h)
    {
        this->m_w = w;
        this->m_h = h;
        s_sum += (this->m_w * this->m_h);//非静态成员函数可以访问静态成员
    } 
    static void GetSum();  //声明
};
//出现在类外的函数定义不能指定关键字static
void Rectangle：：GetSum()//静态成员函数的实现 不带static
{
	......
	//cout<<m_W<<endl;//wrong 静态成员函数不能访问非静态成员
}

```

**静态函数的特点：**

1. 静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数;
2. 非静态成员函数可以任意地访问静态成员函数和静态数据成员;
3. 静态成员函数不能访问非静态成员函数和非静态数据成员;
4. 调用静态成员函数，可以用成员访问操作符(.)和(->)为一个类的对象或指向类对象的指针调用静态成员函数,也可以用类名::函数名调用(因为他本来就是属于类的，用类名调用很正常)

前三点其实是一点：静态成员函数不能访问非静态(包括成员函数和数据成员)，但是非静态可以访问静态。

**如何理解这3点？**因为静态是属于类的，它是不知道你创建了10个还是100个对象，所以它对你对象的函数或者数据是一无所知的，所以它没办法调用，而反过来，你创建的对象是对类一清二楚的(不然你怎么从它那里实例化呢)，所以你是可以调用类函数和类成员的，就像不管GetSum是不是static，都可以调用static的s_sum一样。

**Q： 为什么引入static？**

希望让函数内部定义的变量保存早下一次调用，当然这也可以定义全局变量解决，但全局变量破坏了此变量的访问范围，这个变量不仅仅只受该函数控制。

**Q：什么时候用static？**

需要一个数据对象为整个类而不是单个对象服务、而且力求不破坏封装性，即要求此成员隐藏在类的内部，对外不可见

**Q：static的优势**

节省内存，提高时间效率（对于不同对象，static只需要更新一次

**注意事项**：

1. 类的静态成员函数是属于整个类而非类的对象，所以没this指针，这就导致了它只能访问类的静态成员
2. 不能将静态成员函数定义为虚函数
3. ![image-20200224200107393](C:\Users\win10\AppData\Roaming\Typora\typora-user-images\image-20200224200107393.png)



## const与static的区别

1. const定义的常量在超出其作用域之后其空间会被释放，而static定义的静态常量在函数执行后不会释放其存储空间。
2. static表示的是静态的。类的静态成员函数、静态成员变量是和类相关的，而不是和类的具体对象相关的。即使没有具体对象，也能调用类的静态成员函数和成员变量。一般类的静态函数几乎就是一个全局函数，只不过它的作用域限于包含它的文件中。
3. 在C++中，static静态成员变量不能在类的内部初始化。在类的内部只是声明，定义必须在类定义体的外部，通常在类的实现文件中初始化，如：double Account::Rate=2.25; static关键字只能用于类定义体内部的声明中，定义时不能标示为static。
4. 在C++中，const成员变量也不能在类定义处初始化，只能通过构造函数初始化列表进行，并且必须有构造函数。
5. **const数据成员,只在某个对象生存期内是常量，而对于整个类而言却是可变的。**因为类可以创建多个对象，不同的对象其const数据成员的值可以不同。所以不能在类的声明中初始化const数据成员，**因为类的对象没被创建时，编译器不知道const数据成员的值是什么。**
6. **const数据成员的初始化只能在类的构造函数的初始化列表中进行。**要想建立在整个类中都恒定的常量，应该用类中的**枚举常量**来实现，或者**static const**。
7. const成员函数主要目的是防止成员函数修改对象的内容。即const成员函数不能修改成员变量的值，但可以访问成员变量。当方法成员函数时，该函数只能是const成员函数。///  static成员函数主要目的是作为类作用域的全局函数。不能访问类的非静态数据成员。类的静态成员函数没有this指针，这导致：1、不能直接存取类的非静态成员变量，调用非静态成员函数2、不能被声明为virtual 



