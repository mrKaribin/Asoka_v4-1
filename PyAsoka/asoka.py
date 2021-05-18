

def set(name, value):
    data[name] = value


def get(name):
    if data.get(name) is not None:
        return data.get(name)


data = {
    'user_name': 'Демьян',
    'program_name': 'Асока'
}

nullInt = -1