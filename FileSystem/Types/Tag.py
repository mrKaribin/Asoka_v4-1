import sys
from Service import Global
sys.path.append(Global.PyAsoka_Path)
sys.path.append(Global.PyAsoka_Service_Path)
import asoka
from AsokaType import *


class Tag(AsokaType):

    def __init__(self, id = asoka.nullInt):
        super().__init__(
            id=id,
            structure=Structure()
                .create_field('name', FieldType.string)
                .create_field('color', FieldType.string)
                .getMap(),
            database=databaseConfig('filesystem.db', 'tags'),
            environment=environmentConfig(__file__)
        )

    def getName(self):
        return self.get('name')

    def getColor(self):
        return self.get('color')

    def setName(self, name):
        self.set('name', name)

    def setColor(self, color):
        self.set('color', color)
