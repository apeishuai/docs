界面设计的核心：自适应
各种控件设计


静态布置
	frame
	menu bar
	tool bar
	dock widget
	central widget	
	status bar
动态特性
	窗口变化：子组件变化逻辑1
		sizehint:
			fixed 
			minimum
			maximum
			expanding:
		qsizepolicy
		minsize maxsize: high width
		越靠近某一侧，变化越慢
		隐藏一部分

sizehint 规则：

并列关系：   rect，根据规则计算长宽，+policy
QSizePolicy 策略：	对 sizeHint 的影响
Fixed	                严格使用 sizeHint，不扩展也不压缩。
Minimum	                至少为 sizeHint，可以扩展。
Maximum	                最大为 sizeHint，可以压缩。
Preferred	                尽量使用 sizeHint，但可扩展或压缩。
Expanding	        以 sizeHint 为基准，主动扩展并允许压缩。
MinimumExpanding minimum和expand的合体
Ignored                    完全忽略sizehint和minimumSizeHint，仅根据其他控件的策略分配空间(控件大小应由布局中的其他控件决定)

# qwidget

![](https://img2024.cnblogs.com/blog/3531360/202504/3531360-20250424141126058-180141274.png)

The widget is the atom of the user interface: it receives mouse, keyboard and other events from the window system, and paints a representation of itself on the screen. Every widget is rectangular, and they are sorted in a Z-order. A widget is clipped by its parent and by the widgets in front of it.  
A widget that is not embedded in a parent widget is called a window. Usually, windows have a frame and a title bar, although it is also possible to create windows without such decoration using suitable window flags. In Qt, QMainWindow and the various subclasses of QDialog are the most common window types.

### qmainwindow:
qobject

qtmetamacros.h

```scss
#define Q_PROPERTY(...) QT_ANNOTATE_CLASS(qt_property, __VA_ARGS__) //(...)表示变长参数，__VA_ARGS__ 是一个特殊的预处理器变量，它代表 ... 中的所有参数
# define QT_ANNOTATE_CLASS(type, ...)

Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
           [RESET resetFunction]
           [NOTIFY notifySignal]
           [REVISION int | REVISION(int[, int])]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
           [USER bool]
           [BINDABLE bindableProperty]
           [CONSTANT]
           [FINAL]
           [REQUIRED])
```