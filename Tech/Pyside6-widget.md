# 用到的库
QApplication\
QWidget

# 使用方法
1.1 直接使用QWidget\
1.2 继承Qwidget，封装类\
2 加载uic生成的类


```python
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget

app = QApplication()

wid = QWidget()
wid.resize(250,150)
wid.setWindowTitle('Simple')
wid.show()

app.exec()

```

super(): 子类调用父类方法\
有属性依赖调用此方法
```python
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget

class ex(QWidget):
  def __init__(self):
    super(ex,self).__init__()
    self.initUI()
  def initUI(self):
    self.setGeometry(300,300,250,150)
    self.setWindowTitle('Icon')
    self.show()

def main():
  app = QApplication()
  exp = ex()
  app.exec()

if __name__ == '__main__':
  main()
```

# tooltip
```python
    self.setToolTip('this is a <b>QWidget</b> widget')
```

# pushbutton
```python
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget


from PySide6.QtWidgets import QPushButton
from PySide6 import QtCore

class ex(QWidget):
  def __init__(self):
    super().__init__()
    self.initUI()
  def initUI(self):
    self.setToolTip('this is a <b>QWidget</b> widget')
    self.setGeometry(300,300,250,150)
    self.setWindowTitle('Icon')

    qbtn = QPushButton('Quit',self)
    qbtn.clicked.connect(QtCore.QCoreApplication.instance().quit)
    qbtn.resize(qbtn.sizeHint())
    qbtn.move(50,50)

    self.show()

def main():
  app = QApplication()
  exp = ex()
  app.exec()

if __name__ == '__main__':
  main()
```

# messagebox
```python
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget


from PySide6.QtWidgets import QPushButton
from PySide6.QtWidgets import QMessageBox
from PySide6 import QtCore


class ex(QWidget):
  def __init__(self):
    super().__init__()
    self.initUI()
  def initUI(self):
    self.setToolTip('this is a <b>QWidget</b> widget')
    self.setGeometry(300,300,250,150)
    self.setWindowTitle('Icon')
    self.show()

  def closeEvent(self,event):
    reply = QMessageBox.question(self,'Message','Are u sure to quit',QMessageBox.Yes | QMessageBox.No,QMessageBox.No)
    if reply == QMessageBox.Yes:
      event.accept()
    else:
      event.ignore()


def main():
  app = QApplication()
  exp = ex()
  app.exec()

if __name__ == '__main__':
  main()
```
# center
```python
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget

from PySide6.QtWidgets import QPushButton
from PySide6.QtWidgets import QMessageBox
from PySide6 import QtCore

class ex(QWidget):
  def __init__(self):
    super().__init__()
    self.initUI()
  def initUI(self):
    self.setToolTip('this is a <b>QWidget</b> widget')
    self.setGeometry(300,300,250,150)
    self.center()
    self.setWindowTitle('Icon')
    self.show()

  def center(self):
    """将窗口居中显示在屏幕上"""
    # 获取屏幕信息
    desktop = QApplication.primaryScreen()
    
    if desktop:
        # 获取屏幕可用区域
        screen_rect = desktop.availableGeometry()
        # 计算居中位置
        x = (screen_rect.width() - self.width()) // 2
        y = (screen_rect.height() - self.height()) // 2
        # 移动窗口
        self.move(x, y)

def main():
  app = QApplication()
  exp = ex()
  app.exec()

if __name__ == '__main__':
  main()
```
