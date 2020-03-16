import java.awt.*;
import java.util.Stack;
import java.util.LinkedList;


public class Visualizer {
    private static int DELAY = 5;
    private static int blockSide = 8;

    private MazeData data;
    private AlgoFrame frame;
    private static final int d[][] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    /**
     *
     * @param mazeFile
     * @param algoType: 1 - runDFS;
     *                  2 - runRecursiveDFS;
     *                  3 - runBFS;
     */
    public Visualizer(String mazeFile, int algoType) {
        // 初始化数据
        data = new MazeData(mazeFile);
        int sceneHeight = data.N() * blockSide;
        int sceneWidth = data.M() * blockSide;

        // 初始化视图
        EventQueue.invokeLater(() -> {
            frame = new AlgoFrame("Maze Solver Visualization", sceneWidth, sceneHeight);

            new Thread(() -> {
                if (algoType == 1) {
                    runDFS();
                } else if (algoType == 2) {
                    runRecursiveDFS();
                } else if (algoType == 3) {
                    runBFS();
                }
            }).start();
        });
    }

    private void runDFS() {
        printData(-1, -1, false);

        Stack<Position> stack = new Stack<Position>();
        Position entrance = new Position(data.getEntranceX(), data.getEntranceY());
        stack.push(entrance);
        data.visited[entrance.getX()][entrance.getY()] = true;

        boolean isSolved = false;
        while (!stack.empty()) {
            Position curPos = stack.pop();
            printData(curPos.getX(), curPos.getY(), true);
            if (curPos.getX() == data.getExitX() && curPos.getY() == data.getExitY()) {
                isSolved = true;
                findPath(curPos);
                break;
            }
            // 遍历四个方向
            for (int i = 0; i < 4; i++) {
                int newX = curPos.getX() + d[i][0];
                int newY = curPos.getY() + d[i][1];
                if (data.inArea(newX, newY)
                        && !data.visited[newX][newY]
                        && data.getMaze(newX, newY) == MazeData.ROAD) {
                    stack.push(new Position(newX, newY, curPos));
                    data.visited[newX][newY] = true;
                }
            }
        }

        if (!isSolved) {
            System.out.println("No solution!");
        }
        printData(-1, -1, false);
    }

    private void runRecursiveDFS() {
        printData(-1, -1, false);
        if (!dfs(data.getEntranceX(), data.getEntranceY()))
            System.out.println("The maze has NO solution!");
        printData(-1, -1, false);
    }

    private boolean dfs(int x, int y) {
        if (!data.inArea(x, y))
            throw new IllegalArgumentException("x,y are out of index in go function!");

        data.visited[x][y] = true;
        printData(x, y, true);
        if (x == data.getExitX() && y == data.getExitY())
            return true;

        for (int i = 0; i < 4; i++) {
            int newX = x + d[i][0];
            int newY = y + d[i][1];
            if (data.inArea(newX, newY)
                    && !data.visited[newX][newY]
                    && data.getMaze(newX, newY) == MazeData.ROAD)
                if (dfs(newX, newY) == true)
                    return true;
        }

        // 回溯
        printData(x, y, false);
        return false;
    }

    private void runBFS() {
        printData(-1, -1, false);

        LinkedList<Position> queue = new LinkedList<Position>();
        Position entrance = new Position(data.getEntranceX(), data.getEntranceY());
        queue.addLast(entrance);
        data.visited[entrance.getX()][entrance.getY()] = true;

        boolean isSolved = false;
        while (queue.size() != 0) {
            Position curPos = queue.poll();
            printData(curPos.getX(), curPos.getY(), true);
            if (curPos.getX() == data.getExitX() && curPos.getY() == data.getExitY()) {
                isSolved = true;
                findPath(curPos);
                break;
            }
            for (int i = 0; i < 4; i++) {
                int newX = curPos.getX() + d[i][0];
                int newY = curPos.getY() + d[i][1];
                if (data.inArea(newX, newY)
                        && !data.visited[newX][newY]
                        && data.getMaze(newX, newY) == MazeData.ROAD) {
                    queue.addLast(new Position(newX, newY, curPos));
                    data.visited[newX][newY] = true;
                }
            }
        }

        if (!isSolved) {
            System.out.println("No solution!");
        }
        printData(-1, -1, false);
    }

    /**
     * 渲染迷宫结构或者遍历的路径
     *
     * @param x
     * @param y
     * @param isPath
     */
    private void printData(int x, int y, boolean isPath) {
        if (data.inArea(x, y))
            data.path[x][y] = isPath;

        frame.render(data);
        AlgoVisHelper.pause(DELAY);
    }

    /**
     * 输出路径数据
     *
     * @param des
     */
    private void findPath(Position des) {
        Position cur = des;
        while (cur != null) {
            data.result[cur.getX()][cur.getY()] = true;
            cur = cur.getPrev();
        }
    }

    public static void main(String[] args) {
        String mazeFile = "maze_101_101.txt";

        Visualizer vis = new Visualizer(mazeFile, 2);
    }
}
