# this指针

##### 1、this指针指向的是对象的首地址，首地址一般是第一个变量的地址，若有虚函数，则是虚函数表的首地址

2、return this;返回的是对象的首地址
       return *this;返回的是对象；

# share_ptr

## 若智能指针指向的对象要求能被多个智能指针使用，用share_ptr

## 若智能指针指向的对象要求能被1个智能指针使用，用unique_ptr

而unique_ptr之间的赋值需要配合std::move(),这样传值完了后之前的对象也同样报废了。

## 1、误用代码点

##### 误以为申请了一个整数型，内存大小为5个int类型的区域

```c++
shared_ptr<int> data = make_shared<int>(5);
```



## 2、正确用法

##### 智能指针指向一个整数型，内存大小为5个int类型的区域

```c++
shared_ptr<int> data(new int[5]);
```

##### int类型可以换成任意类型或者对象，例如：

```c++
shared_ptr<string> data = make_shared<string>(5);
```

## 3、需要注意的点

##### 智能指针的赋值会增加引用次数

```c++
shared_ptr<int> data(new int[5]);
shared_ptr<int> p = data;
```

p和data指向的是一个对象，而引用的次数代表着对象被多少个指针指向着，故p.use_count()和data.use_count()都为2，

##### 不会增加引用次数的方式

```c++
shared_ptr<int> data(new int[5]);
data.reset(p.get());
```

这样的方式，也会使data.use_count()重置为1

此时使用data.reset()会让data指向的之前的对象释放掉，unique_ptr也是如此

# unique_ptr

```c++
template<typename T>
class LineList
{


public:
	LineList(int Size);
	LineList();
	~LineList();
    
	//深拷贝构造函数
	LineList(LineList<T> &rhs);
	//移动拷贝构造函数
	LineList(LineList<T> &&rhs);
	//深拷贝赋值构造函数
	LineList<T> & operator=(LineList<T> &rhs);
	//移动赋值函数
	LineList<T> & operator=(LineList<T> &&rhs);
    
	int GetLength();
	int GetMaxSize();
private:
	//T *data = NULL;		//普通---指示动态分配数组的指针
	std::unique_ptr<T> data;	//智能指针---指示动态分配数组的指针
	int MaxSize;		//顺序表的最大容量
	int length;
};
```





```c++
template<typename T>
LineList<T>::LineList(LineList<T> &&rhs)
{
	printf("移动构造函数\n");

	this->data = move(rhs.data);
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;
	rhs.length = 0;
	rhs.MaxSize = 0;

}

```

通过move调用unique_ptr的移动重载=

```c++
template<typename T>
inline LineList<T> & LineList<T>::operator=(LineList<T> &rhs)
{
	printf("赋值重载=\n");
	if (this == &rhs)
	{
		return *this;
	}
	this->data.reset((T *)malloc(rhs.GetMaxSize() * sizeof(T)));
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;

	auto pData = this->data.get();
	auto pRhs = rhs.data.get();

	memset(pData, 0, this->MaxSize * sizeof(T));
	for (int i = 0; i < this->length; i++)
	{
		pData[i] = pRhs[i];

	}
	return *this;
}
```



```c++
template<typename T>
inline LineList<T> & LineList<T>::operator=(LineList<T> && rhs)
{
	printf("移动重载=\n");
	if (this == &rhs)
	{
		return *this;
	}
	this->data = move(rhs.data);
	this->length = rhs.length;
	this->MaxSize = rhs.MaxSize;
	rhs.length = 0;
	rhs.MaxSize = 0;
	return *this;
}
```

通过move调用unique_ptr的移动重载=

```c++
this->data = move(rhs.data);
```

执行这条语句前

![1612095065121](C:\Users\guibinw\AppData\Local\Temp\1612095065121.png)

执行后

![1612095145326](C:\Users\guibinw\AppData\Local\Temp\1612095145326.png)

可以看到指针移动到另一个智能指针里面去了

```c++
	LineList<int> List4;
	List4 = move(List5);
	List5.PrintList();		
	List4.PrintList();
```

通过move调用LineList的移动重载=



# 重载

类中的重载会有个默认参数

```c++
 LineList<T>& operator+( LineList<T> &rhs);
```

这样写其实代码是这样的

```c++
 LineList<T>& operator<<( *this,LineList<T> &rhs);
```

故当重载<<时,在类中这样写会出现提供过多参数的错误

```c++
ostream& operator<<(ostream & os,LineList<T> &rhs);
```



要避免这样的错误需要用类外部的重载<<函数，但是这样就不能访问类内部的成员了。

要实现写在类中能访问类内成员，还不出现提供过多参数的错误

#### 第一种解决方法:

```c++
friend ostream& operator<<(ostream & os,  LineList<T> &rhs)
{
    //逻辑代码
}
```

注意:不能在类外实现重载的逻辑代码

因为友元函数虽然可以访问类内部的成员，但是它相对于类是独立的，它的实现不能依赖类。代码中用到模板类template<class T> 而在类内声明友元函数的时候也用到了<T>,所以此时友元函数是依赖于类的实现而实现的，编译器才会报错。 

#### 第二种解决方法：

在类的内部声明友元函数的时候在之前为它单独配一个模板类型，然后在外部实现 



