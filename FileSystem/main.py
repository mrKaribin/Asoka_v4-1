import tkinter
import sys
import argparse
from Service import Global
from Widgets.MainWindow import MainWindow
from Types.File import File

sys.path.insert(0, Global.PyAsoka_Path)
import asoka


def createArgParser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-u', '--uitype', default = Global.UIType.linear)
    return parser


if __name__ == '__main__':
    parser = createArgParser()
    args = parser.parse_args(sys.argv[1:])
    Global.currentUIType = args.uitype

    file = File()

    MainWindow().run()