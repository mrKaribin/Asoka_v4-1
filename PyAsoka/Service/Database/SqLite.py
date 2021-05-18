import sqlite3 as sql
from Service import Console


def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d


class SqLite:

    connection = None
    lastRowId = None
    database = ''

    @staticmethod
    def init(path):
        SqLite.database = path
        SqLite.connection = None

    @staticmethod
    def connect():
        try:
            SqLite.connection = sql.connect(SqLite.database)
            SqLite.connection.row_factory = dict_factory
            Console.comment(f'Database connected from "{SqLite.database}"')
            return SqLite.connection.cursor()
        except sql.Error as error:
            Console.error(f"SQL connect exception ({error})")
            return None

    @staticmethod
    def getTables():
        cursor = SqLite.connect()
        with SqLite.connection:
            cursor.execute('SELECT name from sqlite_master where type = "table"')
            SqLite.connection.commit()
            return cursor.fetchall()

    @staticmethod
    def execute(query: str, save_row_id = False):
        cursor = SqLite.connect()
        try:
            with SqLite.connection:
                cursor.execute(query)
                if save_row_id:
                    SqLite.lastRowId = cursor.lastrowid
        except sql.Error as error:
            Console.error(f"SQL execute exception ({error}) with: {query}")

    @staticmethod
    def query(query: str):
        cursor = SqLite.connect()
        try:
            with SqLite.connection:
                cursor.execute(query)
                return cursor.fetchall()
        except sql.Error as error:
            Console.error(f"SQL query exception ({error}) with: {query}")
            return {}
