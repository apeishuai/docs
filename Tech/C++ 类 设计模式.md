![](/skins/bj2008/images/fire.gif) [c++ 类 设计模式](https://www.cnblogs.com/apeishuai/articles/18853258 "发布于 2025-04-29 10:49")

# 类关系

![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250429104807174-2036723337.png)  
C++ 的接口 用 纯虚类 表示，所有方法都是 = 0。

如果你确定两件对象之间是is-a的关系，那么此时你应该使用继承；比如菱形、圆形和方形都是形状的一种，那么他们都应该从形状类继承。  
如果你确定两件对象之间是has-a的关系，那么此时你应该使用聚合；比如电脑是由显示器、CPU、硬盘等组成的，那么你应该把显示器、CPU、硬盘这些类聚合成电脑类。  
如果你确定两件对象之间是like-a的关系，那么此时你应该使用组合；比如空调继承于制冷机，但它同时有加热功能，那么你应该把让空调继承制冷机类，并实现加热接口。

### 依赖关系

形式参数、局部变量、静态方法调用和返回值

形式参数

```cpp
// Logger 类
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// DataProcessor 类通过形式参数依赖 Logger
class DataProcessor {
public:
    void process(int data, Logger& logger) {  // Logger 作为形式参数
        logger.log("Processing data: " + std::to_string(data));
        // 处理数据...
    }
};

int main() {
    Logger logger;
    DataProcessor processor;
    processor.process(42, logger);  // 传递 Logger 实例
    return 0;
}
```

局部变量

```cpp
// Logger 类
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// ReportGenerator 类通过局部变量依赖 Logger
class ReportGenerator {
public:
    void generateReport() {
        Logger logger;  // Logger 作为局部变量
        logger.log("Generating report...");
        // 生成报告...
    }
};

int main() {
    ReportGenerator generator;
    generator.generateReport();
    return 0;
}
```

静态方法

```cpp
// Logger 类
class Logger {
public:
    static void log(const std::string& message) {  // 静态方法
        std::cout << "[LOG] " << message << std::endl;
    }
};

// NetworkManager 类通过静态方法调用依赖 Logger
class NetworkManager {
public:
    void connect() {
        Logger::log("Connecting to network...");  // 调用静态方法
        // 连接网络...
    }
};

int main() {
    NetworkManager manager;
    manager.connect();
    return 0;
}
```

返回值

```cpp
#include <iostream>
#include <string>

class Logger{
public:
        Logger(const std::string& name): name(name){}
        void log(const std::string& message){
                std::cout << "[" << name << "]" << message << std::endl;
        }
private:
        std::string name;

};

class LoggerFactory{
public:
        Logger createLogger(const std::string& name){
        Logger logger(name);
        logger.log("Logger created");
        return logger;
        }
};

int main(){
        LoggerFactory factory;
        Logger myLogger = factory.createLogger("MyApp");
        myLogger.log("Application started");
        return 0;
}
```

### 继承

  

特殊化子类型、规范化子类型、扩展子类化

特殊化子类型：子类是父类的一种特殊形式  
规范化子类型：父类和子类维持一样的接口，父类仅定义行为，却不实现，推迟到子类中实现  
扩展子类化：对父类增加新的功能，且子类的功能与父类联系不密切

特殊化子类型

```cpp
#include <iostream>
#include <string>

class Window{
protected:
        int x,y;
        int width,height;
        bool isMinized;
        std::string title;
public:
        Window(const std::string& title,int x,int y,int width,int height): title(title),x(x),y(y),width(width),height(height){}

        virtual void move(int newX,int newY){
                x = newX;
                y = newY;
        }
        virtual void resize(int newWidth,int newHeight){
                width = newWidth;
                height = newHeight;
                std::cout << title << "resized to " << width << "x" << height << "\n";
        }
        virtual void minimize(){
                isMinized = true;
                std::cout << title << "minimized\n";
        }

        virtual void restore(){
                isMinized = false;
                std::cout << title << "restored\n";
        }
        virtual void display() const{
                std::cout << "Window '" << title << "' at (" << x  << ", " << y << "), " << "size: " << width << "x" << height << ", " << (isMinized ? "Minimized" : "Normal") << "\n";
        }

        virtual ~Window(){}
};

class TextEditWindow: public Window{
private:
        std::string content;
        bool isReadOnly;

public:
        TextEditWindow(const std::string& title, int x,int y,int width,int height):Window(title,x,y,width,height),content(""),isReadOnly(false){}

        void setContent(const std::string& text){
                if(!isReadOnly){
                        content = text;
                        std::cout << title << "content updated\n";}else
                        {
                                std::cout << title << "is read-only, cannot modify content\n";
                        }
                }

        void setReadOnly(bool readOnly){
                isReadOnly = readOnly;
                std::cout << title << "is now " << (isReadOnly ? "readonly" : "writable") << "\n";
        }

        void display() const override{
                Window::display();
                std::cout << " Content: \"" << content << "\"\n";
        }
};

void manipulateWindow(Window& window){
        window.move(100,200);
        window.resize(800,600);
        window.minimize();
        window.restore();
        window.display();
}


int main(){
        Window normalWindow("Normal Window",50,50,400,300);
        TextEditWindow textWindow("Text Editor",200,100,500,400);
        textWindow.setContent("hello world");
        textWindow.setReadOnly(false);

        std::cout << "\nManipulating base Window:\n";
        manipulateWindow(normalWindow);

        std::cout << "\nManipulating TextEditWindow (subcalss):\n";
        manipulateWindow(textWindow);

        std::cout << "\nManipulating TextEditWindow specific features:\n";
        textWindow.setContent("update content");
        textWindow.setReadOnly(true);
        textWindow.setContent("Try to change read-only content");
        textWindow.display();

        return 0;
}
```

规范化子类型

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class GraphicalObject {
public:
    virtual void draw() const = 0;
    virtual void handleCollision(GraphicalObject* other) = 0;
    virtual std::string getType() const = 0;

    void moveTo(double x, double y) {
        this->x = x;
        this->y = y;
        std::cout << getType() << " moved to (" << x << ", " << y << ")\n";
    }

    double distanceTo(GraphicalObject* other) const {
        double dx = x - other->x;
        double dy = y - other->y;
        return std::sqrt(dx*dx + dy*dy);
    }

    virtual ~GraphicalObject() {}

protected:
    double x = 0;
    double y = 0;
};

class Ball : public GraphicalObject {
public:
    Ball(double radius) : radius(radius) {}

    void draw() const override {
        std::cout << "Drawing Ball at (" << x << ", " << y
                  << ") with radius " << radius << "\n";
    }

    void handleCollision(GraphicalObject* other) override {
        std::cout << "Ball collided with " << other->getType()
                  << " at (" << x << ", " << y << ")\n";
    }

    std::string getType() const override { return "Ball"; }

private:
    double radius;
};

class Wall : public GraphicalObject {
public:
    Wall(double length) : length(length) {}

    void draw() const override {
        std::cout << "Drawing Wall from (" << x << ", " << y
                  << ") to (" << x + length << ", " << y << ")\n";
    }

    void handleCollision(GraphicalObject* other) override {
        std::cout << "Wall collided with " << other->getType()
                  << " at position (" << x << ", " << y << ")\n";
    }

    std::string getType() const override { return "Wall"; }

private:
    double length;
};

class Hole : public GraphicalObject {
public:
    Hole(double radius) : radius(radius) {}

    void draw() const override {
        std::cout << "Drawing Hole at (" << x << ", " << y
                  << ") with radius " << radius << "\n";
    }

    void handleCollision(GraphicalObject* other) override {
        std::cout << "Hole swallowed " << other->getType()
                  << " at (" << x << ", " << y << ")\n";
    }

    std::string getType() const override { return "Hole"; }

private:
    double radius;
};

class GameScene {
public:
    void addObject(GraphicalObject* obj) {
        objects.push_back(obj);
    }

    GraphicalObject* getObject(size_t index) {
        if (index < objects.size()) {
            return objects[index];
        }
        return nullptr;
    }

    void drawAll() const {
        for (const auto& obj : objects) {
            obj->draw();
        }
    }

    void simulateCollisions() {
        for (size_t i = 0; i < objects.size(); ++i) {
            for (size_t j = i + 1; j < objects.size(); ++j) {
                if (objects[i]->distanceTo(objects[j]) < 5.0) {
                    objects[i]->handleCollision(objects[j]);
                    objects[j]->handleCollision(objects[i]);
                }
            }
        }
    }

    ~GameScene() {
        for (auto obj : objects) {
            delete obj;
        }
    }

private:
    std::vector<GraphicalObject*> objects;
};

int main() {
    GameScene scene;

    scene.addObject(new Ball(3.0));
    scene.addObject(new Wall(10.0));
    scene.addObject(new Hole(2.0));
    scene.addObject(new Ball(2.5));

    dynamic_cast<Ball*>(scene.getObject(0))->moveTo(2.0, 3.0);
    dynamic_cast<Wall*>(scene.getObject(1))->moveTo(0.0, 0.0);
    dynamic_cast<Hole*>(scene.getObject(2))->moveTo(8.0, 8.0);
    dynamic_cast<Ball*>(scene.getObject(3))->moveTo(7.5, 7.5);

    std::cout << "\nDrawing all objects:\n";
    scene.drawAll();

    std::cout << "\nSimulating collisions:\n";
    scene.simulateCollisions();

    return 0;
}
```

扩展化子类型

```cpp
#include <set>
#include <string>
#include <algorithm>
#include <iostream>

template <typename T>
class Set {
protected:
    std::set<T> elements;

public:
    void add(const T& element) {
        elements.insert(element);
    }

    void remove(const T& element) {
        elements.erase(element);
    }

    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    size_t size() const {
        return elements.size();
    }

    void display() const {
        std::cout << "{ ";
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << "}" << std::endl;
    }

    virtual ~Set() {}
};

class StringSet : public Set<std::string> {
public:
    StringSet findByPrefix(const std::string& prefix) const {
        StringSet result;
        for (const auto& str : elements) {
            if (str.compare(0, prefix.length(), prefix) == 0) {
                result.add(str);
            }
        }
        return result;
    }

    StringSet findBySubstring(const std::string& substring) const {
        StringSet result;
        for (const auto& str : elements) {
            if (str.find(substring) != std::string::npos) {
                result.add(str);
            }
        }
        return result;
    }

    void toUpperCase() {
        std::set<std::string> newElements;
        for (const auto& str : elements) {
            std::string upperStr = str;
            std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
            newElements.insert(upperStr);
        }
        elements = newElements;
    }
};

int main() {
    Set<int> numberSet;
    numberSet.add(1);
    numberSet.add(2);
    numberSet.add(3);

    std::cout << "Number Set: ";
    numberSet.display();

    StringSet stringSet;
    stringSet.add("apple");
    stringSet.add("application");
    stringSet.add("banana");
    stringSet.add("appetizer");
    stringSet.add("cherry");

    std::cout << "\nOriginal String Set: ";
    stringSet.display();

    stringSet.remove("banana");
    std::cout << "After removing 'banana': ";
    stringSet.display();

    StringSet appSet = stringSet.findByPrefix("app");
    std::cout << "\nStrings starting with 'app': ";
    appSet.display();

    stringSet.toUpperCase();
    std::cout << "\nAfter converting to uppercase: ";
    stringSet.display();

    StringSet eSet = stringSet.findBySubstring("E");
    std::cout << "\nStrings containing 'E': ";
    eSet.display();

    return 0;
}
```

好文要顶 关注我 收藏该文 微信分享

[![](https://pic.cnblogs.com/face/3531360/20250403195920.png)](https://home.cnblogs.com/u/apeishuai/)

[Pomr](https://home.cnblogs.com/u/apeishuai/)  
[粉丝 - 0](https://home.cnblogs.com/u/apeishuai/followers/) [关注 - 2](https://home.cnblogs.com/u/apeishuai/followees/)  

0

0

[升级成为会员](https://cnblogs.vip/)

[«](https://www.cnblogs.com/apeishuai/articles/18849856) 上一篇： [c++ template](https://www.cnblogs.com/apeishuai/articles/18849856 "发布于 2025-04-27 16:53")  
[»](https://www.cnblogs.com/apeishuai/articles/18861366) 下一篇： [网络编程 socket](https://www.cnblogs.com/apeishuai/articles/18861366 "发布于 2025-05-06 13:48")

posted on 2025-04-29 10:49  [Pomr](https://www.cnblogs.com/apeishuai)  阅读(3)  评论(0)  [MD](https://www.cnblogs.com/apeishuai/articles/18853258.md)  [编辑](https://i.cnblogs.com/EditArticles.aspx?postid=18853258)  收藏  举报