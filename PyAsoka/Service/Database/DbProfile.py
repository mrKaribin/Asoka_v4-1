import asoka as a


class DbProfile:
    def __init__(self, lang=a.types.db.lang.sqlite, name=None, user=None, password=None, table=None):
        self.lang = lang
        self.name = name
        self.user = user
        self.password = password
        self.table = table
