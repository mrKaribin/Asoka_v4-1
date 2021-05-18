import sys
from Service import Global
sys.path.append(Global.PyAsoka_Path)
sys.path.append(Global.PyAsoka_Service_Path)
import asoka
from AsokaType import *


class Block(AsokaType):

    def __init__(self, id = asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('type', FieldType.int)
                .create_field('name', FieldType.string)
                .create_field('data', FieldType.blob)
                .getMap(),
            database=databaseConfig('filesystem.db', 'blocks'),
            environment=environmentConfig(__file__)
        )

    def getType(self):
        return self.get('type')

    def getData(self):
        return self.get('name')

    def getName(self):
        return self.get('data')

    def setType(self, type):
        self.set('type', type)

    def setName(self, name):
        self.set('name', name)

    def setData(self, data):
        self.set('data', data)
