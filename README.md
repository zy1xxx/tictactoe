# tictactoe

这是一个用qt实现的tictacoe游戏。

主要运用的mini-max tree search和alpha-beta pruning,其实井字棋的状态数量很少，不需要alpha-beta pruning，但是为了练习并且为后面五子棋AI的项目做准备，所以加入了alpha-beta pruning。

先用一个cpp文件，使用命令行的交互方式实现一个tictactoe game，然后再将其移植到qt上，实现其ui。

qt的部分写得很匆忙，导致项目结构是不是很好，比如AI计算的函数放在了鼠标监听回调里面，虽然这个项目AI计算量很小，但是对于计算量大一点AI可能会使回调函数阻塞。

## 算法

### alpha-beta pruning
使用深度优先搜索，父节点的alpha beta要传到子节点上，到达叶子节点计算状态的value值，然后回溯。

回溯的时候max层的更新alpha的值，取本节点alpha值，子节点alpha、beta值的最大值，min层的更新beta的值，取本节点alpha值，子节点alpha、beta值的最小值。

为了能让根节点直接获取到下棋的位置，状态中还加入一个下一个落子位置的变量。

### 计算value
记AI棋子为1，玩家棋子为4，计算每行每列斜向的和，根据值的情况判断是否是三连，还是两连空，还是一个空两
根据不同情况计分，玩家和AI都算一次，最终得分为 AI-玩家

