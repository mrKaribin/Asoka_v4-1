
comment = None
warning = None
error = None


nullInt = -1


class types:
    int = 'int'
    float = 'float'
    str = 'str'
    bool = 'bool'
    bytes = 'bytes'
    list = 'list'
    dict = 'dict'
    tuple = 'tuple'

    simple = (int, float, str, bool, bytes)
    all = (int, float, str, bool, bytes, list, dict, tuple)

    class db:
        class lang:
            mysql = 'MySql'
            sqlite = 'SqLite'


class dir:
    log = 'log.txt'
