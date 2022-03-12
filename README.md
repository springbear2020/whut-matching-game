
> Gitee 项目地址：[欢乐连连看](https;//gitee.com/Spring-_-Bear/llk.git)
> 实验指导视频链接：[欢乐连连看(C++ & MFC)指导视频](https://www.bilibili.com/video/BV1cK411g7sP?from=search&seid=7868355334761322039&spm_id_from=333.337.0.0)
> 温馨提示：克隆本仓库到本地并使用 Visual Studio 2019 打开工程即可。全程使用 git 进行版本控制，可回退到指定阶段
## 一、游戏介绍
“连连看游戏”是给一堆图案中的相同的图案进行配对的简单游戏，在一定的规则之内对相同的图案进行消除处理，在规定时间内消除所有图案后玩家就获胜。“连连看游戏”只要将相同的两张元素用三根以内的直线连在一起就可以消除，规则简单容易上手，游戏速度节奏快，画面清晰可爱。

## 二、游戏规则
1. 一条直线消子：选择的两张图片花色相同，并且处于同一条水平线或者同一条垂直线上，并且两张图片之间没有其余的图片，则可以进行一条直线消子。
2.  两条直线消子：选择的两条图片花色相同，既不在同一水平线上，也不再同一垂直线上，两个图片的连通路径至少有两条直线组成，两条直线经过的路径必须是空白，中间只要有一个非同种类的图片，该路径无效。
3. 三条直线消子：使用一个折点的路径无法连通的两个图片，只能如图中连线所示连通，即连通路径有三条直线，在该直线的路径上没有图案出现，只能是空白区域。

## 三、功能简介
![在这里插入图片描述](https://img-blog.csdnimg.cn/eaddd0d34e4a44d787a3356966611d67.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAU3ByaW5nLV8tQmVhcg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
## 四、数据结构设计
1. 顶点存储结构：添加 global.h 文件，定义结构体 Vertex，用于保存游戏地图中一个点的行号、列表、值信息。代码如下：

```cpp
typedef struct tagVertex{
 int row; // 行
 int col; // 列
 int info; // 信息类
}Vertex;
```
2. 游戏地图存储结构：使用二维数组来保存连连看游戏地图，给每种图片一个编号，并将这些编号保存在二
维数组中。用户在屏幕上选择 2 张图片，对应为数组中的两组坐标。分别实现三个消子判断算法：“一条直线消子”、“两条直线消子”、“三条直线消子”，并使用这三个算法进行消子判断。若符合消子规则，就在屏幕上消除一对图片，并把数组对应元素清空。
> 2.1 游戏地图中的图片种类和重复次数与游戏的级别和难度有关。图片种类越多，重复次数越小，游戏的难度越大，反之则越容易。
> 2.2 因为 2 张同类的图片才能消。为保证游戏能完全消完，每种图片重复的次数一定要是偶数，即 2 的倍数。
> 2.3 地图的大小与图片元素种类之间的关系：地图的行数 * 地图的列数 = 图片的种类数 * 每种图片重复的次数
> 2.4 地图数据的存储
> >1) 用 int 类型动态二维数组(int** m_pGameMap)存储地图中元素图片的编号。
>> 2) 获得某行某列对应的元素数值

## 五、游戏界面
1. 欢迎界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214758966.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

2. 游戏界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214804405.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

3. 暂停界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214809305.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

4. 提示界面

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214814589.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

5. 背景音乐

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214822638.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

6. 帮助信息

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214830582.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

7. 版权信息

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210503214835679.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl81MTAwODg2Ng==,size_16,color_FFFFFF,t_70#pic_center)

