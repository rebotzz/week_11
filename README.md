# week_11
第11周的学习(C++算入门了吧)

**********************
1.优先级队列学习;priority_queue 本质是容器适配器(适配器模式)堆,默认是大堆,仿函数默认less; 
priority_queue模拟实现;建堆的时间复杂度O(N),向上/下调整算法时间复杂度O(logN);
2.仿函数(函数对象)学习,本质是类对象重载operator()(参数),有点像函数;
3.双端队列学习,有list和vector的优点,但是不够极致,一般作为stack和queue底层容器,一般只头插头删,尾插尾删
4.反向迭代器实现:迭代器适配器,分装正向迭代器实现,底层不同的正向迭代器也能实现,但是要支持双向


************************
数值计算算法实现：
1.实现了拉格朗日插值算法
2.实现了牛顿插值算法
3.牛顿插值算法优化
4.最小二乘法模拟实现
5.龙贝格积分算法模拟实现