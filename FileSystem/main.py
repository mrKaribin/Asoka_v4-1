import tkinter
import sys
import argparse
from Service import Global
from Widgets.MainWindow import MainWindow
from Types.File import File

sys.path.insert(0, Global.PyAsoka_Path)
import asoka


def print_hi():
    print(f'Привет, {asoka.get("user_name")}, я - {asoka.get("program_name")}!')


def createArgParser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-u', '--uitype', default = Global.UIType.linear)
    return parser


if __name__ == '__main__':
    parser = createArgParser()
    args = parser.parse_args(sys.argv[1:])
    Global.currentUIType = args.uitype

    root = tkinter.Tk()
    screen_w = root.winfo_screenwidth()
    screen_h = root.winfo_screenheight()
    if Global.currentUIType == Global.UIType.linear:
        width = int(screen_w * 0.21)
        heigth = int(screen_h * 0.5)
        # print(f'{width}:{heigth}')

    file = File()

    MainWindow(400, 540).run()