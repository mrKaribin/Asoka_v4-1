import asoka as a
from Service.Database.DbProfile import *


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
        self.net = net_profile


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


def generate_service():
    result = {}

    result['__database_is_ok__'] = f"""
def __database_is_ok__(self):
    return True
"""

    result['__insert__'] = f"""
def __insert__(self, fields):
    for 
"""

    return result


def generate_exist(table):
    return f"""
def exist(self, id=self.__id__):
    if not self.__database_is_ok__():
        Console.warning("Type.load(): обращение к SQL с некорректными параметрами")
        return
    table = self.database.get('table')
    id = self.get('id')
    if id == asoka.nullInt:
        return False
    query = f'SELECT id FROM {table} WHERE id = {id};'
    data = Database.query(query)
    if len(data) == 0:
        return False
    else:
        return True
"""


def generate_save():
    return f"""
def save(self):
    if self.exist():
        self.update()
    else:
        self.insert()
"""


def generate_insert(lang=a.types.db.lang.sqlite):
    pass


def generate_update(lang=a.types.db.lang.sqlite):
    pass


def generate_select(lang=a.types.db.lang.sqlite):
    pass


def generate_remove(lang=a.types.db.lang.sqlite):
    pass


def create_class(classname, parents=(), structure=(), mode=()):
    struct = {}
    functions = {}

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
    functions.update(generate_service())

    # Добавляем в структуру методы будущего класса
    exec(generate_imports())
    for key in functions.keys():
        exec(functions[key])
        struct[key] = eval(key)

    inheritance = ''
    for parent in parents:
        inheritance += f'parent, '
    inheritance = f'({inheritance[0:len(inheritance) - 2]})'
    return type(classname, eval(inheritance), struct)
