import asoka as a
from Service.Database.DbProfile import *
from Service.Console import *


class Field:
    def __init__(self, name=None, datatype=None, access=(False, False), regular=None, main=True, autoupdate=False):
        self.name = name
        self.datatype = datatype
        self.access = access
        self.regular = regular
        self.main = main
        self.autoupdate = autoupdate


class NetProfile:
    def __init__(self):
        pass


class Mode:
    def __init__(self, database_profile: DbProfile = False, net_profile: NetProfile = False):
        self.database = database_profile
        self.network = net_profile


def generate_imports():
    return f"""
import json
import asoka as a
from Service import Console
from Service.Database.SqLite import SqLite as Database
"""


def generate_getter(fld):
    return f"""
def get{fld.name.capitalize()}(self):
    return self.__{fld.name}__.value
"""


def generate_setter(fld):
    return f"""
def set{fld.name.capitalize()}(self, value):
    if isinstance(value, {fld.datatype}):
        self.__{fld.name}__.value = value
    else:
        a.warning('Метод set для поля {fld.name} вызван с неверным типом данных')
"""


def generate_to_json():
    pass


def generate_database_service(db_mode):
    result = {}

    result['__database_is_ok__'] = f"""
def __database_is_ok__(self):
    return True
"""

    result['exist'] = f"""
def exist(self, id=None):
    if not self.__database_is_ok__():
        Console.warning("Type.load(): обращение к SQL с некорректными параметрами")
        return
    if id is None:
        id = self.__id__.value
    table = self.database.get('table')
    id = self.get('id')
    if id == asoka.nullInt:
        return False
    query = 'SELECT id FROM %s WHERE id = %s;' % (self.__mode__.database.table, id)
    data = Database.query(query)
    if len(data) == 0:
        return False
    else:
        return True
"""

    return result


def quotes(string):
    return f"'{string}'"


def to_sql(value, datatype):
    t = a.types
    if datatype in (t.int, t.bool, t.float):
        return str(value)
    elif datatype in (t.str, t.bytes):
        return quotes(str(value))


def from_sql(value, datatype):
    pass


def generate_insert(db_mode):
    code = f"""
def __insert__(self, keys):
    from Service.Database.{db_mode.lang} import {db_mode.lang} as db
    names = ''
    values = ''

    for key in keys:
        field = eval('self.__%s__' % key)
        if True in field.access:
            value = field.value
        else:
            value = eval('self.%s' % key)

        names += key + ', '
        values += to_sql(value, field.datatype) + ', '
    names = names[0:len(names) - 2]
    values = values[0:len(values) - 2]

    query = 'INSERT INTO {db_mode.table} (%s) VALUES(%s);' % (names, values)
    comment('New query: %s' % query)
    return
"""
    if db_mode.lang == a.types.db.lang.sqlite:
        code += f"""
    data = db.execute(query, True)
"""
    return {'__insert__': code}


def generate_update(lang=a.types.db.lang.sqlite):
    pass


def generate_select(lang=a.types.db.lang.sqlite):
    pass


def generate_remove(lang=a.types.db.lang.sqlite):
    pass


def create_class(classname, parents=(), structure=(), mode: Mode = False):
    struct = {}
    functions = {}

    struct['__mode__'] = mode

    # Добавляем в структуру поля будущего класса
    fields = []
    for fld in structure:
        name = f'__{fld.name}__'
        fields.append(name)
        struct[name] = fld

        get, set = fld.access
        if get:
            functions[f'get{fld.name.capitalize()}'] = generate_getter(fld)
        if set:
            functions[f'set{fld.name.capitalize()}'] = generate_setter(fld)

        if True in fld.access:
            struct[name].value = None
        elif fld.datatype in a.types.all:
            struct[fld.name] = eval(f'{fld.datatype}()')
        else:
            struct[fld.name] = None
    struct['__fields__'] = fields

    # Создаем код методов
    if mode.database is not False:
        db_mode = mode.database
        struct['to_sql'] = to_sql
        struct['from_sql'] = from_sql
        functions.update(generate_database_service(db_mode))
        functions.update(generate_insert(db_mode))

    # Добавляем в структуру методы будущего класса
    exec(generate_imports())
    for key in functions.keys():
        comment(f'Объявляю метод {key}(?)...')
        exec(functions[key])
        struct[key] = eval(key)

    inheritance = ''
    for parent in parents:
        inheritance += f'parent, '
    inheritance = f'({inheritance[0:len(inheritance) - 2]})'
    return type(classname, eval(inheritance), struct)
