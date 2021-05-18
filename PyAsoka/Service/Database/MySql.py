import pymysql as sql
from Service import Console


class MySql:

    connection = None
    host = ''
    user = ''
    password = ''
    database = ''

    @staticmethod
    def init(host, user, password, database):
        MySql.host = host
        MySql.user = user
        MySql.password = password
        MySql.database = database

    @staticmethod
    def connect():
        if MySql.connection is None or not MySql.connection.open:
            MySql.connection = sql.connect(
                host=MySql.host,
                user=MySql.user,
                password=MySql.password,
                database=MySql.database)
            cursor = MySql.connection.cursor()
            cursor.execute("SELECT VERSION()")
        else:
            cursor = MySql.connection.cursor()
        return cursor

    @staticmethod
    def getTables():
        cursor = MySql.connect()
        with MySql.connection:
            cursor.execute("SELECT `TABLE_NAME` FROM `information_schema`.`TABLES` "
                           "WHERE `TABLES`.`TABLE_SCHEMA` = 'mrKaribin$hotel_server';")
            MySql.connection.commit()
            return cursor.fetchall()

    @staticmethod
    def execute(query: str, params=None):
        if params is None:
            params = []
        cursor = MySql.connect()
        try:
            with MySql.connection:
                cursor.execute(query, params)
                MySql.connection.commit()
        except Exception:
            Console.warning(f"SQL execute exception: {query}")

    @staticmethod
    def query(query: str, params=[]):
        cursor = MySql.connect()
        try:
            with MySql.connection:
                cursor.execute(query, params)
                MySql.connection.commit()
                return cursor.fetchall()
        except Exception:
            Console.warning(f"SQL query exception: {query}")
            return {}
