# 线性回归大结局(岭(Ridge)、 Lasso回归原理、公式推导、评价方式)，你想要的这里都有

<h2 style="text-align:center">线性模型</h2>

所谓线性模型就是通过数据的线性组合来拟合一个数据，比如对于一个数据 $X$
$$
X = (x_1, x_2, x_3, ...,x_n) \tag{1}
$$
$$
Y = f(X) = a_1x_1 + a_2x_2 + ... a_nx_n + b \tag{2}
$$

来预测 $Y$的数值。例如对于人的两个属性 <span style="color:red;font-weight:bold">(鞋码，体重) </span>来预测 <span style="color:red;font-weight:bold">身高 </span>。从上面来看线性模型的表达式简单、比较容易建模，而却有很好的解释性。比如 身高$(H)$和鞋码$(S)$、体重$(W)$的关系。
$$
H=0.3*S + 0.7*W + 20 \tag{3}
$$


所谓解释性简单一点来说就是知道模型哪个属性更加重要，比如说对于上述表达式来说，就意味着对于身高来说体重的因素比较大，体重更加重要，这个例子纯为了解释为什么线性模型有很好的解释性，可能不够严谨。对于线性模型来说，旨在学习到所有的 $a_i, b$，即模型的参数。

<h2 style="text-align:center">普通线性回归</h2>

对于一个数据集
$$
Dataset = \{ (x_1, y_1), (x_2, y_2), (x_3, y_3), ..., (x_n, y_n) \} \ \ , \ y_i \in R \tag{4}
$$
其中 $x_i$, 可能含有多个属性，如 $x_i$ 有$m$个属性时, 即 $x_i = (x_{i1}, x_{i2}, ..., x_{im})$，$y_i$ 是一个实数值。线性回归需要做的事就是需要找到一套参数尽可能的使得模型的输出跟 $y_i$接近。

不妨设如下表达式，我们的目标就是让 $f(x_i)$ 越靠近真实的 $y_i $越好。
$$
f(x_i) = a_1x_{i1} + a_2x_{i2} + ... + a_mx_{im} + b \tag{5}
$$
即 : 
$$
f(x_i) = b + \sum_{j = 1}^{m}a_jx_{ij} \tag{6}
$$
为了方便使用一个式子表示整个表达式，不妨令 : 
$$
x_i = (x_{i1}, x_{i2}, ..., x_{im}, b) \tag{7}
$$
$$
\hat{w} = (a_1, a_2, ..., a_m, 1)^T \tag{8}
$$



上述表达式用矩阵形式表示为 ：
$$
\left[ \begin{matrix} x_{i1} & x_{i2} & x_{i3} & ... & x_{i(m - 1)} & x_{im} & b\end{matrix} \right] \cdot \left[\begin{matrix} a_1 \\ a_2 \\ a_3 \\ .\\.\\. \\ a_{m-1} \\ a_m \\ 1\end{matrix} \right] = f(x_i) \tag{9}
$$
简写为 : 
$$
f(x_i) = x_i\cdot \hat{w} \tag{10}
$$

现在需要来衡量模型的输出和真v是值之间的差异，我们这里使用均方误差$MSE(Mean\ Squared\ Error)$来衡量，即对于 $y_i$来说误差为:
$$
\mathcal{l_i} = (f(x_i) - y_i)^2 \tag{11}
$$
像这种基于最小化 $MSE$ 来求解模型参数的方法叫做最小二乘法。对于整个数据集来说他的误差为 $\mathcal{L}$ ：
$$
\mathcal{L} = \sum_{i = 1}^{n}(f(x_i) - y_i)^2\ \tag{12}
$$
现在我们将他们用矩阵来表示 其中 ：
$$
Y = (y_1, y_2, y_3, ..., y_{n - 2}, y_{n - 1}, y_{n})^T = \left[\begin{matrix}y_1 \\ y_2 \\ y_3 \\ . \\. \\. \\ y_{n - 2} \\ y_{n - 1}\\ y_{n}\end{matrix}\right] \tag{13}
$$

$$
X = (x_1; x_2; ...; x_{n - 1}; x_n)= (x_1, x_2, ..., x_{n - 1}, x_n)^T =  \left[\begin{matrix}x_1 \\ x_2  \\ . \\. \\. \\ x_{n-1}\\ x_{n}\end{matrix}\right]=  \left[\begin{matrix}x_{11} & x_{12} & x_{13} & . .. & x_{1m} &1& \\ x_{21} & x_{22} & x_{23} & ... & x_{2m} &1& \\ . & . & . & . & . &.\\. &  . & . & . & . &.  \\ . & . & . & . & . &. \\ x_{(n - 1)1} & x_{(n - 1)2} & x_{(n - 1)3} & ... & x_{(n - 1)m} &1\\ x_{n1} & x_{n2} & x_{n3} & ... & x_{nm} & 1\end{matrix}\right] \tag{14}
$$

$$
f(X) =  \left[\begin{matrix}x_{11} & x_{12} & x_{13} & . .. & x_{1m} &1& \\ x_{21} & x_{22} & x_{23} & ... & x_{2m} &1& \\ . & . & . & . & . &.\\. &  . & . & . & . &.  \\ . & . & . & . & . &. \\ x_{(n - 1)1} & x_{(n - 1)2} & x_{(n - 1)3} & ... & x_{(n - 1)m} &1\\ x_{n1} & x_{n2} & x_{n3} & ... & x_{nm} & 1\end{matrix}\right] \cdot \left[\begin{matrix} a_1 \\ a_2 \\ a_3 \\ .\\.\\. \\ a_{m-1} \\ a_m \\ b\end{matrix} \right] = \left[\begin{matrix} x_1\hat{w} \\ x_2\hat{w} \\ x_3\hat{w} \\ .\\.\\. \\ x_{n-2}\hat{w} \\ x_{n - 1}\hat{w} \\ x_{n}\hat{w}\end{matrix} \right] = \left[\begin{matrix}\hat{y}_1\\ \hat{y}_2\\ \hat{y}_3\\ \\.\\.\\.\\\hat{y}_{n-2}\\\hat{y}_{n-1}\\\hat{y}_n\\ \end{matrix}\right] \tag{15}
$$

其中 $\hat{y}_i$ 是模型的预测值 $y_i$ 是数据的真实值，$m$ 是一条数据 $x_i$的属性的个数。现在来梳理一下数据的维度：
$$
X : n\times (m+1) \\
\hat{w} : (m+1)\times 1\\
Y : n\times 1 \\
f(X) : n\times 1
$$
那容易得出，对于整个数据集的误差为 $\mathcal{L}(w, b)$ ：
$$
\mathcal{L}(w, b) = \mathcal{L}({\hat{w}}) = \sum_{i=1}^{n}( \hat{y} - y_i)^2 = \sum_{i=1}^{n}(x_i\hat{w}-y_i)^2 = ||X\hat{w}-Y||_2^2  = (X\hat{w}-Y)^T(X\hat{w}-Y) \tag{16}\\
x_i = (x_{i1}, x_{i2}, ..., x_{im}, b)\\
\hat{w} = (a_1, a_2, ..., a_m, 1)^T
$$
现在来仔细分析一下公式$(16)$，首先对于一个$1\times n$或者$n \times 1$向量来说，它的二范数为：
$$
||x||_2 = \sqrt{\sum_{i=1}^{n}x_i^2}
$$
二范数平方为：
$$
||x||_2^2 = \sum_{i=1}^{n}x_i^2
$$
所以就有了 $\sum_{i=1}^{n}(X\hat{w}-Y)^2 = ||Y-X\hat{w}||_2^2$， 那么对于公式$(16)$来说 $X\hat{w}-Y$ 是一个 $n\times 1$的向量：
$$
X\hat{w}-Y = \left[\begin{matrix}\hat{y}_1 - y_1 \\ \hat{y}_2 - y_2 \\.\\.\\.\\\hat{y}_{n-1} - y_{n-1} \\\hat{y}_{n}- y_{n} \end{matrix}\right]
$$
所以根据矩阵乘法就有：
$$
(X\hat{w} - Y)^T(X\hat{w} - Y)=\left[\begin{matrix} \hat{y}_1 - y_1  ,& \hat{y}_2 - y_2 ,&.&.&.&\hat{y}_{n-1} - y_{n-1}  , &\hat{y}_{n} - y_{n} \end{matrix}\right]\cdot \left[\begin{matrix}\hat{y}_1 - y_1 \\\hat{y}_2  - y_2 \\.\\.\\.\\\hat{y}_{n-1} - y_{n-1} \\\hat{y}_{n} - y_{n} \end{matrix}\right] = \sum_{i=1}^{n}(\hat{y}- y_i )^2 \tag{17}
$$
根据上面的分析最终就得到了模型的误差：
$$
\mathcal{L}(w, b) = \mathcal{L(\hat{w})} = ||X\hat{w} - Y||_2^2  = (X\hat{w} - Y)^T(X\hat{w} - Y) \tag{18}
$$
现在就需要最小化模型的误差，即优化问题，易知$\mathcal{L(w, b)}$是一个关于 $\hat{w}$ 的凸函数，则当它关于$\hat{w}$导数为0时求出的$\hat{w}$是$\hat{w}$的最优解。这里不对其是凸函数进行解释，如果有时间以后专门写一篇文章来解读。现在就需要对$\hat{w}$进行求导。
$$
\mathcal{L(\hat{w})} = ||X\hat{w} - Y||_2^2  = (X\hat{w} - Y)^T(X\hat{w} - Y)\\
= ((X\hat{w})^T - Y^T)(X\hat{w} - Y) = (\hat{w}^TX^T - Y^T)(X\hat{w} - Y)\\
=\hat{w}^TX^TX\hat{w} - \hat{w}^TX^TY - Y^TX\hat{w} + Y^TY
$$
我们现在要对上述公式进行求导，我们先来推导一下矩阵求导法则，请大家扶稳坐好：

<span style="background-Color:skyblue;font-weight:bold">公求导式法则一:</span>

$\forall$ 向量 $A:1 \times n$ , $X: n \times 1, Y=A\cdot X$，则 $\frac{\partial Y}{\partial X} = A^T$，其中$Y$是一个实数值。

<span style="background-Color:skyblue;font-weight:bold">证明:</span>

不妨设：
$$
A = (a_1, a_2, a_3, ..., a_n)\\
X = (x_1, x_2, x_3, ..., x_n)^T\\
\therefore Y = (a_1, a_2, a_3, ..., a_n)\cdot \left[\begin{matrix} x_1\\x_2\\x_3\\.\\.\\.\\x_n\end{matrix}\right] = \sum_{i = 1}^{n}a_ix_i
$$
当我们在对x_i，求导的时候其余$x_j, j \neq i$，均可以看做常数，则：
$$
\frac{\partial Y}{\partial x_i} = 0 + ...+0 + a_i + 0 +... + 0\\
\therefore \frac{\partial Y}{\partial X} = \left[\begin{matrix}\frac{\partial Y}{\partial x_1}\\ \frac{\partial Y}{\partial x_2}\\.\\.\\.\\ \frac{\partial Y}{\partial x_{n-1}}\\\frac{\partial Y}{\partial x_n}\\\end{matrix}\right] = \left[\begin{matrix}a_1\\ a_2\\.\\.\\.\\a_{n-1}\\ a_n\end{matrix}\right] = (a_1, a_2, a_3, ..., a_n)^T = A^T
$$
由上述分析可知：
$$
\frac{\partial Y}{\partial X} = A^T
$$
<span style="background-Color:skyblue;font-weight:bold">公求导式法则二:</span>

当$Y = X^TA$，其中 $X:n\times 1, A:n\times 1$，则$\frac{\partial Y}{\partial X} = A$

<span style="background-Color:skyblue;font-weight:bold">公求导式法则三:</span>

当$Y = X^TAX$，其中 $X:1\times n, A : n\times n$，则$\frac{\partial Y}{\partial X} = (A^T + A)X$

上面公式同理可以证明，在这里不进行赘述了。
$$
\mathcal{L(\hat{w})} =\hat{w}^TX^TX\hat{w} - \hat{w}^TX^TY - Y^TX\hat{w} + Y^TY \tag{19}
$$
有公式$(19)$和上面求导法则可知：
$$
\frac{\partial \mathcal{L(\hat{w})}}{\partial \hat{w}} = ((X^TX)^T + X^TX)\hat{w} - X^TY - (Y^TX)^T\\
= 2X^TX\hat{w} - 2X^TY  = 2X^T(X\hat{w} - Y) = 0\\
\therefore X^TX\hat{w} = X^TY \\
\therefore \hat{w}^* = (X^TX)^{-1}X^TY
$$
即 $\hat{w}^* = (X^TX)^{-1}X^TY$ 为我们要求的参数。

<h2 style="text-align:center">性回归实现过程</h2>

在编码实现线性回归的过程中，如果数据集比较小可以直接所有的数据同时进行计算一次性求出$\hat{w}^* = (X^TX)^{-1}X^TY$的值，节省计算资源，但是如果数据量过大的话，计算无法一次性完成，可以使用随机梯度下降法，进行多次迭代学习，得到最终的结果。
