import datetime
import asoka as a


def write(text):
    global mode
    text = f'{getTimeMark()} :: {text}'
    if mode == 1:
        with getLogFile() as file:
            file.write(text)
    elif mode == 2:
        print(text)


def getLogFile():
    file = open(a.dir.log, 'a')
    file.write('\n')
    return file


def getTimeMark():
    now = datetime.datetime.now()
    return now.strftime("%d-%m-%Y %H:%M:%S")


def comment(text, newline = False):
    global level
    if level > 1: return
    if newline:
        text = '\n' + text
    write(text)


def warning(text):
    if level > 2: return
    write(f"WARNING !!! {text}")


def error(text):
    if level > 3: return
    write(f"ERROR !!! {text}")


a.comment = comment
a.warning = warning
a.error = error


mode = 1
level = 2
