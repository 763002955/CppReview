# C++关键字

### union

共同体/联合体，**union变量所占用的内存长度等于最长的成员的内存长度。**

由于union里面的东西共享内存，所以**不能定义静态、引用类型的变量**。由于在**union里也不允许存放带有构造函数、析构函数和复制构造函数等的类的对象，但是可以存放对应的类对象指针**。编译器无法保证类的构造函数和析构函数得到正确的调用，由此，就可能出现**内存泄漏**。所以，在C++中使用union时，尽量保持C语言中使用union的风格，尽量不要让union带有对象。

##### union与struct区别？

- 结构体：**每个成员都拥有自己的内存**，互不干涉，同时**遵循内存对齐原则**。**一个struct变量的总大小等于所有成员的大小之和**。
- 联合体：**各成员共用一块内存空间，并且同时只有一个成员可以得到这块内存的使用权**(对该内存的读写)，各变量共用一个内存首地址。

##### union的用法

union的一个用法就是可以用来测试CPU是大端模式还是小端模式：

```
#include <iostream>
using namespace std;

void checkCPU()
{
    union MyUnion{
        int a;
        char c;
    }test;
    test.a = 1;
    if (test.c == 1)
        cout << "little endian" <<endl;
    else cout << "big endian" <<endl;
}

int main()
{
    checkCPU();
    return 0;
}
```

union的赋值机制：

```
#include <stdio.h>
union u{
	int a;	
	short b;
};
int main()
{
	union u t;
	t.a=100000;
	t.b=10;
	printf("%d %hd", t.a, t.b); // 输出结果为： 65546 10。
	return 0;
}
```

给联合体中的成员赋值时，**只会对这个成员所属的数据类型所占内存空间的大小覆盖成后来的这个值**，而不会影响其他位置的值。

  成员a为int类型，b为short类型，第一次给a赋值100000，二进制为`0000 0000 0000 0001 1000 0110 1010 0000`，第二次给b赋值，由于short只占2个字节，所以只会覆盖16位二进制，`0000 0000 0000 1010`，最后的结果是`0000 0000 0000 0001 0000 0000 0000 1010`(从低位覆盖)，所以输出结果为65546。

### mutable

mutable也是为了突破const的限制而设置的。**被mutable修饰的变量(mutable只能由于修饰类的非静态数据成员)，将永远处于可变的状态，即使在一个const函数中**。

**一个常用的场景是计算某个函数被调用的次数**。

### extern

**外部变量**：extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行链接指定。extern关键字用来声明另一个文件中的全局变量。 

1. `extern "c"`：与"C"一起连用时，如: 

   `extern "C" void fun(int a, int b);`

   则告诉编译器在编译fun这个函数名时按着C的规则去翻译相应的函数名而不是C++的，C++的规则在翻译这个函数名时会把fun这个名字变得面目全非，可能是fun@aBc_int_int#%$也可能是别的，这要看编译器的"脾气"了(不同的编译器采用的方法不一样，因为C++支持函数的重载)

   C++语言在编译的时候为了解决函数的多态问题，会将函数名和参数联合起来生成一个中间的函数名称，而C语言则不会，因此会造成链接时找不到对应函数的情况，此时C函数就需要用extern “C”进行链接指定，这告诉编译器，请保持我的名称，不要给我生成用于链接的中间函数名。

2. **修饰变量或函数时**，如在头文件中: `extern int g_Int;` 它的作用就是**声明函数或全局变量的作用范围的关键字**，其声明的函数和变量可以在本模块或其他模块中使用，**记住它是一个声明不是定义!**也就是说B模块(编译单元)要是引用模块(编译单元)A中定义的全局变量或函数时，它只要包含A模块的头文件即可,在编译阶段，模块B虽然找不到该函数或变量，但它不会报错，它会在**链接**时从模块A生成的目标代码中找到此函数。

##### **extern 变量**

> 在一个源文件里定义了一个数组：char a[6];
> 在另外一个文件里用下列语句进行了声明：extern char *a；
> 请问，这样可以吗？ 


不可以，程序运行时会告诉你非法访问。原因在于，指向类型T的指针并不等价于类型T的数组。`extern char *a`声明的是一个指针变量而不是字符数组，因此与实际的定义不同，从而造成运行时非法访问。应该将声明改为extern char a[ ]。

在使用extern时候要严格对应声明时的格式
extern用在变量声明中常常有这样一个作用，你在.c文件中声明了一个全局的变量，这个全局的变量如果要被引用，就放在.h中并用extern来声明。

##### **extern函数声明**

如果函数的声明中带有关键字extern，仅仅是暗示这个函数可能在别的源文件里定义，没有其它作用。

#####  **extern 和 static**

extern 表明该变量在别的地方已经定义过了,在这里要使用那个变量。 static 表示静态的变量，分配内存的时候, 存储在静态区,不存储在栈上面。static修饰的全局变量声明与定义同时进行；static修饰全局变量的作用域只能是本身的编译单元，也就是说它的“全局”只对本编译单元有效，其他编译单元则看不到它

extern和static是矛盾的，不能同时使用。

```
test1.h:
#ifndef TEST1H
#define TEST1H
static char g_str[] = "123456"; 
void fun1();
#endif

test1.cpp:
#include "test1.h"
void fun1()  {   cout << g_str << endl;  }

test2.cpp
#include "test1.h"
void fun2()  {   cout << g_str << endl;  }

```

以上两个编译单元可以连接成功, 当你打开test1.obj时，你可以在它里面找到字符串"123456",同时你也可以在test2.obj中找到它们，它们之所以可以连接成功而没有报重复定义的错误是因为虽然它们有相同的内容，但是存储的物理地址并不一样，就像是两个不同变量赋了相同的值一样，而这两个变量分别作用于它们各自的编译单元。 也许你比较较真，自己偷偷的跟踪调试上面的代码,结果你发现两个编译单元（test1,test2）的g_str的内存地址相同，于是你下结论static修饰的变量也可以作用于其他模块，但是我要告诉你，那是你的编译器在欺骗你，大多数编译器都对代码都有优化功能，以达到生成的目标程序更节省内存，执行效率更高，当编译器在连接各个编译单元的时候，它会把相同内容的内存只拷贝一份，比如上面的"123456", 位于两个编译单元中的变量都是同样的内容，那么在连接的时候它在内存中就只会存在一份了，如果你把上面的代码改成下面的样子，你马上就可以拆穿编译器的谎言:

```
 (1) test1.cpp:
    #include "test1.h"
    void fun1()
    {
        g_str[0] = ''a'';
        cout << g_str << endl;
    }

    (2) test2.cpp
    #include "test1.h"
    void fun2()  {  cout << g_str << endl;  }
    (3) void main()     {
        fun1(); // a23456
        fun2(); // 123456
    }
```

这个时候你在跟踪代码时，就会发现两个编译单元中的g_str地址并不相同，因为你在一处修改了它，所以编译器被强行的恢复内存的原貌，在内存中存在了两份拷贝给两个模块中的变量使用。**正是因为static有以上的特性，所以一般定义static全局变量时，都把它放在原文件中而不是头文件，**这样就不会给其他模块造成不必要的信息污染。

##### **extern 和const**

  C++中**const修饰的全局常量具有跟static相同的特性**，**即它们只能作用于本编译模块中，但是const可以与extern连用来声明该常量可以作用于其他编译模块中,** 如`extern const char g_str[];`
  然后在原文件中别忘了定义:   `const char g_str[] = "123456";` 

所以当const单独使用时它就与static相同，而当与extern一起合作的时候，它的特性就跟extern的一样了，相当于将const的static属性给去掉了

```
//demo.h
extern const int MyAge = 30
//注意: 这里虽然加了extern, 但在定义声明的同时, 又给MyAge初始化了, 所以这里即声明了又定义了,
// 严格的说: 这里是定义式，如果demo.h被多个.cpp包含, 就会出现"重复定义错误"
// test1.cpp
#include "demo.h"

void test1()
{
    std::cout << MyAge;
}

// test2.cpp
#include "demo.h"

void test2()
{
  std::cout << MyAge;
}
```

解决上述错误，有两个解决方法：

```
//法一：
// demo.h
// 仅仅是声明式
extern const int MyAge;

// demo.cpp
// 这里才是定义式
const int MyAge = 30;

// test1.cpp
#include "demo.h"

void test1()
{
    std::cout << MyAge;
}

// test2.cpp
#include "demo.h"

void test2()
{
  std::cout << MyAge;
}
```

```
//法二：
// demo.h

const int MyAge = 30;

// test1.cpp
#include "demo.h"

void test1()
{
    std::cout << MyAge;
}

// test2.cpp
#include "demo.h"

void test2()
{
  std::cout << MyAge;
}
```

**上述两个方法的区别在哪呢？？**

对于法二：在头文件直接定义const变量, 那么当此头文件被多个地方引用时， 相当于每个引用的地方都包含了此const变量的一个副本, 即: 从存储空间上讲, 如果有3处引用, 就相当于定义3个相同的”局部const变量”。

而对于法一：如果此头文件被多个地方引用时, 此const变量始终只有一个, 可以说是真正的全局变量.

一般情况下, const的变量的”占用空间成本”和”构造成本”都非常低, 几乎可以忽略不计, 因此一般使用法二的方式就够了, 而且从理解上来讲也先的清晰, 这也是C++工程实践推荐的做法。

一般如果你用C++编程, 那么对const变量导致性能(const的多次构造成本)和存储空间(多个const副本)其实是不太敏感的, 如果真要敏感, 就说明你不应该用C++写, 而应该使用C语言来写。这也就解释了为什么C++项目中我们一般很少见到使用”extern const”的, 并且也不推荐这样使用, 而在C语言中 “extern const”使用的很频繁。

能严格要求使用C语言(而非C++)的场景, 一般都是一些单片机或嵌入式的系统环境, (或者是操作系统内核), 其对性能和内存的占用都是非常敏感的,所以大量使用extern const也就见怪不怪了. 而用C++的场合, 项目工程的可阅读性,可维护性远远大于这一点性能和存储占用, 所以C++场合, 推荐使用法二的方式。



**链接与const、static、extern——内存分配与读写** 
**无链接性：**在代码块中的局部变量（包括static局部变量） 
**外部链接：**函数之外定义的所有变量（除了const变量）和函数默认为外部链接性。在定义时使用extern关键字显式指定标识符具有外部链接。也就是说在多个文件程序中，可以在文件并且只能在一个文件中定义全局变量，其他文件要使用该变量，要在变量前添加extern关键字。当有extern时，只是告知编译器存在这个变量，编译器并不为该变量分配存储空间，即真正的声明；若没有extern，则在声明的同时，编译器也为该变量分配存储空间。 
**内部链接：**全局static变量和const变量为内部链接，为了使const具有外部链接以便让另外一个文件可以对它引用，必须在当前文件里明确把它定义为extern并初始化。 
**应使用链接性为外部的多文件程序的不同文件中共享数据，而使用链接性为内部的静态变量在同一文件中的多个函数间共享数据**

### volatile

作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值。

**简单地说就是防止编译器对代码进行优化**。当要求使用volatile 声明的变量的值的时候，**系统总是重新从它所在的内存读取数据，而不是使用保存在寄存器中的备份**。即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存。



- **易变性**：两条语句，下一条语句不会直接使用上一条语句对应的volatile变量的寄存器内容，而是**重新从内存中读取**。（因为因为一般的对象编译器可能会将其的拷贝放在寄存器中用以加快指令的执行速度）

- 不可优化：volatile告诉编译器，不要对我这个变量进行各种激进的优化，**甚至将变量直接消除**，保证程序员写在代码中的指令，一定会被执行。

  ```
  int a;
  int b;
  int c;
  a=1;
  b=2;
  c=3;
  printf("%d,%d,%d",a,b,c);
  上述代码非volatile变量a，b，c全部被编译器优化掉了 (optimize out)，因为编译器通过分析，发觉a，b，c三个变量是无用的，可以进行常量替换。最后的汇编代码相当简洁，高效率。
  如果将a,b,c换成volatile，这个区别，反映到汇编语言中，就是三个变量仍旧存在，需要将三个变量从内存读入到寄存器之中，然后再调用printf()函数。
  ```

- 顺序性：保证volatile变量间的顺序性，**编译器不会进行乱序优化**。

  volatile跟多线程无关，它不是一种同步手段，用它来实现线程安全是错的。**原子和锁会保证线程安全性**。

##### **volatile与多线程语义**

对于多线程编程而言，在临界区内部，可以通过互斥锁（mutex）保证只有一个线程可以访问该临界区的内容，因此临界区内的变量不需要是 volatile 的；而在临界区外部，被多个线程访问的变量应声明为 volatile 的，这也符合了 volatile 的原意：防止编译器缓存（cache）了被多个线程并发用到的变量。
不过，需要注意的是，由于 volatile 关键字的“顺序执行特性”并非会完全保证语句的顺序执行（如 volatile 变量与非volatile 变量之间的操作；又如一些 CPU 也会对语句的执行顺序进行优化），**因此导致了对 volatile 变量的操作并不是原子的，也不能用来为线程建立严格的 happens-before 关系。**

```

int nNum1 = 0;
volatile bool flag = false;
 
thread1()
{
    // some code
 
    nNum1 = 666;  // 语句1
 
    flag = true;  // 语句2
}
 
thread2()
{
    // some code
 
    if (true == flag)
    {
        // 语句3：按照程序设计的预想，此处的nNum1的值应为666，并据此进行逻辑设计
    }
}
```

在上述代码中，我们的设计思路是先执行 thread1() 中的“语句1”、“语句2”、再执行 thread2() 中的“语句3”，不过实际上程序的执行结果未必如此。根据 volatile 的“顺序性”，非 volatile 变量 nNum1 和 volatile 变量 flag 的执行顺序，可能会被编译器（或 CPU）进行乱序优化，最终导致thread1中的“语句2”先于“语句1”执行，当“语句2”执行完成但“语句1”尚未执行时，此时 thread2 中的判断语句“if (true == flag)”是成立的，但实际上 nNum1 尚未进行赋值为666（语句1尚未执行），所以在判断语句中针对 nNum1 为666的前提下进行的相关操作，就会有问题了。

这是一个在多线程编程中，使用 volatile 不容易发现的问题。

实际上，上述多线程代码想实现的就是一个 happens-before 语义，即保证 thread1 代码块中的所有代码，一定要在 thread2 代码块的第一条代码之前完成。使用互斥锁（mutex）可以保证 happens-before 语义。但是，在 C/C++ 中的 volatile 关键词不能保证这个语义，也就意味着在多线程环境下使用 C/C++ 的 volatile 关键词，如果不够细心，就可能会出现上述问题。

```
class AObject
{
public:
    void wait()
    {
        m_flag = false;
        while (!m_flag)
        {
            this_thread::sleep(1000ms);
        }
    }
    void notify()
    {
        m_flag = true;
    }

private:
    volatile bool m_flag;
};

AObject obj;

...

// Thread 1
...
obj.wait();
...

// Thread 2
...
obj.notify();
...
```

因为在多核CPU中，每个CPU都有自己的缓存。缓存中存有一部分内存中的数据，**CPU要对内存读取与存储的时候都会先去操作缓存，而不会直接对内存进行操作。所以多个CPU“看到”的内存中的数据是不一样的，这个叫做内存可见性问题（memory visibility）**。放到例子中就是，Thread 2修改了m_flag对应的内存，但是Thread 1在其他CPU核上运行，所以Thread 1不一定能看到Thread 2对m_flag做的更改。C++11开始，C++标准中有了线程的概念，C++标准规定了什么情况下一个线程一定可以看到另一个线程做的内存的修改。而根据标准，上述例子中的Thread 1可能永远看不到m_flag变成true，更严重的是，Thread 1对m_flag的读取会导致Undefined Behavior。

##### **volatile指针**

(1) 可以把一个非volatile int赋给volatile int，但是不能把非volatile对象赋给一个volatile对象。

(2) 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。
(3) C++中一个有volatile标识符的类只能访问它接口的子集，一个由类的实现者控制的子集。用户只能用const_cast来获得对类型接口的完全访问。此外，volatile向const一样会从类传递到它的成员。

**volatile修饰函数**

直接修饰C函数，方便编译器进行优化其实这里的作用是帮助编译器进行优化，而不是防止编译器优化，对应oom()和do_exit()函数而言，它们是永远都不会返回的，如果还将调用它们的函数的返回地址保存在堆栈上的话，是没有任何意义的，

但是加了volatile过后，就意味着这个函数不会返回，就相当于告诉编译器，我调用后是不用保存调用我的函数的返回地址的。这样就达到了优化的作用。

**面试题—>一个参数可以即是const又是volatile吗？**

**可以，一个例子是只读状态寄存器。**

C语言中const 是指只读，而不是常量。比如单片机的AD结果寄存器，其值只能读，程序不能改变它，但其能被外界改变。

### explicit

关键字explicit只对**一个实参的构造函数有效**，**只能在类内定义**，**它表示禁止对构造函数进行隐式转换**。当我们用explicit关键字声明构造函数时，**它将只能以直接初始化的形式使用**，而不能使用赋值初始化。

```
explicit A(const string &s):a(s) {};
A a("abc");//直接初始化。
a.fun(static_cast<A>(cin));//强制执行显式转换。
```

### typedef

**typedef表示为参数定义一个别名，具有一定的封装性**。

```
typedef (int*) pInt1;
#define pInt2 int*
pInt1 a, b; // a和b都是int类型的指针
pInt2 a, b; // a是int类型的指针，但是b只是一个int变量
```

### sizeof

**sizeof返回的是变量所占用的字节数，是运算符而不是函数**，常见的sizeof如下所示：

```
// 基本数据类型的sizeof
cout<<sizeof(char)<<endl;                    //结果是1
cout<<sizeof(int)<<endl;                     //结果是4
cout<<sizeof(unsigned int)<<endl;            //结果是4
cout<<sizeof(long int)<<endl;                //结果是4
cout<<sizeof(short int)<<endl;               //结果是2
cout<<sizeof(float)<<endl;                   //结果是4
cout<<sizeof(double)<<endl;                  //结果是8

// 指针变量的sizeof
char *pc ="abc";
sizeof(pc);     // 结果为4
sizeof(*pc);      // 结果为1
int *pi;
sizeof(pi);     //结果为4
sizeof(*pi);      //结果为4

// 数组的sizeof值等于数组所占用的内存字节数
char a1[] = "abc";
int a2[3];
sizeof( a1 ); // 结果为4，字符 末尾还存在一个NULL终止符
sizeof( a2 ); // 结果为3*4=12（依赖于int）
void foo3(char a3[3]) // 数组作为函数参数时就变成指针   
{
	int c3 = sizeof( a3 ); // c3 = 4
}
void foo4(char a4[])
{
	int c4 = sizeof( a4 ); // c4 = 4
}

// 空结构体的sizeof
// C++编译器会在空类或空结构体中增加一个虚设的字节（有的编译器可能不止一个），
// 以确保不同的对象都具有不同的地址。
struct S5 { };
sizeof( S5 ); // 结果为1

// 类的sizeof
class A
{
    public:
        int b;
        float c;
        char d;
}; // 内存对齐
int main(void)
{
    A object;
    cout << "sizeof(object) is " << sizeof(object) << endl;// 12 
    return 0 ;
}
```

**说明sizeof的使用场合？**

- **查看某个对象所占用的字节数**。
- **与存储分配和I/O系统那样的例程进行通信**。

**说明sizeof和strlen？**

- **sizeof是运算符而strlen是函数**。
- strlen的结果是**在运行期计算出来的**，结果是**字符串的长度**而不是所占用的内存大小。
- strlen的参数**只能是char*，而且必须是以’\0’结尾的**。

### inline

使用inline声明的函数叫做**内联函数**，原理是将函数调用替换为函数实体（**编译期**），**不需要中断调用，减少了函数参数压栈过程，增加了函数调用的效率**。但是有几点需要注意：

- 内联函数**只适合体积较小**（一般十行以内），没有循环、递归和开关操作的函数；
- 在类内定义的成员函数都是内联函数；
- 过多使用内联函数可能会**增加程序体积**，**减少高速缓存命中率**。



##### **C++中哪些函数不能声明为inline？**

- **包含了递归、循环等结构的函数一般不会被内联**。
- **虚函数**一般不会内联，但是如果编译器能在编译时确定具体的调用函数，那么仍然会就地展开该函数。
- 如果通过函数指针调用内联函数，那么该函数将不会内联而是通过call进行调用。
- **构造和析构函数一般会生成大量代码，因此一般也不适合内联**。
- 如果内联函数调用了其他函数也不会被内联。

如果想要阻止某函数被内联，可以在函数体前加上 `__attribute__((noinline))` 。

### template

C++ 中泛型机制的实现。

##### 函数模板

```
//以swap为例
//method.h 
template<typename T> void swap(T& t1, T& t2);
//必须在method.h文件的最后一行加入#include "method.cpp"。
#include "method.cpp"

//method.cpp
template<typename  T> void swap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}
//main.cpp
#include <stdio.h>
#include "method.h"
int main() {
    //模板方法 
    int num1 = 1, num2 = 2;
    swap<int>(num1, num2);
    printf("num1:%d, num2:%d\n", num1, num2);  
    return 0;
}
```

##### 类模板

考虑我们写一个简单的栈的类，这个栈可以支持int类型，long类型，string类型等等，不利用类模板，我们就要写三个以上的stack类，其中代码基本一样，通过类模板，我们可以定义一个简单的栈模板，再根据需要实例化为int栈，long栈，string栈。

```
//statck.h
template <class T> class Stack {
    public:
        Stack();
        ~Stack();
        void push(T t);
        T pop();
        bool isEmpty();
    private:
        T *m_pT;        
        int m_maxSize;
        int m_size;
};

#include "stack.cpp"
```

```
 
//stack.cpp
template <class  T>  Stack<T>::Stack(){
   m_maxSize = 100;      
   m_size = 0;
   m_pT = new T[m_maxSize];
}
template <class T>  Stack<T>::~Stack() {
   delete [] m_pT ;
}
        
template <class T> void Stack<T>::push(T t) {
    m_size++;
    m_pT[m_size - 1] = t;
    
}
template <class T> T Stack<T>::pop() {
    T t = m_pT[m_size - 1];
    m_size--;
    return t;
}
template <class T> bool Stack<T>::isEmpty() {
    return m_size == 0;
}
//在类定义体外定义成员函数时，若此成员函数中有模板參数存在，则除了须要和一般类的体外定义成员函数一样的定义外，还需在函数体外进行模板声明 
//main.cpp
#include <stdio.h>
#include "stack.h"
int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    
    while (!intStack.isEmpty()) {
        printf("num:%d\n", intStack.pop());
    }
    return 0;
}
```

